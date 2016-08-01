#ifndef __DIBUIXOS_H__

#define  __DIBUIXOS_H__

#include <SDL.h>

typedef struct
{
    struct
    {
        unsigned UseKeyEsc:1;
    } flags;
    const char *name;
    const char *menustr;
    int (*init)();
    int (*initgl)();
    void (*update)(SDL_Event *e);
    void (*render)();
    void (*finalize)();
} DIBUIXO;

extern int width,height,bpp,fullscreen,loop,demo;

extern SDL_Window *window;
extern SDL_GLContext *glcontext;
extern void (*update)(SDL_Event *e);
extern void (*render)();

extern DIBUIXO *dibuixo_arg,*dibuixo_act;
extern const DIBUIXO dib_presentacio;

int readargs(int argc, char **argv,int *exit);
void showusage(const char *msgerror);
int setdibuixo(DIBUIXO *dib);

#endif