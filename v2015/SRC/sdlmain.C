#include "StdAfx.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include "dibuixos.h"

int vi_width=800;
int vi_height=600;
int vi_fullscreen=0;
SDL_Renderer *vi_displayRenderer;
void (*vi_render)();
void (*sceneupdate)();

static int init();
static void loop();
static void render();
static int done();

int SDL_main(int argc, char *argv[])
{
	return dw_main();
}

int dw_main()
{
	int ret=init();

	if (!ret)
	{
		loop();
		ret=done();
	}
	if (ret)
	{
		dwe_showError();
	}

	return 0;
}

static void Display_InitGL()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}

/* function to reset our viewport after a window resize */
static int Display_SetViewport( int width, int height )
{
    /* Height / width ration */
    GLfloat ratio;

    /* Protect against a divide by zero */
    if ( height == 0 ) {
        height = 1;
    }

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

    return 1;
}

static int init()
{
	SDL_Window* displayWindow;
    
    SDL_RendererInfo displayRendererInfo;
	Uint32 flags=SDL_WINDOW_OPENGL;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
        return dwe_setsdlerror();
	if (vi_fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;
    if (SDL_CreateWindowAndRenderer(vi_width, vi_height, flags, &displayWindow, &vi_displayRenderer)<0)
		return dwe_setsdlerror();
    if (SDL_GetRendererInfo(vi_displayRenderer, &displayRendererInfo)<0)
		return dwe_setsdlerror();
    /*TODO: Check that we have OpenGL */
    if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 || 
        (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) 
	{
        /*TODO: Handle this. We have no render surface and not accelerated. */
			return dwe_seterror(DWE_NOOPENGL);
    }
	Display_InitGL();
	Display_SetViewport(vi_width,vi_height);
	vi_render=vi_rendernull;
	sceneupdate=scene1;

   return 0;
   /*
	if (!ret)
		if (!(ret=choosevideo(vi_videos,vi_num,&v)))
		{
			vi_setvideo(v);
			vi_getgrmodes(&g,&num,&alloc);
			if (!(ret=choosegrmode(g,num,&gp)))
			{
				vi_setgrmode(gp);
				if (!(ret=vi_init()))
				{
				}
			}
			if (alloc)
				free(g);
		}


	return ret;
   */
}

static void loop()
{
	SDL_Event ev;
	int exit=0;
	TIMERMS timer;

	timer.last=timer.fist=SDL_GetTicks();
	while(!exit)
	{
		while(SDL_PollEvent(&ev)) 
		{
			switch(ev.type)
			{
				case SDL_QUIT:
					exit=1;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					if (ev.key.keysym.sym==SDLK_ESCAPE)
						exit=1;
					break;
			}
		}
		timer.current=SDL_GetTicks();
		timer.ellapse=timer.current-timer.last;
		timer.total=timer.current-timer.fist;
		timer.last=timer.current;
		sceneupdate(&timer);
		render();
	}
}

static void render()
{
	/* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();

	vi_render();

	SDL_RenderPresent(vi_displayRenderer);
}

void vi_rendernull()
{
}

static int done()
{
	/*int ret=0;

	if (vi_binit)
		ret=vi_close();

	return ret;*/
	return 0;
}

/*
static MEMFREE mf_inicio;
static int mbIsInitVideo=0;

static int init();
static void mensaje_finish();
static void pon_memfree(char *mensaje,MEMFREE *mf);

int _cdecl main(int argc,char *argv[])
{
	if (!init())
	{
		gprintlinexy(10,10,128,"hola mundo");
		getch();
	}
	if (mbIsInitVideo)
		closevideo();
	mensaje_finish();

	return 0;
}

static int init()
{
	int pRet=0;

	getmemfree(&mf_inicio);
	if (!(pRet=checkSystem()))
	{
		initvideo();
		mbIsInitVideo=1;
	}

	return pRet;
}

static void mensaje_finish()
{
	printf("demoscene dibuixos matematics\n\n");
	if (!dwe_isOk())
	{
		printf(dwe_geterrorstr());
	}
	pon_memfree("memoria inicial libre",&mf_inicio);
}

static void pon_memfree(char *mensaje,MEMFREE *mf)
{
	if (mf->calc)
	{
		printf("%s dosmemfree = %lu bytes\n",mensaje,mf->dosmemfree);
	}
}

*/