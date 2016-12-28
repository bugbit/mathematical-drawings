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

char *glexBitmapMakeCars(int width,int height)
{
	char *cars=malloc((width+1)*height+1),*c;
	
	if (cars==NULL)
	{
		seterrorno();
		
		return NULL;
	}
	
	for(c=cars;height-->0;)
	{
		memset(c,' ',width);
		c += width;
		*c++='\n';
	}
	*c++='\x0';
	
	return cars;
}

char *glexBitmapCarsScrollUp(char *str)
{
	int size=strlen(str);
	char *newline=strchr(str,'\n')+1;
	int n=newline-str;
	int n2=size-n;
	char *last=str+n2;
	
	/*
	 * 123\n
	 * 2456\n
	 * 
	 * 2456\n
	 *    \n
	 * 
	 * size=9
	 * newline=3+1=4
	 * n=4
	 * n2=9-4=5
	 * 
	 */
	memcpy(str,newline,n2);
	memset(last,' ',n);
	
	return last;
}