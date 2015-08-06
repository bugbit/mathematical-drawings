#ifndef	__DIBUIXOS_H__

#define 	__DIBUIXOS_H__

#define	SRESX				640
#define	SRESY				400


#define	DWE_NOERRORS		-10000
#define	DWE_NO386			0
#define	DWE_NO387   		1
#define	DWE_EXIT				2

#ifdef __A4__
     #include <allegro.h>
#else
     #include "a4_aux.h"
#endif

// memoria

typedef struct
{
  int calc;
  long dosmemfree;
} MEMFREE;

// videos

typedef struct
{
	int w;
	int h;
	int maxcol;
} GRMODE;


typedef struct
{
	char *name;
	int (*getgrmodes)(GRMODE **gr,int *num,int *alloc);
	int (*init)();
	int (*close)();
} VIDEO;

extern VIDEO vi_videos[];

extern VIDEO *vi_video;

extern int vi_num;

extern GRMODE *vi_grmode;

extern int vi_binit;

// main

int dw_main();
int choosevideo(VIDEO *videos,int num,VIDEO **vp);
int choosegrmode(GRMODE *g,int num,GRMODE **gp);


// system

void showError(char *msg);

// util

extern int dw_errorcode;


#define 	dwe_cleanerrors() dw_errorcode=DWE_NOERRORS
#define	dwe_isOk() dw_errorcode==DWE_NOERRORS

void dwe_showError();


char *dwe_geterrorstr();
int checkSystem();


// memoria

void getmemfree(MEMFREE *mf);

// video

void vi_setvideo(VIDEO *v);
void vi_setgrmode(GRMODE *g);
int vi_getgrmodes(GRMODE **gr,int *num,int *alloc);
int vi_init();
int vi_close();

#endif