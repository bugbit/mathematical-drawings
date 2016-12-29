#include "pch.h"

#include "dibuixos.h"

/*
 * 
 * dibuixos [options] [dibuixo]
 * 
 * options:
 *  --help : show usage
 *  -r<width>x<height>x[bpp] : resolucion. Default -r800x600
 *  -f : fullscreen
 *  -l : play demo in infinite loop
 *  --monocpu : no use paralel algoritms
 *  dibuixo default demo
 *
 * dibuixo:
 *  demo : demo [part]
 *  <dibuixo> : one of dibuixo (see README for more help)
 * 
 */

int main(int argc, char **argv)
{
	char pi[100+3];
	int ret=readargs(argc,argv);
	
	fastpi(pi,0,100);
	
	if (isnosucess(ret))
		showusage((ret==RET_ERROR) ? dib_error : NULL);
	else
	{		
		if (issucess((ret=init())))
			if (issucess((ret=initgl())))
			 run();
		deinit();
		if (ret==RET_ERROR)
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"dibuixos matematics",dib_error,NULL);
	}		
	
	return (ret!=RET_ERROR) ? EXIT_SUCCESS : EXIT_FAILURE;
}
