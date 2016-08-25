#include "pch.h"

#include <math.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "dibuixos.h"

typedef struct _STACK
{
	unsigned int ndx;
	unsigned int iteracion;
	short nlado;
} STACK;

// Ejemplo http://interactivepython.org/runestone/static/pythonds/Recursion/pythondsSierpinskiTriangle.html

//static GLdouble s_triangle2[2*3];
static GLdouble *s_triangle;
static GLdouble *s_triangle_colores;
static GLuint s_triangle_iter;
static GLuint s_triangle_count;
static GLuint s_triangle_ndraw;
static GLdouble s_point[2];
static GLdouble s_line_len,s_line_rad;
static GLdouble s_line_ang;
static GLdouble s_line_color[3];
static int s_line_tri_ndx;
static int s_line_tri_count;
static STACK *s_stack;
static int s_stack_ndx;
static int s_fin=0;

static int sierpinski_init(void *init_params);
static int sierpinski_initgl(void *init_params);
static void sierpinski_render();
static void sierpinski_finalize();

const DIBUIXO dib_sierpinski=
{
	"sierpinski",
	"Triangle de sierpinski",
	NULL,
	sierpinski_init,
	sierpinski_initgl,
	sierpinski_render,
	sierpinski_finalize
};

static void setline(GLdouble s[],int ndx)
{
	int ndx0=(ndx>0) ? ndx-2 : 2*2;
	GLdouble x=s[ndx]-s[ndx0];
	GLdouble y=s[ndx+1]-s[ndx0+1];
	
	s_line_tri_ndx=ndx;
	s_point[0]=s[ndx0];
	s_point[1]=s[ndx0+1];
	s_line_len=sqrt(x*x+y*y);	
	s_line_ang=((y!=0.0d || x>=0.0d)) ? asin(y/s_line_len) : M_PI;
	s_line_rad=0;
	if (ndx==2)
	{
		s_line_color[0]=x/width;
		s_line_color[1]=y/height;
		s_line_color[2]=s_line_ang/M_PI_2;	
	}
}

static void sierpinski_func
(
	GLdouble x0,GLdouble y0,
	GLdouble x1,GLdouble y1,
	GLdouble x2,GLdouble y2,
	int iter
)
{
	GLdouble *s=s_triangle+(s_triangle_count);
	GLdouble *c=s_triangle_colores+(s_triangle_count);
	STACK *stk=s_stack+(++s_stack_ndx);
	int i;
	
	s[0]=x0;
	s[1]=y0;
	s[2]=x1;
	s[3]=y1;
	s[4]=x2;
	s[5]=y2;
	stk->iteracion=iter;
	stk->ndx=s_triangle_count;
	stk->nlado=-1;
	setline(s,2);
	for (i=3;i-->0;c += 3)
		memcpy(c,s_line_color,3*sizeof(*s_triangle_colores));
	s_triangle_count+=2*3;
	s_line_tri_count=0;
}

static int buildtrianglesmaxinter()
{
	int i=32*log(2)/log(3);
	unsigned int n;
	void *ptr;
	void *ptr2;
	
	ptr=ptr2=NULL;
	do
	{
		n=pow(3,i);
		if ((ptr=calloc(2*3*n,sizeof(*s_triangle))) && (ptr2=calloc(2*3*n,sizeof(*s_triangle))) && (s_stack=calloc(i,sizeof(*s_stack))))
			break;
		FREE(ptr);
		FREE(ptr2);
	} while(--i>0);
	if (ptr==NULL)
		return seterror("buildtrianglesmaxinter: %s",strerror(errno));
	
	s_triangle_iter=i-1;
	s_triangle=ptr;
	s_triangle_colores=ptr2;
	s_triangle_ndraw=s_triangle_count=0;
	s_stack_ndx=-1;
		
	return 0;
}

static int sierpinski_init(void *init_params)
{
	if (buildtrianglesmaxinter())
		return -1;
		
	if (!demo)
		waitanykey=1;
	sierpinski_func(0,0,(GLdouble) width/2.0d,height,width,0,s_triangle_iter);
	/*s_triangle[0]=0;
	s_triangle[1]=0;
	s_triangle[2]=(GLdouble) width/2.0d;
	s_triangle[3]=height;
	s_triangle[4]=width;
	s_triangle[5]=0;
	setline(s_triangle,2);*/
	
	return 0;
}

static int sierpinski_initgl(void *init_params)
{
	glexOrthoWindow();
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	//glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	 
	return 0;
}

static void sierpinski_update(unsigned int elapse)
{	
	STACK *stk;
	GLdouble *s;
	int i01,i02,i11,i12;
	
	s_line_rad += (GLdouble) elapse/0.5d;
	if (s_line_rad>s_line_len)
	{
		if (s_line_tri_count++<2)
			setline(s_triangle+(3*2*s_triangle_ndraw),(s_line_tri_ndx+2) % (2*3));
		else
		{
			s_triangle_ndraw++;
			for(;!s_fin;)
			{
				if (s_stack_ndx<0)
				{
					s_fin=1;
					
					return;
				}
				stk=s_stack+s_stack_ndx;
				if (stk->iteracion<=0)
				{
					s_stack_ndx--;
					continue;
				}
				s=s_triangle+stk->ndx;
				switch(++(stk->nlado))
				{
					case 0:	// p[0], mid[p[0],p[1]], mid[p[0],p[2]]
						i01=0;
						i02=1;
						i11=0;
						i12=2;
						break;
					case 1:	// p[1], mid[p[0],p[1]], mid[p[1],p[2]]
						i01=0;
						i02=1;
						i11=1;
						i12=2;
						break;
					case 2:	// p[2], mid[p[2],p[1]], mid[p[0],p[2]]
						i01=2;
						i02=1;
						i11=0;
						i12=2;
						break;
					default:
						s_stack_ndx--;						
						continue;
				}
				sierpinski_func
				(
					s[2*stk->nlado],s[2*stk->nlado+1],
					(s[2*i01]+s[2*i02])/2.0d,(s[2*i01+1]+s[2*i02+1])/2.0d,
					(s[2*i11]+s[2*i12])/2.0d,(s[2*i11+1]+s[2*i12+1])/2.0d,
					stk->iteracion-1
				);
				
				return;
			}
		}
	}
}

static void sierpinski_render()
{
	unsigned int elapse=elapse_timers(&timer_dib,1);
	int i;
	GLdouble *s;
	GLdouble *c;
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (s_triangle_ndraw>0 && glcmaxVertices>0)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(2, GL_DOUBLE, 0, s_triangle);
		glColorPointer(3, GL_DOUBLE, 0, s_triangle_colores);
		glDrawArrays(GL_TRIANGLES, 0, 3*min(s_triangle_ndraw,glcmaxVertices));
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
	if (s_triangle_ndraw>glcmaxVertices)
	{
		glBegin(GL_TRIANGLES);
		for
		(
			s=s_triangle+2*3*glcmaxVertices,c=s_triangle_colores+2*3*glcmaxVertices,
			i=2*3*(s_triangle_ndraw-glcmaxVertices),i-->0;s += 2,c += 2;
		)
		{
			glVertex2dv(s);
			glColor3dv(c);
		}
		glEnd();
	}
	if (!s_fin)
	{
		glColor3dv(s_line_color);
		glBegin(GL_LINES);
		glVertex2dv(s_point);
		glVertex2d(s_point[0]+s_line_rad*cos(s_line_ang),s_point[1]+s_line_rad*sin(s_line_ang));
		if (s_line_tri_count>0)
		{
			for(s=s_triangle+s_stack[s_stack_ndx].ndx,i=s_line_tri_count;i-->0;)
			{
				glVertex2dv(s);
				s += 2;
				glVertex2dv(s);
			}
		}
		glEnd();		
	}
	if (!demo)
	{
		WriteWaitKey();
	}
	glutSwapBuffers();
	if (!s_fin)
		sierpinski_update(elapse);
}

static void sierpinski_finalize()
{
	FREE(s_triangle);
	FREE(s_stack);
}
