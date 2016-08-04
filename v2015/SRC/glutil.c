#include "pch.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include "dibuixos.h"

GLdouble glScalefact()
{
	float modelview[16];
	
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	
	return modelview[0];
}

void glOrthoWindow()
{
	//Initialize Projection Matrix
     glMatrixMode( GL_PROJECTION );
     glLoadIdentity();
	 gluOrtho2D(0,width,height,0);
     
     //Initialize Modelview Matrix
     glMatrixMode( GL_MODELVIEW );
     glLoadIdentity();
}

GLdouble glStrokeHeight(void *font)
{
	GLdouble h=(font==GLUT_STROKE_MONO_ROMAN || font==GLUT_STROKE_ROMAN) ? 119.05d+33.33d : 119.05d;
	
	return glScalefact()*h*(GLdouble)height/(GLdouble)width;
	
}