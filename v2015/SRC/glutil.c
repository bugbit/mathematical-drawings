#include "pch.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include "dibuixos.h"

GLdouble glexScalefact()
{
	float modelview[16];
	
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	
	return modelview[0];
}

void glexOrthoWindow()
{
	//Initialize Projection Matrix
     glMatrixMode( GL_PROJECTION );
     glLoadIdentity();
	 gluOrtho2D(0,width,0,height);
     
     //Initialize Modelview Matrix
     glMatrixMode( GL_MODELVIEW );
     glLoadIdentity();
}

GLdouble glexStrokeHeight(void *font)
{
	GLdouble h=(font==GLUT_STROKE_MONO_ROMAN || font==GLUT_STROKE_ROMAN) ? 119.05d+33.33d : 119.05d;
	
	return glexScalefact()*h*(GLdouble)height/(GLdouble)width;
	
}

int glexStrokeStrWidth(void *font,char *str)
{
	int w=0;
	
	while (*str)
		w+= glutStrokeWidth(font,*str++);
		
		return w;
}

int glexStrokeMinWidth(void *font,char *str)
{
	int w=999;
	
	while (*str)
		w= min(w,glutStrokeWidth(font,*str++));
		
	return w;
}