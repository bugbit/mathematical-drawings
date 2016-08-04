#ifndef __DIBUIXOS_H__

#define  __DIBUIXOS_H__

#include <GL/gl.h>

typedef struct
{
    const char *name;
    const char *menustr;
    int (*init)();
    int (*initgl)();
    void (*render)();
    void (*finalize)();
} DIBUIXO;

extern char dib_error[128];
extern int width,height,bpp,fullscreen,loop,demo;
extern GLdouble aspectratio;

extern DIBUIXO *dibuixo_arg,*dibuixo_act;
extern const DIBUIXO dib_presentacio;

int readargs(int argc, char **argv,int *exit);
void showusage(const char *msgerror);
void KeyboardFuncEscape(unsigned char key,int x, int y);
int setdibuixo(DIBUIXO *dib);

GLdouble glScalefact();
void glOrthoWindow();
GLdouble glStrokeHeight(void *font);

#endif