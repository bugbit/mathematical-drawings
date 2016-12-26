#include "pch.h"

#include "dibuixos.h"

static int demo_part;

static int demo_readargs(int argc, char **argv);
static int demo_init();
static int demo_initgl();
static void demo_run();
static void demo_deinit();

DIBUIXOS dib_demo=
{
	"demo",demo_readargs,demo_init,demo_initgl,demo_run,demo_deinit,
	{ "demo [part] default 0",NULL}
};

static int demo_readargs(int argc, char **argv)
{
	if (argc>1)
		return seterror("expect one argument");
		
	if (argc==1)
	{
		if (sscanf(*argv,"%d",&demo_part)==0)
			return seterror("expect number as argument");
		
		return RET_SUCESS;
	}
	
	demo_part=0;
	
	return RET_SUCESS;
}

static int demo_init()
{
	return RET_SUCESS;
}

static int demo_initgl()
{
	return RET_SUCESS;
}

static void demo_run()
{
}

static void demo_deinit()
{
	
}