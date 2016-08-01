#include "pch.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glut.h>

#include "dibuixos.h"

static int presentacio_init();
static int presentacio_initgl();
static void prensentacio_update(SDL_Event *e);
static void prensentacio_render();
static void prensentacio_finalize();

const DIBUIXO dib_presentacio=
{ 
    { 0 },
    "presentacio","",
    presentacio_init,
    presentacio_initgl,
    prensentacio_update,
    prensentacio_render,
    prensentacio_finalize
};

const static char *Titulo[]=
{
  "DIBUIXOS",
  "MATEMATICS",
  NULL
};

static void prensentacio_update(SDL_Event *e)
{
    
}

static void prensentacio_render()
{
    
}

static int presentacio_init()
{   
    return 0;
}

static int presentacio_initgl()
{    
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
     
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
     
    return 0;
}

static void prensentacio_finalize()
{
    
}