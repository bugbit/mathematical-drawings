#include "pch.h"

#include "DIBUIXOS.H"

int dib_alloc(DIBUIXOS **dib)
{
    DIBUIXOS *dibp;

    if ((dibp=*dib=malloc(sizeof(DIBUIXOS)))==NULL)
        return dwe_seterror(strerror(errno));
    
    memset(dibp,0,sizeof(DIBUIXOS));
    dibp->grmodeauto=1;
    
    return 0;
}

void dib_free(DIBUIXOS *dib)
{
    if (dib!=NULL)
    {
        free(dib);
    }
}