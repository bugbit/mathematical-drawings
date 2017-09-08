#include "pch.h"

#include "dibuixos.h"

static Mix_Music *music;

int demo_readargs(int argc, char **argv)
{
	if (argc>1)
		return seterror("expect one argument");
		
	if (argc==1)
	{
		if (sscanf(*argv,"%d",&numpart)==0)
			return seterror("expect number as argument");
		
		return RET_SUCESS;
	}
	
	return RET_SUCESS;
}

int demo_init()
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

int demo_initgl()
{
	return RET_SUCESS;
}

void demo_run()
{
	Mix_PlayMusic(music, 1);
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

void demo_deinit()
{
	if (music!=NULL)
		Mix_FreeMusic(music);
}