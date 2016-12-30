#include "pch.h"

#include "dibuixos.h"

typedef struct
{
	char *str;
	int at;
	int numdec;
	int (*calcpi)(char *str,int at,int numdec);
} CALCDIGITSPI_THREAD;

static int thread_calcpi(CALCDIGITSPI_THREAD *t)
{
	return t->calcpi(t->str,t->at,t->numdec);
}

int calcpimulticore(char *str,int at,int numdec,int (*calcpi)(char *str,int at,int numdec))
{
	char *str2=str;
	int at2=at,cpus,numpart,n,i,sizepart,sizepart2,*dump,d;
	SDL_Thread **threads=NULL,**threads2;
	CALCDIGITSPI_THREAD *ninedig_t,*ninedig_t2;
	int ret=RET_SUCESS;
	
	cpus=reservemaxnumcpus();
	if (cpus<=0 || (threads=calloc(cpus,sizeof(SDL_Thread *)))!=NULL)
	{	
		if (threads)
			memset(threads,0,cpus*sizeof(SDL_Thread *));
		numpart=cpus+1;
		n=numdec/numpart;
		if (numpart==1)
		{
			sizepart=0;
			sizepart2=numdec;
		}
		else
		{
			d=n%9;
			sizepart=(!d) ? n : n+9-d;
			if (sizepart==0)
				numpart=1;
			sizepart2=numdec-(numpart-1)*sizepart;
		}
		if ((ninedig_t=calloc(numpart-1,sizeof(*ninedig_t))))
		{
			for(i=numpart,ninedig_t2=ninedig_t;i>1;i--,ninedig_t2++)
			{
				ninedig_t2->str=str2;
				ninedig_t2->numdec=sizepart;
				ninedig_t2->at=at2;
				ninedig_t2->calcpi=calcpi;
				at2 += sizepart;
				str2 += sizepart;
			}
			for(i=numpart,threads2=threads,ninedig_t2=ninedig_t;i>1;i--,ninedig_t2++)
			{
				dump=ninedig_t2;
				if ((*threads2++=SDL_CreateThread(thread_calcpi,"thread_ninedigitpi",dump))==NULL)
				{
					ret=seterror("ninedigitpi_calcpi: %s", SDL_GetError());
					break;				
				}
			}
			if (issucess(ret))
			{
				calcpi(str2,at2,sizepart2);
				at2 += sizepart2;
				str2 += sizepart2;
				*str2='\x0';
				for(i=numpart,threads2=threads;i>1;i--,threads2++)
				{
					SDL_WaitThread(*threads2,NULL);
					*threads2=NULL;
				}
			}
			free(ninedig_t);
		}
		
		if (threads)
		{
			for(i=cpus,threads2=threads;i>0;i--,threads2++)
				if (*threads2)
					SDL_DetachThread(*threads2);
			free(threads);
		}
	}
	else
		ret=seterror("ninedigitpi_calcpi: %s", SDL_GetError());			
	dereservenumcpus(cpus);
	
	return ret;
}