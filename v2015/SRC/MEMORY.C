#include <alloc.h>

#include "dibuixos.h"

void getmemfree(MEMFREE *mf)
{
	mf->calc=1;
	mf->dosmemfree=coreleft();
}
