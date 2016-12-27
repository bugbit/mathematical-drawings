#include "pch.h"

#include "dibuixos.h"

static int demo_part;
static Mix_Music *music;

static int demo_readargs(int argc, char **argv);
static int demo_init();
static int demo_initgl();
static void demo_run();
static void demo_deinit();

DIBUIXOS dib_demo=
{
	"demo",demo_readargs,demo_init,demo_initgl,demo_run,demo_deinit,
	{ "demo [part] default 0",NULL}
};

static int demo_readargs(int argc, char **argv)
{
	if (argc>1)
		return seterror("expect one argument");
		
	if (argc==1)
	{
		if (sscanf(*argv,"%d",&demo_part)==0)
			return seterror("expect number as argument");
		
		return RET_SUCESS;
	}
	
	demo_part=0;
	
	return RET_SUCESS;
}

static int demo_init()
{
	int flags = MIX_INIT_MP3;
	char filemp3[512];
	 
	if (SDL_Init(SDL_INIT_AUDIO) < 0) 
        return seterror( "SDL could not initialize sound system! SDL_Error: %s\n", SDL_GetError() );
	
	if (Mix_Init(flags)<0)
		return seterror( "SDL could not initialize sound system! SDL_Error: %s\n", SDL_GetError() );
		
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	getfiledata(filemp3,"demo.mp3");
	if ((music = Mix_LoadMUS(filemp3))==NULL)
		return seterror("error %s\n",Mix_GetError());
	
	return RET_SUCESS;
}

static int demo_initgl()
{
	return RET_SUCESS;
}

static void demo_run()
{
	Mix_PlayMusic(music, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1.0, 0.0, 0.0);
	glRasterPos2f(0, height-13);
	glutBitmapString(GLUT_BITMAP_8_BY_13,"31415927");
	glutBitmapString(GLUT_BITMAP_8_BY_13,"31415927");
	glswap();
	SDL_Delay(5000);
}

static void demo_deinit()
{
	if (music!=NULL)
		Mix_FreeMusic(music);
}