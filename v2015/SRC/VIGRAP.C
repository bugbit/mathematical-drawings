#ifdef __VI_GRAPHICS__

#include <graphics.h>
#include <memory.h>
#include "svga256.h"

#include "dibuixos.h"

static GRMODE grmode_herc[]=
{
	{ 720,348,2,HERCMONOHI }
};

static GRMODE grmode_vga[]=
{
	{ 640,200,16,VGALO },
	{ 640,380,16,VGAMED }
};

static GRMODE grmode_svga256[]=
{
	{ 320,200,256,SVGA320x200x256 },
	{ 640,400,256,SVGA640x400x256 },
	{ 640,480,256, SVGA640x480x256 },
	{ 800,600,256, SVGA800x600x256 },
	{ 1024,768,256,SVGA1024x768x256 },
	{ 640,350,256, SVGA640x350x256 },
	{ 1280,1024,256, SVGA1280x1024x256 }
};


int gr_herc_getgrmodes(GRMODE **gr,int *num,int *alloc)
{
	*gr=grmode_herc;
	*num=sizeof(grmode_herc)/sizeof(*grmode_herc);
	*alloc=0;

	return 0;
}

int gr_vga_getgrmodes(GRMODE **gr,int *num,int *alloc)
{
	*gr=grmode_vga;
	*num=sizeof(grmode_vga)/sizeof(*grmode_vga);
	*alloc=0;

	return 0;
}

int gr_svga256_getgrmodes(GRMODE **gr,int *num,int *alloc)
{
	*gr=grmode_svga256;
	*num=sizeof(grmode_svga256)/sizeof(*grmode_svga256);
	*alloc=0;

	return 0;
}

int gr_initgraph()
{
	int gd,gm=vi_grmode->bgi_grmode;

	if (!vi_video->bgi_driver)
	{
		gd=vi_video->bgi_grdriver;
	}
	else
	{
		gd=installuserdriver(
	}
}

#endif
