#include "pch.h"

#include "dibuixos.h"

static int demo_part;

static int demo_readargs(int argc, char **argv);
static int demo_run();

DIBUIXOS dib_demo=
{
	"demo",demo_readargs,demo_run,"demo [part] default 0"
};

static int demo_readargs(int argc, char **argv)
{
	if (argc>1)
		return seterror("expect one argument");
		
	if (argc==1)
	{
		if (sscanf(*argv,"%d",&demo_part)==0)
			return seterror("expect number as argument");
		
		return 0;
	}
	
	demo_part=0;
	
	return 0;
}

static int demo_run()
{
	return 0;
}