#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include "dibuixos.h"

static int init();
static int done();

int dw_main()
{
	int ret=init();

	if (!ret)
	{
		ret=done();
	}
	if (ret)
	{
		dwe_showError();
	}

	return 0;
}

static int init()
{
	int ret=checkSystem();
	VIDEO *v;
	GRMODE *gp;
	int num,k,alloc;
	GRMODE *g;


	if (!ret)
		if (!(ret=choosevideo(vi_videos,vi_num,&v)))
		{
			vi_setvideo(v);
			vi_getgrmodes(&g,&num,&alloc);
			if (!(ret=choosegrmode(g,num,&gp)))
			{
				vi_setgrmode(gp);
				if (!(ret=vi_init()))
				{
				}
			}
			if (alloc)
				free(g);
		}


	return ret;
}

static int done()
{
	int ret=0;

	if (vi_binit)
		ret=vi_close();

	return ret;
}

/*
static MEMFREE mf_inicio;
static int mbIsInitVideo=0;

static int init();
static void mensaje_finish();
static void pon_memfree(char *mensaje,MEMFREE *mf);

int _cdecl main(int argc,char *argv[])
{
	if (!init())
	{
		gprintlinexy(10,10,128,"hola mundo");
		getch();
	}
	if (mbIsInitVideo)
		closevideo();
	mensaje_finish();

	return 0;
}

static int init()
{
	int pRet=0;

	getmemfree(&mf_inicio);
	if (!(pRet=checkSystem()))
	{
		initvideo();
		mbIsInitVideo=1;
	}

	return pRet;
}

static void mensaje_finish()
{
	printf("demoscene dibuixos matematics\n\n");
	if (!dwe_isOk())
	{
		printf(dwe_geterrorstr());
	}
	pon_memfree("memoria inicial libre",&mf_inicio);
}

static void pon_memfree(char *mensaje,MEMFREE *mf)
{
	if (mf->calc)
	{
		printf("%s dosmemfree = %lu bytes\n",mensaje,mf->dosmemfree);
	}
}

*/