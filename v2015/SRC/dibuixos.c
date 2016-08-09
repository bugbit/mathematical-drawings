#include "pch.h"

#include <stdio.h>
#include <error.h>
#include <stdarg.h>

#include <GL/glut.h>

#include "dibuixos.h"

const char 
	autor[]="Programa realitzat per Oscar Hernandez Baño en gcc",
	texto_salir[]="Prem una tecla per sortir";

char dib_error[128];
int width=800,height=600,bpp=-1,fullscreen=0,loop=0,demo=0;

const DIBUIXO *dibuixos[]=
{
    &dib_presentacio
};

TIMER timer_dib;

DIBUIXO *dibuixo_arg,*dibuixo_act;

size_t dibuixos_count=sizeof(dibuixos)/sizeof(*dibuixos);

void showusage(const char *msgerror)
{
    char msg[512];
    
    if (msgerror==NULL)
        *msg='\x0';
    else
        sprintf(msg,"error: %s\n\n",msgerror);
    strcat
        (
            msg,
            "dibuixos [options] [dibuixo]\n\n"
            "options:\n"
            "   --help : show usage\n"
            "   -r<width>x<height>x[bpp] : resolucion. Por defecto es -r800x600\n"
            "   -f : fullscreen"
            "   -l : play demo in infinite loop\n\n"
            "dibuixo:\n"
            "   demo : All of dibuixos"
            "   <dibuixo> : one of dibuixo (see README for more help)"
        );
    
    if (msgerror==NULL)
        printf("%s", msg);
    else
        perror(msg);
}

static int dibuixo_cmp(const void *arg,const void *dib)
{
    return strcmp((const char *) arg,((*(DIBUIXO **)dib))->name);
}

int seterror(char *fmt,...)
{
	va_list args;
	va_start (args, fmt);
  
	vsprintf (dib_error,fmt, args);
	va_end (args);
	
	return -1;
}

int readargs(int argc, char **argv,int *exit)
{
    char *arg;
    *exit=0;
    DIBUIXO **dib;
    
    while(--argc>0)
    {
        arg=*++argv;
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
        else if (!strcmp(arg,"demo"))
            demo=1;
        else
        {
            if (!(dib=lfind(arg,dibuixos,&dibuixos_count,sizeof(DIBUIXO),dibuixo_cmp)))
            {
                return seterror("%s dibuixo not found",arg);
            }
            dibuixo_arg=*dib;
        }
    }
    
    return 0;
}

int setdibuixo(DIBUIXO *dib)
{
    int ret;    
    
    if (dibuixo_act!=NULL)
        dibuixo_act->finalize();
    
    dibuixo_act=dib;
	if (dib)
	{
		if ((ret=dib->init()) || (ret=dib->initgl()))
			perror(dib_error);
		else
		{
			init_timers(&timer_dib);
			glutDisplayFunc(dib->render);
			glutIdleFunc(dib->render);
		}		
	}
    
    return ret;
}