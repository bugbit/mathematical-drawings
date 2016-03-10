#ifndef	__DIBUIXOS_H__

#define 	__DIBUIXOS_H__

#define     DWE_NOERRORS    0
#define     DWE_ERRORS      -1

#define	dwe_isOk(r) r==DWE_NOERRORS
#define	dwe_isNoOk(r) r!=DWE_NOERRORS

typedef int dwe_type;

typedef struct _DIBUIXOS
{
	void *app;
    int width_m,height_m,grmodeauto;
    dwe_type (*initsystem)(struct _DIBUIXOS *dib);
} DIBUIXOS;

typedef struct
{
  int calc;
  long dosmemfree;
} MEMFREE;

typedef struct
{
	int fist;
	int last;
	int current;
	int ellapse;
	int total;
} TIMERMS;

//extern SDL_Surface *vi_surface;

extern int vi_width;
extern int vi_height;
extern int vi_bpp;
extern int vi_fullscreen;
//extern SDL_Renderer *vi_displayRenderer;
extern void (*vi_render)();

dwe_type dwe_seterror(const char *fmt,...);
DIBUIXOS * dib_alloc();
void dib_free(DIBUIXOS *dib);
dwe_type dib_main(DIBUIXOS *dib);

int dw_main();

void showError(char *msg);

extern char dwe_msgerror[255];

#define 	dwe_cleanerrors() dw_errorcode=DWE_NOERRORS
//#define	dwe_isOk() dw_errorcode==DWE_NOERRORS

void getmemfree(MEMFREE *mf);

void vi_rendernull();

void calcpi(char *str,int n);

void (*sceneupdate)(TIMERMS *);

void scene1(TIMERMS *);

#endif