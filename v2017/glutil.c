#include "pch.h"

#include "dibuixos.h"

GLint glcmaxVertices;

void glexOrthoW()
{	
     glLoadIdentity();
	 gluOrtho2D(0,width,0,height);
}

void glexOrthoWindow()
{
	//Initialize Projection Matrix
     glMatrixMode( GL_PROJECTION );
	 glexOrthoW();
     
     //Initialize Modelview Matrix
     glMatrixMode( GL_MODELVIEW );
     glLoadIdentity();
}