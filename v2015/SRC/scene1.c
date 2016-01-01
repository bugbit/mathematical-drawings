#include "StdAfx.h"
#include "DIBUIXOS.H"

static char *linestr=NULL;
static char *pi_digstr=NULL;
static int caracters=0;
static int rate;
static int maxtimer;
static int pi_digits;
static int pi_adddig;
static int pi_calctimer;

static char *makecars(char *str,int car);

void drawlinestr();
void updatepi(TIMERMS *timer);

void scene1(TIMERMS *timer)
{
	vi_render=drawlinestr;
	sceneupdate=updatepi;
	rate=10;
	pi_adddig=1;
	pi_digits=0;
	maxtimer=timer->total+2*1000000;
	pi_calctimer=timer->total;
}

void drawlinestr()
{
	if (linestr)
	{
	}
}

void updatepi(TIMERMS *timer)
{
	int n=pi_digits+pi_adddig*(timer->total-pi_calctimer)/10;

	if (n!=pi_digits)
	{
		pi_digits=n;
		pi_digstr=makecars(pi_digstr,pi_digits+2+1);
		calcpi(pi_digstr,n);
	}
}

static char *makecars(char *str,int car)
{
	return (str==NULL) ? calloc(car,sizeof(char)) : realloc(str,car*sizeof(char));
}