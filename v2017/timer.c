#include "pch.h"

#include "dibuixos.h"

void init_timers(TIMER *timer)
{
	timer->ticksf=timer->ticks=SDL_GetTicks();
	timer->elapsetime=0;
}

unsigned int elapse_timers(TIMER *timer,int reset)
{
	unsigned int ticks=SDL_GetTicks();
	
	timer->elapsetime=ticks-timer->ticksf;
	timer->ticks=ticks;
	if (reset)
		timer->ticksf=ticks;
	
	return timer->elapsetime;
}

int count_timers(TIMER *timer,unsigned int counter) 
{
	unsigned int elapse=elapse_timers(timer,0);
	unsigned int rest;
	
	if (elapse<counter)
		return 0;
		
	rest=elapse % counter;
	timer->elapsetime=rest;
	timer->ticksf=timer->ticks-rest;
		
	return 1;
}