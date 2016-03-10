#include "pch.h"

#include "DIBUIXOS.H"

static dwe_type no_initsystem(DIBUIXOS *dib)
{
    return dwe_seterror("DIBUIXOS::init_gr not implement");
}

DIBUIXOS * dib_alloc()
{
    DIBUIXOS *dibp;

    if ((dibp=malloc(sizeof(DIBUIXOS)))==NULL)
        dwe_seterror(strerror(errno));
    else
    {
        memset(dibp,0,sizeof(DIBUIXOS));
        dibp->grmodeauto=1;    
        dibp->initsystem=no_initsystem;
    }
    
    return dibp;
}

void dib_free(DIBUIXOS *dib)
{
    if (dib!=NULL)
    {
        free(dib);
    }
}

dwe_type dib_main(DIBUIXOS *dib)
{
    if (dwe_isNoOk(dib->initsystem(dib)))
        return DWE_ERRORS;
        
    return DWE_NOERRORS;
}