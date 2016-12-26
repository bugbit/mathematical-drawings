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
	
	return RET_ERROR;
}

static int dibuixo_cmp(const void *arg,const void *dib)
{
    return strcmp((const char *) arg,((*(DIBUIXOS **)dib))->name);
}

int readargs(int argc, char **argv)
{
    char *arg;
    DIBUIXOS **dib=NULL,*dibl;
	int ret=RET_SUCESS;
    
    while (--argc>0)
    {
        arg=*++argv;
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
