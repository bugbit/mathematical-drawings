#include "pch.h"

#include "DIBUIXOS.H"

char dwe_msgerror[255];

/*
static char *dwe_errors[]=
{
	"NO OPENGL or no accelerated",
};
 */

int dwe_seterror(const char *msg,...)
{
    va_list aptr;
    
    va_start(aptr, msg);
    vsprintf(dwe_msgerror,msg,aptr);
    va_end(aptr);
    
    return -1;
}

int dwe_seterrno()
{
    if (errno!=0)
    {
        strcpy(dwe_msgerror,strerror(errno));
        
        return -1;
    }
    
    return 0;
}

int dwe_msgerrf(int _errno,const char *msg,...)
{
    va_list aptr;
    
    errno=_errno;
    va_start(aptr, msg);
    vsprintf(dwe_msgerror,msg,aptr);
    va_end(aptr);
    
    return -1;
}
