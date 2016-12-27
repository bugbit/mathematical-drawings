#include "pch.h"

#include "dibuixos.h"

char dib_error[128],kPathSeparator,path_data[128];
int width=800,height=600,bpp=-1,fullscreen=0,loop=0;
DIBUIXOS *dibuixo_arg;

static char kPathDataShare[]="/usr/lib/shared/dibuixos";

static DIBUIXOS *dibuixos[]=
{
	&dib_demo
};

static size_t dibuixos_count=sizeof(dibuixos)/sizeof(*dibuixos);

static SDL_Window *displayWindow;
SDL_Renderer *displayRenderer;
SDL_RendererInfo displayRendererInfo;

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
    return strcmp((const char *) arg,((*(DIBUIXOS **)dib))->name);
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

int readargs(int argc, char **argv)
{
    char *arg;
    DIBUIXOS **dib=NULL,*dibl;
	int ret=RET_SUCESS;
    
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
        else if (!strncmp(arg,"-",1))
        {
            return seterror("%s option error",arg);
        }
        else
        {
            if (!(dib=lfind(arg,dibuixos,&dibuixos_count,sizeof(*dibuixos),dibuixo_cmp)))
            {
                return seterror("%s dibuixo not found",arg);
            }
			
			break;
            //dibuixo_arg=*dib;
			
			//return (*dib)->readargs(argc,argv);
        }
    }
	dibl=(dib==NULL) ? &dib_demo : *dib;
	if (isnosucess((ret=dibl->readargs(--argc,++argv))))
		return ret;
		
	dibuixo_arg=dibl;
    
    return ret;
}

void showusage(const char *msgerror)
{
    char msg[2048];
	int i=dibuixos_count;
	DIBUIXOS **dib=dibuixos;
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
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		return seterror( "SDL could not initialize video system! SDL_Error: %s\n", SDL_GetError() );
	}
	if (fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;
	SDL_CreateWindowAndRenderer(width, height, flags, &displayWindow, &displayRenderer);
	SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
	/*TODO: Check that we have OpenGL */
    if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 || 
        (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
        /*TODO: Handle this. We have no render surface and not accelerated. */
}
	if (!fullscreen)
		SDL_SetWindowTitle(displayWindow,"Dibuixos Matematics");
	
	return dibuixo_arg->init();
}

int initgl()
{
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &glcmaxVertices);
	glexOrthoWindow();
	
	return dibuixo_arg->initgl();
}

void deinit()
{
	dibuixo_arg->deinit();
	SDL_Quit();
}