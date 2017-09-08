#include "pch.h"

#include "dibuixos.h"

char dib_error[128],kPathSeparator,path_data[128];
int width=800,height=600,bpp=-1,fullscreen=0,loop=0,monocpu=0,quitanykey=1,numcpu,numpart=-1;
GLdouble aspectratio;

static DIBUIXODEF *dibuixos[]=
{
	&dib_pi
};

static size_t dibuixos_count=sizeof(dibuixos)/sizeof(*dibuixos);

static SDL_Window *displayWindow;
SDL_Renderer *displayRenderer;
SDL_RendererInfo displayRendererInfo;

TIMER timer_dib,timer_update;

int seterror(char *fmt,...)
{
	va_list args;
	va_start (args, fmt);
  
	vsprintf (dib_error,fmt, args);
	va_end (args);
	
	return RET_ERROR;
}

static int dibuixo_cmp(const void *arg,const void *dib)
{
    return strcmp((const char *) arg,((*(DIBUIXODEF **)dib))->name);
}

static void getpath_data(char *fileexe,int lng)
{	
	memset(path_data,0,sizeof path_data);
	strncpy(path_data,fileexe,lng);
	path_data[lng]=kPathSeparator;
	strcat(path_data,"data");
	
	if (!exist_dir(path_data))
		sprintf(path_data,"%cusr%clib%cshare%cdibuixos",kPathSeparator,kPathSeparator,kPathSeparator,kPathSeparator);
}

static void readfileexe(char *fileexe)
{
	char *sep=strrchr(fileexe, '/');
	int lng;
	
	if (sep==NULL)
		sep=strrchr(fileexe, '\\');		
	kPathSeparator= *sep;
	lng=sep-fileexe;
	getpath_data(fileexe,lng);
}

static DIBUIX *mallocdib(DIBUIXODEF *def)
{
	DIBUIX *dib=(DIBUIX *) malloc(sizeof(DIBUIX)+def->size);
	
	if (dib==NULL)
		seterror(strerror(errno));
	else
	{
		dib->def=def;
		memset(&dib->data,0,def->size);
	}
	
	return dib;
}

int readargs(int argc, char **argv)
{
    char *arg;
    DIBUIXODEF **dib=NULL,*dibl;
	int ret=RET_SUCESS;
	DIBUIX *db;
    
	readfileexe(*argv++);
    while (--argc>0)
    {
        arg=*argv++;
        if (!strcmp(arg,"--help"))
            return RET_EXIT;
        if (!strncmp(arg,"-r",2))
        {
            if (sscanf(arg+2,"%dx%dx%d",&width,&height,&bpp)<2)
            {
                return seterror("%s option error",arg);
            }
        }
        else if (!strcmp(arg,"-f"))
            fullscreen=1;
        else if (!strcmp(arg,"-l"))
            loop=1;
		else if (!strcmp(arg,"--monocpu"))
            monocpu=1;
        else if (!strncmp(arg,"-",1))
        {
            return seterror("%s option error",arg);
        }
        else
        {
			break;
            //dibuixo_arg=*dib;
			
			//return (*dib)->readargs(argc,argv);
        }
    }
		
	if (isnosucess((ret=demo_readargs(--argc,++argv))))
	{		
		return ret;
	}
    
    return ret;
}

void showusage(const char *msgerror)
{
    char msg[2048];
	int i=dibuixos_count;
	DIBUIXODEF **dib=dibuixos;
	char **descptr;
    
    if (msgerror==NULL)
        *msg='\x0';
    else
        sprintf(msg,"error: %s\n\n",msgerror);
    strcat
        (
            msg,
            "dibuixos [options] [dibuixo]\n"
			"\n"
			"\toptions:\n"
			"\t\t--help : show usage\n"
 			"\t\t-r<width>x<height>x[bpp] : resolucion. Default -r800x600\n"
 			"\t\t-f : fullscreen\n"
 			"\t\t-l : play demo in infinite loop\n"
			"\t\t--monocpu : no use paralel algoritms"
 			"\tdibuixo default demo\n"
			"\n"
 			"\tdibuixo:\n"
        );
    for(;i-->0;dib++)
	{		
		for(descptr=(*dib)->description;(*descptr)!=NULL;descptr++)
		{
			strcat(msg,"\t\t");
			strcat(msg,*descptr);
			strcat(msg,"\n");			
		}
	}
	if (msgerror!=NULL)
		fputs(msg,stderr);
    else
        printf("%s", msg);
}

int init()
{
	Uint32 flags=SDL_WINDOW_OPENGL;
	int ret;
		
	numcpu=(monocpu) ? 1 : SDL_GetCPUCount();
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		return seterror( "SDL could not initialize video system! SDL_Error: %s\n", SDL_GetError() );
	}
	if (isnosucess((ret=initmuxtexreservecpu())))
		return ret;
	if (fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;
	SDL_CreateWindowAndRenderer(width, height, flags, &displayWindow, &displayRenderer);
	SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
	/*TODO: Check that we have OpenGL */
    if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 || 
        (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) 
		{
        	/*TODO: Handle this. We have no render surface and not accelerated. */
		}
	if (!fullscreen)
		SDL_SetWindowTitle(displayWindow,"Dibuixos Matematics");
	
	return demo_init();
}
 
static void changeSize(GLsizei w,GLsizei h)
{
	if (h==0)
		h=1;
	glViewport(0,0,w,h);
	aspectratio=(GLfloat)w/(GLfloat)h;
}

int initgl()
{
	changeSize(width,height);
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &glcmaxVertices);
	glexOrthoWindow();
	
	return demo_initgl();
}

void run()
{
	init_timers(&timer_dib);
	init_timers(&timer_update);
	demo_run();
}

void deinit()
{
	deinitmuxtexreservecpu();
	demo_deinit();
	SDL_Quit();
}

int updatex(SDL_Event *ev)
{
	int ret;
	
	elapse_timers(&timer_update,1);
	if ((ret=SDL_PollEvent(ev)))
	{
		switch (ev->type) {
			case SDL_QUIT:
				return RET_CANCEL;
			case SDL_KEYDOWN:
				if (quitanykey)
				{
					SDL_Quit();
					
					return RET_CANCEL;					
				}
				break;
		}
	}
	
	return ret;
}

int update()
{
	SDL_Event ev;
	
	return updatex(&ev);
}

int timestuff(int keyfinish,int rate,void *data, void (*update) (void *data), void (*render) (void *data), int maxtime)
{
	SDL_Event ev;
	int ret;
	TIMER time,time2;
	int dorender=1;
	
	init_timers(&time);
	init_timers(&time2);
	while (!count_timers(&time,maxtime))
	{
		if (isnosucess((ret=updatex(&ev))))
			return ret;
		if (count_timers(&time2,rate))
		{
			if (update!=NULL)
				update(data);
			dorender=1;
		}
		if (dorender && render!=NULL)
		{
			render(data);
			dorender=0;
		}
	}
	
	return RET_SUCESS;
}

