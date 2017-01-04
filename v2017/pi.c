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

static char pi2str[]="3.";

int lpi_make(LISTDECIMALPI *lpi)
{
	int w=width/8,h=(height/13)-3;
	
	lpi->thread=NULL;
	lpi->mutexadd=NULL;
	lpi->nummaxthread=numcpu+1;
	lpi->lfirst=lpi->llast=lpi->ldfirst=lpi->ldlast=lpi->lact=NULL;
	lpi->fastpi=1;
	lpi->blnumdec=2*w*h;
	lpi->blmaxelapse=1000;
	if ((lpi->cars=glexBitmapMakeCars(w,h))==NULL)
		return RET_ERROR;
	if ((lpi->mutexadd=SDL_CreateMutex())==NULL)
		return seterror("Don't can create mutexadd: %s", SDL_GetError());
	lpi->cars_act=lpi->cars;
	lpi->width=w;
	lpi->height=h;
	lpi->pistr=pi2str;
		
	return RET_SUCESS;
}

static void lpi_freelist(struct _LISTDECSPI *ptr0)
{
	struct _LISTDECSPI *ptr=ptr0,*ptr2;
	
	while(ptr!=NULL)
	{
		ptr2=ptr;
		ptr=ptr->next;
		FREE(ptr2->decstr);
		free(ptr2);
	}
}

static void freelistninedigitsofpi(LISTDECIMALPI *lpi)
{
	lpi_freelist(lpi->ldfirst);
	lpi_freelist(lpi->lfirst);
	lpi->lfirst=lpi->llast=lpi->ldfirst=lpi->ldlast=lpi->lact=NULL;
}

void lpi_destroy(LISTDECIMALPI *lpi)
{
	if (!lpi->finish)
		lpi_donethread(lpi,0);
	if (lpi->mutexadd!=NULL)
		SDL_DestroyMutex(lpi->mutexadd);
	FREE(lpi->cars);
	freelistninedigitsofpi(lpi);
}

static struct _LISTDECSPI *lpi_deasignldfirst(LISTDECIMALPI *lpi)
{
	struct _LISTDECSPI *ptr=NULL;
	
	if (SDL_LockMutex(lpi->mutexadd)==0)
	{
		ptr=lpi->ldfirst;
		if (ptr)
		{
			lpi->ldfirst=ptr->next;
			if (!lpi->ldfirst)
				lpi->ldlast=NULL;
			ptr->next=NULL;
		}
		SDL_UnlockMutex(lpi->mutexadd);
	}
	
	return ptr;
}

static struct _LISTDECSPI *lpi_deasignlfirst(LISTDECIMALPI *lpi)
{
	struct _LISTDECSPI *ptr=NULL;
	
	if (SDL_LockMutex(lpi->mutexadd)==0)
	{
		ptr=lpi->lfirst;
		if (ptr)
		{
			lpi->lfirst=ptr->next;
			if (!lpi->lfirst)
				lpi->llast=NULL;
			ptr->next=NULL;
		}
		SDL_UnlockMutex(lpi->mutexadd);
	}
	
	return ptr;
}

static void lpi_addldlast(LISTDECIMALPI *lpi,struct _LISTDECSPI *ptr)
{
	if (SDL_LockMutex(lpi->mutexadd)==0)
	{
		ptr->next=lpi->ldlast;
		if (lpi->ldfirst==NULL)
			lpi->ldfirst=ptr;
		lpi->ldlast=ptr;
		SDL_UnlockMutex(lpi->mutexadd);
	}
	else
		free(ptr);
}

static void lpi_addllast(LISTDECIMALPI *lpi,struct _LISTDECSPI *ptr)
{
	if (SDL_LockMutex(lpi->mutexadd)==0)
	{
		ptr->next=lpi->llast;
		if (lpi->lfirst==NULL)
			lpi->lfirst=ptr;
		lpi->llast=ptr;
		SDL_UnlockMutex(lpi->mutexadd);
	}
	else
		free(ptr);
}

static struct _LISTDECSPI *lpi_getlistdecspi(LISTDECIMALPI *lpi,int *new)
{
	struct _LISTDECSPI *ptr=lpi_deasignldfirst(lpi);
	
	while ((ptr=lpi_deasignldfirst(lpi))!=NULL)
		if (ptr->numdec>=lpi->blnumdec)
			break;
	*new=!ptr;
	if (*new)
	{
		ptr=malloc(sizeof(*ptr));
		if (ptr)
		{			
			if ((ptr->decstr=calloc(lpi->blnumdec+1,sizeof(char *)))==NULL)
			{	
				ptr->numdec=0;
				lpi_addldlast(lpi,ptr);
				ptr=NULL;
			}
			else
				ptr->numdec=lpi->blnumdec;
		}
	}
	if (ptr && ptr->numdec>0)
		memset(ptr->decstr,'\x0',ptr->numdec+1);
		
	return ptr;
}

int lpi_thread(LISTDECIMALPI *lpi)
{
	TIMER timer;
	struct _LISTDECSPI *ptr;
	int new,ret;
	
	lpi->at=1;
	init_timers(&timer);
	while (!lpi->finish)
	{
		ptr=lpi_getlistdecspi(lpi,&new);
		if (!ptr)
			continue;
		for(;;)
		{
			elapse_timers(&timer,1);
			ret=calcpimulticore(ptr->decstr,lpi->at,lpi->blnumdec,(lpi->fastpi) ? fastpi: ninedigitpi_calcpi);
			elapse_timers(&timer,0);
			if (isnosucess(ret))
			{
				if (lpi->fastpi)
				{
					lpi->fastpi=0;
					lpi->blnumdec /= 16;
					if (lpi->blnumdec<1)
						lpi->blnumdec=1;
				}
				else if (lpi->blnumdec>1)
					lpi->blnumdec--;
				continue;
			}
			else
				break;
		}
		lpi->at += lpi->blnumdec;
		if (timer.elapsetime>lpi->blmaxelapse)
		{
			/*
				lpi->blnumdec -> timer.elapsetime
				 x		 -> lpi->blmaxelapse
			*/
			lpi->blnumdec=(long)lpi->blnumdec*lpi->blmaxelapse/timer.elapsetime;
		}
		lpi_addllast(lpi,ptr);
	}
	
	return 0;
}

int lpi_initthread(LISTDECIMALPI *lpi)
{
	reservenumcpus(1,1);
	if ((lpi->thread=SDL_CreateThread(lpi_thread,"lpi",lpi))==NULL)
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

void lpi_next(LISTDECIMALPI *lpi,int ndec)
{
	while(ndec>0)
	{	
		if(*(lpi->pistr)=='\x0')
		{
			if ((lpi->lact=lpi_deasignlfirst(lpi))==NULL)
				return;
			lpi->pistr=lpi->lact->decstr;
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
				*(lpi->cars_act++)=*(lpi->pistr++);
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
	glColor3d(1.0, 1.0, 1.0);
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
	//char pi[100+1];
	
	//ninedigitpi_calcpi(pi,1,100);
	//calcpimulticore(pi,1,100,ninedigitpi_calcpi);
	
	lpi_initthread(&data->listpi);
	while(timestuff(5,1,&data->listpi,lpi_next_slow,lpi_render,2*1000000)!=RET_CANCEL);
	lpi_donethread(&data->listpi,0);
}

static void pi_deinit(Pi *data)
{
	lpi_destroy(&data->listpi);
}
