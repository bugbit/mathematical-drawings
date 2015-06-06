#include <stdlib.h>  // random()
#include <conio.h>
#include "test1\vesa.h"

int main (int argc, char *argv[], char *env[] )
{
	int i=640*480;
	unsigned char *p=screen;
   int colo;

	initvideo();
	/*
	for (;i>0;i--)
		*p++=(unsigned char) random(255);
	*/
	for (i = 0; i < (640 * 480); i += 641) screen[i] = (unsigned char) 0x7;
	waitb();
	for (colo=0;colo<127;colo++)
	{
			for (i = 0; i < (640 * 480); i ++) screen[i] = colo;
			waitb();
	}
	//for (colo=0;colo<127;colo++) rellenamem32(selectorpan,0,colo,anchopant*altopant);
	//for (colo=255;colo>0;colo--) rellenamem32(selectorpan,0,colo,anchopant*altopant);
	//for (colo=0;colo<127;colo++) rellenamem32(selectorpan,0,colo,anchopant*altopant);

   // ...wait for a key

	while (!kbhit());

	deinitvideo();

	return (0);
}