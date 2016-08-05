#include "pch.h"

#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#include <GL/glut.h>

#include <dibuixos.h>

#define O_NOMOV		0
#define O_MOV		1
#define O_FIN		2

enum ESTATES { MOVE_CARS,ESPERE,FIN };

typedef struct CARACTER  {
  GLdouble rad0,rad,x,y,div,scale,anc,anc0;
  GLdouble ang0,ang,aang;
  GLdouble radms,ancms;
  int car,modo;
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
	cars->y=cy+cars->rad*sin(cars->ang);
	cars->scale=cars->anc/cars->div;
}

static int titulo_initgl(CAR *cars)
{
	GLdouble rad,arad,divx,divy,div,w,h,anc,alfa,beta,radms,ancms;
	int ncars;
	char **str=(char **)Titulo;
	char *str2;
	
	rad=min(width,height)/2.0d;
	cx=width/2.0d;
	cy=height/2.0d;
	arad=rad/(GLdouble)((sizeof(Titulo)/sizeof(*Titulo))-1);
	for (;(str2=*str);str++,rad -= arad)
	{
		ncars=strlen(*str);
		divx=glexStrokeMinWidth(GLUT_STROKE_MONO_ROMAN,str2);
		divy=glexStrokeMinHeight(GLUT_STROKE_MONO_ROMAN,str2);
		div=min(divx,divy);
		alfa=M_PI/(GLdouble) ncars;
		w=rad*cos(alfa);
		h=rad*sin(alfa);
		beta=0;
		anc=min(w,h);
		ancms=anc/20000.0d;
		radms=rad/20000.0d;
		for(;*str2;str2++,cars++,beta += alfa)
		{
			cars->car=*str2;
			cars->div=div;
			cars->rad0=rad;
			cars->ang0=beta;
			cars->ang=M_PI*2.0d;
			cars->rad=0;
			cars->modo=O_MOV;
			cars->aang=alfa;
			cars->anc0=anc;
			cars->anc=1;
			cars->ancms=ancms;
			cars->radms=radms;
			calc_car_xy(cars);
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
	int done=1;
	
	for (;cars->modo!=O_FIN;cars++)
	{
		glPushMatrix();
		glTranslated(cars->x,cars->y,0);
		glScaled(cars->scale,cars->scale,0);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, cars->car);
		glPopMatrix();
		if (state==MOVE_CARS)
			if (cars->modo==O_MOV)
			{
				done=0;
				cars->rad=min(cars->rad+cars->radms*(GLdouble)elapse,cars->rad0);
				cars->ang -= cars->aang*(GLdouble)elapse/10000.0d;
				while (cars->ang<0) cars->ang += 2*M_PI;
				cars->anc=min(cars->anc+cars->ancms*(GLdouble)elapse,cars->anc0);
				if (cars->rad==cars->rad0)
				{
					if (cars->ang>cars->ang0)
					{
						cars->ang=cars->ang0;
						cars->modo=O_NOMOV;						
					}
				}
				calc_car_xy(cars);
			}
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
	glTranslated(0,0,0);
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'A');
	glPopMatrix();
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
    
}