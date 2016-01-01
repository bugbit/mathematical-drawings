#include "StdAfx.h"
#include <string.h>
#include <SDL_error.h>
#include <sdl_log.h>

#include "dibuixos.h"

int dw_errorcode=DWE_NOERRORS;

static char *dwe_errors[]=
{
	"NO OPENGL or no accelerated",
};

int dwe_seterror(int error)
{
	dw_errorcode=error;

	return -1;
}

int dwe_setsdlerror()
{
	return dwe_seterror(DWE_ERRSDL);
}

char *dwe_geterrorstr()
{
	switch(dw_errorcode)
	{
		case DWE_NOERRORS:
			return "";
		case DWE_ERRSDL:
			return SDL_GetError();
		default:
			if (dw_errorcode<0 || dw_errorcode>sizeof(dwe_errors)/sizeof(*dwe_errors))
			{
				#ifdef __VI_GRAPHICS__
					return grapherrormsg(dw_errorcode);
				#endif

				return "";
			}
		return dwe_errors[dw_errorcode];
	}
}


void dwe_showError()
{
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,dwe_geterrorstr());
}