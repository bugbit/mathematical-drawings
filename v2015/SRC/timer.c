#include "pch.h"

#if defined(__unix__) || defined(unix)
#include <time.h>
#include <sys/time.h>
#else	/* assume win32 */
#include <windows.h>
#endif	/* __unix__ */

#include "dibuixos.h"

unsigned long get_msec(void) {
#if defined(__unix__) || defined(unix)
	static struct timeval timeval, first_timeval;
	
	gettimeofday(&timeval, 0);

	if(first_timeval.tv_sec == 0) {
		first_timeval = timeval;
		return 0;
	}
	return (timeval.tv_sec - first_timeval.tv_sec) * 1000 + (timeval.tv_usec - first_timeval.tv_usec) / 1000;
#else
	return GetTickCount();
#endif	/* __unix__ */
}

void init_timers(TIMER *timer)
{
	timer->ticksf=timer->ticks=get_msec();
	timer->elapsetime=0;
}

unsigned int elapse_timers(TIMER *timer,int reset)
{
	unsigned int ticks=get_msec();
	
	timer->elapsetime=ticks-timer->ticksf;
	timer->ticks=ticks;
	if (reset)
		timer->ticksf=ticks;
	
	return timer->elapsetime;
}
