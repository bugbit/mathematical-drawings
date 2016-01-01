#ifndef	__DIBUIXOS_H__

#define 	__DIBUIXOS_H__

#define	DWE_NOERRORS		-10000
#define	DWE_ERRSDL			-20000
#define	DWE_NOOPENGL		0

typedef struct
{
	void *app;

} APP;

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

int dw_main();

void showError(char *msg);

extern int dw_errorcode;

#define 	dwe_cleanerrors() dw_errorcode=DWE_NOERRORS
#define	dwe_isOk() dw_errorcode==DWE_NOERRORS

void dwe_showError();

int dwe_seterror(int error);
int dwe_setsdlerror();
char *dwe_geterrorstr();
void getmemfree(MEMFREE *mf);

void vi_rendernull();

void calcpi(char *str,int n);

void (*sceneupdate)(TIMERMS *);

void scene1(TIMERMS *);

#endif