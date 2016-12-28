#include "pch.h"

#include "dibuixos.h"

typedef struct
{
	int demo_part;
	Mix_Music *music;
} Demo;

static int demo_readargs(Demo *data,int argc, char **argv);
static int demo_init(Demo *data);
static int demo_initgl(Demo *data);
static void demo_run(Demo *data);
static void demo_deinit(Demo *data);

DIBUIXODEF dib_demo=
{
	"demo",sizeof(Demo),demo_readargs,demo_init,demo_initgl,demo_run,demo_deinit,
	{ "demo [part] default 0",NULL}
};

static int demo_readargs(Demo *data,int argc, char **argv)
{
	if (argc>1)
		return seterror("expect one argument");
		
	if (argc==1)
	{
		if (sscanf(*argv,"%d",&data->demo_part)==0)
			return seterror("expect number as argument");
		
		return RET_SUCESS;
	}
	
	data->demo_part=0;
	
	return RET_SUCESS;
}

static int demo_init(Demo *data)
{
	int flags = MIX_INIT_MP3;
	char filemp3[512];
	 
	if (SDL_Init(SDL_INIT_AUDIO) < 0) 
        return seterror( "SDL could not initialize sound system! SDL_Error: %s\n", SDL_GetError() );
	
	if (Mix_Init(flags)<0)
		return seterror( "SDL could not initialize sound system! SDL_Error: %s\n", SDL_GetError() );
		
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	getfiledata(filemp3,"demo.mp3");
	if ((data->music = Mix_LoadMUS(filemp3))==NULL)
		return seterror("error %s\n",Mix_GetError());
	
	return RET_SUCESS;
}

static int demo_initgl(Demo *data)
{
	return RET_SUCESS;
}

static void demo_run(Demo *data)
{
	Mix_PlayMusic(data->music, 1);
	while(update()!=RET_CANCEL)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3d(1.0, 0.0, 0.0);
		glRasterPos2f(0, 13);
		glutBitmapString(GLUT_BITMAP_8_BY_13,"31415927\nhola\n");
		//glutBitmapString(GLUT_BITMAP_8_BY_13,"31415927");
		glxswap();		
	}
	//SDL_Delay(5000);
}

static void demo_deinit(Demo *data)
{
	if (data->music!=NULL)
		Mix_FreeMusic(data->music);
}