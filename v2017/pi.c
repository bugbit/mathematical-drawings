#include "pch.h"

#include "dibuixos.h"

typedef struct
{
	LISTDECIMALPI listpi;
} Pi;

static int pi_readargs(Pi *data,int argc, char **argv);
static int pi_init(Pi *data);
static int pi_initgl(Pi *data);
static void pi_run(Pi *data);
static void pi_deinit(Pi *data);

DIBUIXODEF dib_pi=
{
	"pi",sizeof(Pi),pi_readargs,pi_init,pi_initgl,pi_run,pi_deinit,
	{
		"show all decimals pi"
	}
};

int lpi_make(LISTDECIMALPI *lpi)
{
	int w=width/8,h=height/9;
	
	lpi->thread=NULL;
	lpi->threads=NULL;
	lpi->ninedig_t=NULL;
	lpi->mutexadd=lpi->muteunitat=NULL;
	lpi->condunitat=NULL;
	lpi->nummaxthread=numcpu+1;
	if ((lpi->cars=glexBitmapMakeCars(w,h))==NULL)
		return RET_ERROR;
	if ((lpi->threads=calloc(lpi->nummaxthread,sizeof(SDL_Thread *)))==NULL)
		return seterrorno();
	memset(lpi->threads,0,lpi->nummaxthread*sizeof(SDL_Thread *));
	if ((lpi->ninedig_t=calloc(lpi->nummaxthread,sizeof(int)))==NULL)
		return seterrorno();
	if ((lpi->mutexadd=SDL_CreateMutex())==NULL)
		return seterror("Don't can create mutexadd: %s", SDL_GetError());
	if ((lpi->muteunitat=SDL_CreateMutex())==NULL)
		return seterror("Don't can create muteunitat: %s", SDL_GetError());
	if ((lpi->condunitat=SDL_CreateCond())==NULL)
		return seterror("Don't can create condunitat: %s", SDL_GetError());
	lpi->cars_act=lpi->cars;
	lpi->width=w;
	lpi->height=h;
	lpi->position=-1;
	lpi->untilat=0;
		
	return RET_SUCESS;
}

static void freelistninedigitsofpi(LISTDECIMALPI *lpi)
{
	struct _LISTNINEPIS *ptr=lpi->first,*ptr2;
	
	while(ptr!=NULL)
	{
		ptr2=ptr;
		ptr=ptr->next;
		free(ptr2);
	}
}

void lpi_destroy(LISTDECIMALPI *lpi)
{
	if (!lpi->finish)
		lpi_donethread(lpi,0);
	if (lpi->mutexadd!=NULL)
		SDL_DestroyMutex(lpi->mutexadd);
	if (lpi->muteunitat!=NULL)
		SDL_DestroyMutex(lpi->muteunitat);
	if (lpi->condunitat!=NULL)
		SDL_DestroyCond(lpi->condunitat);
	FREE(lpi->cars);
	FREE(lpi->threads);
	FREE(lpi->ninedig_t);
	freelistninedigitsofpi(lpi);
}

static void addninedigitsofpi(LISTDECIMALPI *lpi)
{
	int n=0,i,*ninedig_t;
	struct _LISTNINEPIS *ptr,*ptr0=NULL,*ptr2=NULL;
	
	for (i=0,ninedig_t=lpi->ninedig_t;i<lpi->numdigits;i++)
	{	
		ptr=malloc(sizeof(struct _LISTNINEPIS));
		if (ptr==NULL)
			break;
		n++;
		if (ptr0==NULL)
			ptr0=ptr;
		if (ptr2!=NULL)
			ptr2->next=ptr;
		ptr2=ptr;
		ptr->ninedig=*ninedig_t++;
		ptr->next=NULL;		
	}
	if (ptr0==NULL || SDL_LockMutex(lpi->mutexadd)<0)
		return ;
	lpi->at += 9*n;
	if (lpi->first==NULL)
		lpi->first=ptr0;
	if (lpi->last!=NULL)	
		lpi->last->next=ptr0;
	lpi->last=ptr2;
	SDL_UnlockMutex(lpi->mutexadd);
	if (SDL_LockMutex(lpi->muteunitat)==0)
	{
		if (lpi_isuntilat(lpi))
			SDL_CondSignal(lpi->condunitat);
		SDL_UnlockMutex(lpi->muteunitat);
	}
}

static int lpi_thread(LISTDECIMALPI *lpi)
{
	int at2;
	int cpus,i,*ninedig_t,*dump;
	SDL_Thread **threads;
	
	lpi->at=1;
	while (!lpi->finish)
	{
		cpus=reservemaxnumcpus();
		for(at2=lpi->at,i=0,ninedig_t=lpi->ninedig_t,threads=lpi->threads;i<cpus;)
		{
			dump=ninedig_t;
			*ninedig_t++=at2;
			at2 += 9;
			i++;
			if ((*threads++=SDL_CreateThread(thread_ninedigitpi,"thread_ninedigitpi",dump))==NULL)
				break;
		}
		lpi->numdigits=++i;
		*ninedig_t=ninedigitsofpi(at2);
		at2 += 9;
		for(ninedig_t=lpi->ninedig_t,threads=lpi->threads;i-->0;threads++,ninedig_t++)
			SDL_WaitThread(*threads,ninedig_t);
		dereservenumcpus(cpus);
		addninedigitsofpi(lpi);
	}
	
	return 0;
}

int lpi_initthread(LISTDECIMALPI *lpi)
{
	reservenumcpus(1,1);
	if ((lpi->thread=SDL_CreateThread(lpi_thread,"lpi_thread",lpi))==NULL)
	{
		dereservenumcpus(1);
		
		return seterror("Don't can create lpi_thread: %s", SDL_GetError());			
	}
	
	return RET_SUCESS;
}

void lpi_donethread(LISTDECIMALPI *lpi,int async)
{
	int status; 
	lpi->finish=1;
	if (lpi->thread!=NULL)
	{
		if (!async)
			SDL_WaitThread(lpi->thread,&status);
		dereservenumcpus(1);
	}
}

int lpi_nextninedigitpi(LISTDECIMALPI *lpi)
{
	int ret;
	struct _LISTNINEPIS *ptr;
	
	if (SDL_LockMutex(lpi->mutexadd)<0)
		return -1;
		
	if (lpi->first==NULL)
	{	
		SDL_UnlockMutex(lpi->mutexadd);	
		
		return -1;		
	}
	ptr	=lpi->first;
	ret=ptr->ninedig;
	lpi->first=ptr->next;
	//free(ptr);
	SDL_UnlockMutex(lpi->mutexadd);
	
	return ret;
}

void lpi_waitunitat(LISTDECIMALPI *lpi,int untilat)
{
	if (SDL_LockMutex(lpi->muteunitat)==0)
	{
		lpi->untilat=untilat;
		while (!lpi_isuntilat(lpi))
			SDL_CondWait(lpi->condunitat,lpi->muteunitat);
		SDL_UnlockMutex(lpi->muteunitat);
	}
}

void lpi_next(LISTDECIMALPI *lpi,int ndec)
{
	char *str;
	int ninedigit;
	
	if (lpi->position<0)
	{
		strcpy(&lpi->ninedig,"3.");
		lpi->position=0;
	}	
	for(str=lpi->ninedig+lpi->position;ndec>0;)
	{		
		if(*str=='\x0')
		{
			if ((ninedigit=lpi_nextninedigitpi(lpi))<0)
				continue;
			sprintf(&lpi->ninedig,"%09i",ninedigit);			
			lpi->position=0;
			str=lpi->ninedig;
			continue;
		}
		switch(*(lpi->cars_act))
		{
			case 0:
				lpi->cars_act=glexBitmapCarsScrollUp(lpi->cars);
				break;
			case '\n':
				lpi->cars_act++;
				break;
			default:
				*(lpi->cars_act++)=*str++;
				lpi->position++;
				ndec--;
		}
	}
}

void lpi_next_slow(LISTDECIMALPI *lpi)
{
	lpi_next(lpi,1);
}

void lpi_render(LISTDECIMALPI *lpi)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0.0, 0.0, 1.0);
	glRasterPos2f(0, 13);
	glutBitmapString(GLUT_BITMAP_8_BY_13,lpi->cars);
	glxswap();	
}

static int pi_readargs(Pi *data,int argc, char **argv)
{
	return RET_SUCESS;
}

static int pi_init(Pi *data)
{
	return lpi_make(&data->listpi);
}

static int pi_initgl(Pi *data)
{
	return RET_SUCESS;
}

static void pi_run(Pi *data)
{
	lpi_initthread(&data->listpi);
	//lpi_waitunitat(&data->listpi,1000 /*2*data->listpi.width*data->listpi.height*/);
	while(timestuff(10,1,&data->listpi,lpi_next_slow,lpi_render,2*1000000)!=RET_CANCEL);
	lpi_donethread(&data->listpi,0);
}

static void pi_deinit(Pi *data)
{
	lpi_destroy(&data->listpi);
}