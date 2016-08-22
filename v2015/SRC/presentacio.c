#include "pch.h"

#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "dibuixos.h"

#define O_OCULTO	0
#define O_MOV		1
#define O_NOMOV		2
#define O_FIN		3

enum ESTATES { MOVE_CARS,ESPERE,FIN };

typedef struct CARACTER  {
  GLdouble rad0,rad,arad,x,y,div,scale,anc,anc0,aanc;
  GLdouble ang0,ang,aang;
  int car,steps,modo;
  } CAR;

const static char esperestr[]="Prem una tecla per continuar";

static CAR *cars;
static GLdouble cx,cy;
static enum ESTATES state=MOVE_CARS;
static int bcounter_titulo=0;
static TIMER counter_titulo;
static CAR *car_titulo=NULL;
static char *esp_texto;
static char *esp_textorender;
static int esp_ndx,esp_len;
static GLdouble esp_scale;
static TIMER esp_titulo;

static int presentacio_init(void *init_params);
static int presentacio_initgl(void *init_params);
static void presentacio_render();
static void presentacio_finalize();

const DIBUIXO dib_presentacio=
{
    "presentacio",
	"presentacio",
	NULL,
    presentacio_init,
    presentacio_initgl,
    presentacio_render,
    presentacio_finalize
};

//const static Uint32 presentacio_timer=3*1000;

const static char *Titulo[]={
  "DIBUIXOS", 
  "MATEMATICS",
  NULL
  };

static int presentacio_init(void *init_params)
{
	size_t size=1;
	char **str=(char **)Titulo;
	
	while (*str)
		size += strlen(*str++);
	if (!(cars=calloc(size,sizeof(CAR))))
		seterror("presentacio_init: %s",strerror(errno));
	memset(cars,0,size*sizeof(CAR));
	esp_texto=
		(demo) 
			? (char *) autor 
			: (dibuixo_arg!=NULL) ? (char *) texto_anykey_salir : (char *) esperestr;
	esp_ndx=0;
	esp_len=strlen(esp_texto);
	if (!(esp_textorender=calloc(esp_len+1,sizeof(char))))
		seterror("presentacio_init: %s",strerror(errno));
	*esp_textorender='\x0';
	
	return 0;
}

static void calc_car_xy(CAR *cars)
{
	cars->x=cx-cars->rad*cos(cars->ang);
	cars->y=cy+cars->rad*sin(cars->ang)-cars->anc;
	cars->scale=cars->anc/cars->div;
}

static int titulo_initgl(CAR *cars)
{
	GLdouble rad,arad,divx,divy,div,anc,alfa,beta;
	int ncars;
	char **str=(char **)Titulo;
	char *str2;
	
	car_titulo=cars;
	rad=min(width,height)/2.0d;
	cx=width/2.0d;
	cy=height/2.0d;
	arad=rad/(GLdouble)((sizeof(Titulo)/sizeof(*Titulo)));
	arad += arad / 2.0d;
	anc=120.0d*rad/348.0d;
	for (;(str2=*str);str++,rad -= arad,anc /= 2.0d)
	{
		ncars=strlen(str2);
		divx=glexStrokeMinWidth(GLUT_STROKE_MONO_ROMAN,str2);
		divy=glexStrokeMinHeight(GLUT_STROKE_MONO_ROMAN,str2);
		div=min(divx,divy);
		alfa=atan
			(
				(double) (glexStrokeStrWidth(GLUT_STROKE_MONO_ROMAN,str2)/2.0d)
				/(double) (glexStrokeStrHeight(GLUT_STROKE_MONO_ROMAN,str2))
			);
		beta=M_PI_2-alfa;
		alfa /= (double) (ncars >> 1);
		if (!(ncars & 1))
			beta += alfa/2;
		for(;*str2;str2++,cars++,beta += alfa)
		{
			cars->car=*str2;
			cars->div=div;
			cars->ang0=beta;
			cars->ang=M_PI*2.0d;
			cars->aang=alfa;
			cars->steps=(cars->ang-cars->ang0)/cars->aang;
			cars->rad0=rad;
			cars->rad=0;	
			cars->arad=rad/(GLdouble)cars->steps;
			cars->modo=O_OCULTO;
			cars->anc0=anc;
			cars->anc=1;
			cars->aanc=anc/((GLdouble)cars->steps+1.0d);
			calc_car_xy(cars);
		}
	}
	cars->modo=O_FIN;
	bcounter_titulo=0;
	
	return 0;
}

static int espere_initgl()
{
	int divx=glexStrokeStrWidth(GLUT_STROKE_ROMAN,esp_texto);
	
	esp_scale=(divx>width) ? (GLdouble) width/(GLdouble) divx : 1.0d;
	
	return 0;
}

static int presentacio_initgl(void *init_params)
{
	int ret=0;
	
	glexOrthoWindow();
	if (!(ret=titulo_initgl(cars)))
		ret=espere_initgl();
     
    return ret;
}

static void titulo_update(CAR *carsptr)
{
	CAR *cars=car_titulo;
	int modo;
	
	if (cars->modo==O_FIN)
	{
		for (cars=carsptr;(modo=cars->modo)==O_NOMOV;cars++);
		if (modo==O_FIN)
		{
			state=ESPERE;
			init_timers(&esp_titulo);
			
			return;
		}
		car_titulo=cars;
	}
	if (!bcounter_titulo || count_timers(&counter_titulo,3))
	{
		if (cars->modo==O_MOV)
		{
			cars->rad=min(cars->rad+cars->arad,cars->rad0);
			cars->ang -= cars->aang;
			while (cars->ang<0) cars->ang += 2*M_PI;
			if (cars->steps--<=0)
			{
				cars->rad=cars->rad0;
				cars->anc=cars->anc0;
				cars->ang=cars->ang0;
				cars->modo=O_NOMOV;
			}			
			car_titulo++;
		}
		else
		{
			cars->modo=O_MOV;
			car_titulo=carsptr;
		}
		cars->anc=min(cars->anc+cars->aanc,cars->anc0);
		calc_car_xy(cars);
		bcounter_titulo=1;
		init_timers(&counter_titulo);
	}
}

static void presentacio_fin()
{
	state=FIN;
	if (!demo)
		waitanykey=1;
}

static void espere_update()
{
	int by;
	
	if (count_timers(&esp_titulo,7))
	{
		esp_ndx++;
		if (esp_ndx>esp_len)
		{
			presentacio_fin();
			
			return;
		}
		strncpy(esp_textorender,esp_texto,(by=(esp_ndx >> 1)+(esp_ndx & 1)));
		strcpy(esp_textorender+by,esp_texto+esp_len-(esp_ndx >> 1));
	}
}

static void titulo_render(CAR *cars)
{
	for (;cars->modo!=O_FIN;cars++)
	{
		if (cars->modo!=O_OCULTO)
		{
			glPushMatrix();
			glTranslated(cars->x,cars->y,0);
			glScaled(cars->scale,cars->scale,0);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, cars->car);
			glPopMatrix();			
		}
	}
}

static void espere_render()
{
	GLdouble w=(GLdouble) glexStrokeStrWidth(GLUT_STROKE_ROMAN,esp_textorender)*esp_scale;
	GLdouble h=(GLdouble) glexStrokeStrHeight(GLUT_STROKE_ROMAN,esp_textorender)*esp_scale;
	
	glPushMatrix();
	glTranslated(((GLdouble) width-w)/2.0d,h,0);
	glScaled(esp_scale,esp_scale,0);
	glutStrokeStr(GLUT_STROKE_ROMAN, esp_textorender);
	glPopMatrix();	
}

static void presentacio_render()
{
	//unsigned int elapse=elapse_timers(&timer_dib,1);
	
	switch(state)
	{
		case MOVE_CARS:
			titulo_update(cars);
			break;
		case ESPERE:
			espere_update();
			break;
	}
	glClearColor( 0.f, 0.f, 0.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT );	
    glColor3d( 1, 1, 1 );
	titulo_render(cars);
	if (state>=ESPERE)
		espere_render();
	glutSwapBuffers();
}

static void presentacio_finalize()
{
    FREE(cars);
	FREE(esp_textorender);
}
