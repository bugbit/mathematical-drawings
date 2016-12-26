#ifndef __DIBUIXOS_H__

#define  __DIBUIXOS_H__

#define	RET_SUCESS		0
#define	RET_ERROR		-1
#define	RET_EXIT		-2
#define	RET_CANCEL		-3

#define	issucess(r)		(r>=RET_SUCESS)
#define	isnosucess(r)	(r<RET_SUCESS)

typedef struct
{
	char *name;
	int (*readargs)(int argc, char **argv);
	int (*init)();
	int (*intgl)();
	void (*run)();
	void (*deinit)();
	char *description[];
} DIBUIXOS;

extern DIBUIXOS dib_demo;
extern DIBUIXOS *dibuixo_arg;

extern char dib_error[128];

int seterror(char *fmt,...);
int readargs(int argc, char **argv);
void showusage(const char *msgerror);

#endif
