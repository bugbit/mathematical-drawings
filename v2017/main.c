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
 *  dibuixo default demo
 *
 * dibuixo:
 *  demo : demo [part]
 *  <dibuixo> : one of dibuixo (see README for more help)
 * 
 */

int main(int argc, char **argv)
{
	int ret=readargs(argc,argv);
	
	if (isnosucess(ret))
	{
		showusage((ret==RET_ERROR) ? dib_error : NULL);
		
		return (ret!=RET_ERROR) ? EXIT_SUCCESS : EXIT_FAILURE;
	}
	printf("hello world\n");
	
	return EXIT_SUCCESS;
}
