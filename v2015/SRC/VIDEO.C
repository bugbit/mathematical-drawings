#include <memory.h>
#ifdef __VI_GRAPHICS__
#include <graphics.h>
#endif

#include "dibuixos.h"


VIDEO vi_videos[]=
{
	{ "null" }
},
*vi_video;

GRMODE *vi_grmode;

int vi_binit=0;

int vi_num=sizeof(vi_videos)/sizeof(*vi_videos);

void vi_setvideo(VIDEO *v)
{
	vi_video=v;
}

void vi_setgrmode(GRMODE *g)
{
	vi_grmode=g;
}

int vi_getgrmodes(GRMODE **gr,int *num,int *alloc)
{
	return vi_video->getgrmodes(gr,num,alloc);
}

int vi_init()
{
	int ret=vi_video->init();

	vi_binit=ret;

	return ret;
}

int vi_close()
{
	int ret=0;

	if (vi_binit)
	{
		ret=vi_video->close();
		vi_binit=0;
	}

   return ret;
}
