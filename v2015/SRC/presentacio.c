#include "pch.h"

#include <SDL.h>

#include <dibuixos.h>

static int presentacio_init();
static int presentacio_initgl();
static void presentacio_update(SDL_Event *e);
static void presentacio_render();
static void presentacio_finalize();

const DIBUIXO dib_presentacio=
{
    "presentacio",NULL,
    presentacio_init,
    presentacio_initgl,
    presentacio_update,
    presentacio_render,
    presentacio_finalize
};

static int presentacio_init()
{
    return 0;
}

static int presentacio_initgl()
{
    return 0;
}

static void presentacio_update(SDL_Event *e)
{    
}

static void presentacio_render()
{
    
}

static void presentacio_finalize()
{
    
}