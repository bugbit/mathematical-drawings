#include "pch.h"

#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#include <GL/glut.h>

#include <dibuixos.h>

#define O_OCULTO	0
#define O_MOV		1
#define O_NOMOV		2
#define O_FIN		3

enum ESTATES { MOVE_CARS,ESPERE,FIN };

typedef struct CARACTER  {
  GLdouble rad0,rad,arad,x,y,div,scale,anc,anc0,aanc;
  GLdouble ang0,ang,aang;
  int car,modo;
  int counter;
  TIMER counter_titulo;
  } CAR;

static CAR *cars;
static GLdouble cx,cy;
static enum ESTATES state=MOVE_CARS;

static int presentacio_init();
static int presentacio_initgl();
static void presentacio_render();
static void presentacio_finalize();

const DIBUIXO dib_presentacio=
{
    "presentacio",NULL,
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

static int presentacio_init()
{
	size_t size=1;
	char **str=(char **)Titulo;
	
	while (*str)
		size += strlen(*str++);
	if (!(cars=calloc(size,sizeof(CAR))))
		seterror("presentacio_init: %s",strerror(errno));
	memset(cars,0,size*sizeof(CAR));
	
	glutKeyboardFunc(KeyboardFuncEscape);
	
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
	
	rad=min(width,height)/2.0d;
	cx=width/2.0d;
	cy=height/2.0d;
	arad=rad/(GLdouble)((sizeof(Titulo)/sizeof(*Titulo)));
	arad += arad / 2.0d;
	anc=120.0d*rad/348.0d;
	for (;(str2=*str);str++,rad -= arad,anc /= 2.0d)
	{
		ncars=strlen(*str);
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
			cars->rad0=rad;
			cars->rad=0;
			cars->arad=rad/40.0d;
			cars->ang0=beta;
			cars->ang=M_PI*2.0d;
			cars->modo=O_OCULTO;
			cars->aang=alfa;
			cars->anc0=anc;
			cars->anc=1;
			cars->aanc=anc/40.0d;
			calc_car_xy(cars);
			cars->counter=0;
		}
	}
	cars->modo=O_FIN;
	
	return 0;
}

static int presentacio_initgl()
{
	int ret=0;
	
	glexOrthoWindow();
	ret=titulo_initgl(cars);
     
    return ret;
}

static void titulo_render(CAR *cars,unsigned int elapse)
{
	int move_cars=state==MOVE_CARS;
	int done=1;
	GLdouble resul;
	
	for (;cars->modo!=O_FIN;cars++)
	{
		done &= cars->modo==O_NOMOV;
		if (move_cars && cars->modo!=O_NOMOV)
		{
			if (!cars->counter || count_timers(&cars->counter_titulo,170))
			{				
				if (cars->modo==O_MOV)
				{
					cars->rad=min(cars->rad+cars->arad,cars->rad0);
					cars->ang -= cars->aang;
					while (cars->ang<0) cars->ang += 2*M_PI;
					if (cars->rad==cars->rad0 && ((resul=fabs(cars->ang-cars->ang0))==0
			  || resul<=cars->aang))
					{
						cars->anc=cars->anc0;
						cars->ang=cars->ang0;
						cars->modo=O_NOMOV;
					}
				}
				else
				{
					cars->modo=O_MOV;
					move_cars=0;
				}
				cars->anc=min(cars->anc+cars->aanc,cars->anc0);
				calc_car_xy(cars);
				cars->counter=1;
				init_timers(&cars->counter_titulo);
			}	
		}
		glPushMatrix();
		glTranslated(cars->x,cars->y,0);
		glScaled(cars->scale,cars->scale,0);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, cars->car);
		glPopMatrix();
	}
	if (state==MOVE_CARS && done)
		state=ESPERE;
}

static void presentacio_render()
{
	unsigned int elapse=elapse_timers(&timer_dib,1);
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT );	
    glColor3d( 1, 1, 1 );
	titulo_render(cars,elapse);
	glutSwapBuffers();
	/*GLdouble w=glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, 'H');
	GLdouble h=glexStrokeHeight(GLUT_STROKE_MONO_ROMAN);
	GLdouble ang;
	char car='1';
	
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT );	
    glColor3d( 1, 1, 1 );
	glLoadIdentity();
	glPushMatrix();
	glTranslated(0,height-h,0);
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'A');
	glPopMatrix();
	glutSwapBuffers();*/
	 /*
	glPushMatrix();
	glTranslated(width-w,0,0);
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'H');
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,h,0);
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'O');
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,height-h,0);
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'X');
	glPopMatrix();
	for(ang=0;ang<=M_PI;ang += M_PI_4)
	{
		glPushMatrix();
		glTranslated(cx-radT*cos(ang)/2.0d,cy+radT*sin(ang)/2.0d,0);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, car++);
		glPopMatrix();
	}
    glutSwapBuffers();*/
}

static void presentacio_finalize()
{
    FREE(cars);
}