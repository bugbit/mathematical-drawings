#ifndef __DIBUIXOS_H__

#define  __DIBUIXOS_H__

#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define	RET_SUCESS		0
#define	RET_ERROR		-1
#define	RET_EXIT		-2
#define	RET_CANCEL		-3

#define	issucess(r)		(r>=RET_SUCESS)
#define	isnosucess(r)	(r<RET_SUCESS)
#define FREE(p) if (p) {free(p); p=NULL; }
#define glxswap()	SDL_RenderPresent(displayRenderer)
#define getfccarsptr(fc)	&fc->cars
#define	seterrorno()	seterror(strerror(errno))
#define lpi_isuntilat(lpi)	(lpi->at>=lpi->untilat)

#ifndef min
#define min(a,b)((a<b) ? a : b)
#endif

typedef struct
{
	unsigned int ticksf;
	unsigned int ticks;
	unsigned int elapsetime;
} TIMER;

// main

extern char dib_error[128],kPathSeparator,path_data[128];
extern int width,height,bpp,fullscreen,loop,monocpu,quitanykey,numcpu,numpart,
w8c,h13c;
extern GLdouble aspectratio;
extern SDL_Renderer *displayRenderer;
extern SDL_RendererInfo displayRendererInfo;
extern TIMER timer_dib,timer_update;

int seterror(char *fmt,...);
int readargs(int argc, char **argv);
void showusage(const char *msgerror);
int init();
int initgl();
void run();
void deinit();
int updatex(SDL_Event *ev);
int update();
int timestuff(int keyfinish,int rate,void *data, void (*update) (void *data), void (*render) (void *data), int maxtime);

// util
int exist_dir(char *dir);
void getfiledata(char *filedest,char *filename);
int initmuxtexreservecpu();
void deinitmuxtexreservecpu();
int reservenumcpus(int numcpus,int force);
int reservemaxnumcpus();
void dereservenumcpus(int numcpus);

int demo_readargs(int argc, char **argv);
int demo_init();
int demo_init();
int demo_initgl();
void demo_run();
void demo_deinit();

// glutil

extern GLint glcmaxVertices;

void glexOrthoW();
void glexOrthoWindow();
char *glexBitmapMakeCars(int width,int height);
char *glexBitmapCarsScrollUp(char *str);

// math

int ninedigitsofpi(int n);
int ninedigitpi_calcpi(char *str,int at,int numdec);
int fastpi(char *str,int at,int numdec);
int calcpimulticore(char *str,int at,int numdec,int (*calcpi)(char *str,int at,int numdec));

// timer

void init_timers(TIMER *timer);
unsigned int elapse_timers(TIMER *timer,int reset);
int count_timers(TIMER *timer,unsigned int counter);

// pi

void lpi_init();
void lpi_deinit();
int lpi_splash();

// freeglut

#   define  GLUT_STROKE_ROMAN               ((void *)0x0000)
#   define  GLUT_STROKE_MONO_ROMAN          ((void *)0x0001)
#   define  GLUT_BITMAP_9_BY_15             ((void *)0x0002)
#   define  GLUT_BITMAP_8_BY_13             ((void *)0x0003)
#   define  GLUT_BITMAP_TIMES_ROMAN_10      ((void *)0x0004)
#   define  GLUT_BITMAP_TIMES_ROMAN_24      ((void *)0x0005)
#   define  GLUT_BITMAP_HELVETICA_10        ((void *)0x0006)
#   define  GLUT_BITMAP_HELVETICA_12        ((void *)0x0007)
#   define  GLUT_BITMAP_HELVETICA_18        ((void *)0x0008)

/*
 * Font stuff, see fg_font.c
 */
void     glutBitmapCharacter( void* font, int character );
int      glutBitmapWidth( void* font, int character );
void     glutStrokeCharacter( void* font, int character );
int      glutStrokeWidth( void* font, int character );
GLfloat  glutStrokeWidthf( void* font, int character ); /* GLUT 3.8 */
int      glutBitmapLength( void* font, const unsigned char* string );
int      glutStrokeLength( void* font, const unsigned char* string );
GLfloat  glutStrokeLengthf( void* font, const unsigned char *string ); /* GLUT 3.8 */

int     glutBitmapHeight( void* font );
GLfloat glutStrokeHeight( void* font );
void    glutBitmapString( void* font, const unsigned char *string );
void    glutStrokeString( void* font, const unsigned char *string );


#endif
