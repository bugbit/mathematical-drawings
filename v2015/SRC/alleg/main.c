#include "pch.h"

#include "DIBUIXOS.H"

/*
int dwe_allegroerr(int _errno)
{
    errno=_errno;
    strcpy(dwe_msgerror,allegro_error);
    
    return -1;
}

int dwe_allegromsgerr(int _errno,const char *msg)
{
    errno=_errno;
    sprintf(dwe_msgerror,msg,allegro_error);
    
    return -1;
}

static int init(DIBUIXOS **dib)
{
    DIBUIXOS *dibp;
    
    if (allegro_init() != 0)
      return dwe_seterror(strerror(errno));
    
    /* set up the keyboard handler */
/*
    install_keyboard(); 

    if (dib_alloc(dib)!=0)
        return -1;
    
    dibp=*dib;    
    if (!dibp->grmodeauto)
    {
        if (set_gfx_mode(GFX_AUTODETECT, dibp->width_m, dibp->height_m, 0, 0) != 0) 
        {
            if (set_gfx_mode(GFX_SAFE, dibp->width_m, dibp->height_m, 0, 0) != 0) 
            {
                return dwe_seterror("Unable to graphic mode %dx%d\n%s\n",dibp->width_m,dibp->height_m,allegro_error);
            }
        }
        else
        {
            if (set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0) != 0) 
            {
                if (set_gfx_mode(GFX_AUTODETECT, 640, 500, 0, 0) != 0) 
                {
                    if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0) 
                    {
                        if (set_gfx_mode(GFX_SAFE, 800, 600, 0, 0) != 0) 
                        {
                            if (set_gfx_mode(GFX_SAFE, 640, 500, 0, 0) != 0) 
                            {
                                if (set_gfx_mode(GFX_SAFE, 320, 200, 0, 0) != 0) 
                                {
                                    return dwe_allegromsgerr(DWE_NOGRMODE,"Unable to set any graphic mode\n%s\n");
                                }
                            }
                        }                        
                    }
                }
            }
        }
    }
    
    return 0;
}
*/

static dwe_type dwa_initsystem(DIBUIXOS *dib)
{
    /* set up the keyboard handler */
    
    install_keyboard(); 
    if (!dib->grmodeauto)
    {
        if (set_gfx_mode(GFX_AUTODETECT, dib->width_m, dib->height_m, 0, 0) != 0) 
        {
            if (set_gfx_mode(GFX_SAFE, dib->width_m, dib->height_m, 0, 0) != 0) 
            {
                return dwe_seterror("Unable to graphic mode %dx%d\n%s\n",dib->width_m,dib->height_m,allegro_error);
            }
        }
        else
        {
            if (set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0) != 0) 
            {
                if (set_gfx_mode(GFX_AUTODETECT, 640, 500, 0, 0) != 0) 
                {
                    if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0) 
                    {
                        if (set_gfx_mode(GFX_SAFE, 800, 600, 0, 0) != 0) 
                        {
                            if (set_gfx_mode(GFX_SAFE, 640, 500, 0, 0) != 0) 
                            {
                                if (set_gfx_mode(GFX_SAFE, 320, 200, 0, 0) != 0) 
                                {
                                    return dwe_seterror("Unable to set any graphic mode\n%s\n");
                                }
                            }
                        }                        
                    }
                }
            }
        }
    }
}

static DIBUIXOS * init()
{
    DIBUIXOS *dib=dib_alloc();
    
    if (dib!=NULL)
    {
        dib->initsystem=dwa_initsystem;        
    }
    
    return dib;
}
    
int main(int argc, char **argv)
{  
    DIBUIXOS *dib;
    int ret=EXIT_FAILURE;
    
    if (allegro_init() != 0)
    {
        printf("Not init library allegro: %s",strerror(errno));
      
        return ret;
    }
    if ((dib=init())!=NULL)
    {
        if (dwe_isOk(dib_main(dib)))
            ret=EXIT_SUCCESS;
        dib_free(dib);
    }
    
    if (ret!=EXIT_SUCCESS)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message(dwe_msgerror);
    }

    return ret;
}
