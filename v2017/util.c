#include "pch.h"

#include "dibuixos.h"

static SDL_mutex *mutexreservecpu;
static int freenumcpu;

int exist_dir(char *pathname)
{
	struct stat sb;

	return (stat(pathname, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void getfiledata(char *filedest,char *filename)
{
	sprintf(filedest,"%s%c%s",path_data,kPathSeparator,filename);
}

int initmuxtexreservecpu()
{
	mutexreservecpu=SDL_CreateMutex();
	if (mutexreservecpu==NULL)
		return seterror("Don't can create mutexreservecpu: %s", SDL_GetError());
		
	freenumcpu=numcpu-1;
	
	return RET_SUCESS;
}

void deinitmuxtexreservecpu()
{
	if (mutexreservecpu!=NULL)
		SDL_DestroyMutex(mutexreservecpu);
}

int reservenumcpus(int numcpus,int force)
{
	int cpu=0;
	
	if (SDL_LockMutex(mutexreservecpu)==0)
	{
		if (force || numcpus<=freenumcpu)
		{
			cpu=numcpus;
			freenumcpu -= numcpus;
		}
		
		SDL_UnlockMutex(mutexreservecpu);
	}
	
	return cpu;	
}

int reservemaxnumcpus()
{
	int cpu=0;
	
	if (SDL_LockMutex(mutexreservecpu)==0)
	{
		if (freenumcpu>0)
		{
			cpu=freenumcpu;
			freenumcpu=0;
		}
		
		SDL_UnlockMutex(mutexreservecpu);
	}
	
	return cpu;	
}

void dereservenumcpus(int numcpus)
{
	if (SDL_LockMutex(mutexreservecpu)==0)
	{
		freenumcpu += numcpus;
		
		SDL_UnlockMutex(mutexreservecpu);
	}
}
