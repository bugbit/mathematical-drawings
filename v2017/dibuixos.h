#ifndef __DIBUIXOS_H__

#define  __DIBUIXOS_H__

typedef struct
{
	char *name;
	int (*readargs)(int argc, char **argv);
	int (*run)();
	char *description;
} DIBUIXOS;

extern DIBUIXOS dib_demo;
extern DIBUIXOS *dibuixo_arg;

extern char dib_error[128];

int seterror(char *fmt,...);

#endif
