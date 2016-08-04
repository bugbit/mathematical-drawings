#include "pch.h"

#include <math.h>
#include <GL/glut.h>

#include <dibuixos.h>

static GLdouble radT;
static GLdouble cx,cy;

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
	glutKeyboardFunc(KeyboardFuncEscape);
	
    return 0;
}

static int presentacio_initgl()
{
	GLdouble arad;
	
	glOrthoWindow();
	radT=((width<height) ? (GLdouble)width : (GLdouble)height)/2.0d;
	cx=width/2.0d;
	cy=height/2.0d;
	arad=radT/(GLdouble)((sizeof(Titulo)/sizeof(*Titulo))-1);
     
    return 0;
}

static void presentacio_render()
{
	GLdouble w=glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, 'H');
	GLdouble h=glStrokeHeight(GLUT_STROKE_MONO_ROMAN);
	GLdouble ang;
	
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT );	
    glColor3d( 1, 1, 1 );
	glPushMatrix();
	glTranslated(0,0,0);
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'H');
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
	for(ang=0;ang<180;ang += 2)
	{
		glPushMatrix();
		glTranslated(cx,cy,0);
		glRotated(ang,1,1,0);
		glTranslated(radT/8.0,0,0);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, 'S');
		glPopMatrix();
	}
    glutSwapBuffers();
}

static void presentacio_finalize()
{
    
}