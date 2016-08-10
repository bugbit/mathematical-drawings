#ifndef __DIBUIXOS_H__

#define  __DIBUIXOS_H__

#include <GL/gl.h>

#define FREE(p) if (p) {free(p); p=NULL; }
#define min(a,b)((a<b) ? a : b)

#define glexStrokeStrHeight(f,str) glexStrokeHeight(f)
#define glexStrokeMinHeight(f,str) glexStrokeHeight(f)

typedef struct
{
    const char *name;
    const char *menustr;
    int (*init)();
    int (*initgl)();
    void (*render)();
    void (*finalize)();
} DIBUIXO;

typedef struct
{
	unsigned int ticksf;
	unsigned int ticks;
	unsigned int elapsetime;
} TIMER;

extern char dib_error[128];
extern const char autor[],texto_anykey_salir[];
extern int width,height,bpp,fullscreen,loop,demo;
extern GLdouble aspectratio;

extern TIMER timer_dib;
extern DIBUIXO *dibuixo_arg,*dibuixo_act;
extern const DIBUIXO dib_presentacio;

unsigned long get_msec(void);
void init_timers(TIMER *timer);
unsigned int elapse_timers(TIMER *timer,int reset);
int count_timers(TIMER *timer,unsigned int counter);

int seterror(char *fmt,...);
int readargs(int argc, char **argv,int *exit);
void showusage(const char *msgerror);
void KeyboardFuncEscape(unsigned char key,int x, int y);
int setdibuixo(DIBUIXO *dib);
void quit();
void KeyboardFuncAnyKeyExit(unsigned char key,int x, int y);

GLdouble glexScalefact();
void glexOrthoWindow();
GLdouble glexStrokeHeight(void *font);
int glexStrokeStrWidth(void *font,char *str);
int glexStrokeMinWidth(void *font,char *str);
void glutStrokeStr(void *font,char *str);

#endif