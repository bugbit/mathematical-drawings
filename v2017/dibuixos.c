#include "pch.h"

#include "dibuixos.h"

char dib_error[128];
int width=800,height=600,bpp=-1,fullscreen=0,loop=0;
DIBUIXOS *dibuixo_arg;

static DIBUIXOS *dibuixos[]=
{
	&dib_demo
};

static size_t dibuixos_count=sizeof(dibuixos)/sizeof(*dibuixos);

int seterror(char *fmt,...)
{
	va_list args;
	va_start (args, fmt);
  
	vsprintf (dib_error,fmt, args);
	va_end (args);
	
	return -1;
}

static int dibuixo_cmp(const void *arg,const void *dib)
{
    return strcmp((const char *) arg,((*(DIBUIXOS **)dib))->name);
}

int readargs(int argc, char **argv,int *exit)
{
    char *arg;
    *exit=0;
    DIBUIXOS **dib=NULL,*dibl;
    
    for(;argc>0;argc--,argv++)
    {
        arg=*argv;
        if (!strcmp(arg,"--help"))
        {
            *exit=1;
            
            return 0;
        }
        if (!strncmp(arg,"-r",2))
        {
            if (sscanf(arg,"%dx%dx%d",&width,&height,&bpp)<2)
            {
                return seterror("%s option error",arg);
            }
        }
        else if (!strcmp(arg,"-r"))
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
	if (dibl->readargs(argc,argv))
		return -1;
		
	dibuixo_arg=dibl;
    
    return 0;
}
