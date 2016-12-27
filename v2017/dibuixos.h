#ifndef __DIBUIXOS_H__

#define  __DIBUIXOS_H__

#define	RET_SUCESS		0
#define	RET_ERROR		-1
#define	RET_EXIT		-2
#define	RET_CANCEL		-3

#define	issucess(r)		(r>=RET_SUCESS)
#define	isnosucess(r)	(r<RET_SUCESS)
#define glswap()	SDL_RenderPresent(displayRenderer)

typedef struct
{
	char *name;
	int (*readargs)(int argc, char **argv);
	int (*init)();
	int (*initgl)();
	void (*run)();
	void (*deinit)();
	char *description[];
} DIBUIXOS;

extern DIBUIXOS dib_demo;
extern DIBUIXOS *dibuixo_arg;

extern char dib_error[128],kPathSeparator,path_data[128];
extern int width,height,bpp,fullscreen,loop;
extern SDL_Renderer *displayRenderer;
extern SDL_RendererInfo displayRendererInfo;

// main
int seterror(char *fmt,...);
int readargs(int argc, char **argv);
void showusage(const char *msgerror);
int init();
int initgl();
void deinit();

// util
int exist_dir(char *dir);
void getfiledata(char *filedest,char *filename);

// glutil

extern GLint glcmaxVertices;

void glexOrthoW();
void glexOrthoWindow();

// math

int ninedigitsofpi(int n);

// freeglut

#   define  GLUT_STROKE_ROMAN               ((void *)0x0000)
#   define  GLUT_STROKE_MONO_ROMAN          ((void *)0x0001)
#   define  GLUT_BITMAP_9_BY_15             ((void *)0x0002)
#   define  GLUT_BITMAP_8_BY_13             ((void *)0x0003)
#   define  GLUT_BITMAP_TIMES_ROMAN_10      ((void *)0x0004)
#   define  GLUT_BITMAP_TIMES_ROMAN_24      ((void *)0x0005)
#   define  GLUT_BITMAP_HELVETICA_10        ((void *)0x0006)
#   define  GLUT_BITMAP_HELVETICA_12        ((void *)0x0007)
#   define  GLUT_BITMAP_HELVETICA_18        ((void *)0x0008)

/*
 * Font stuff, see fg_font.c
 */
void     glutBitmapCharacter( void* font, int character );
int      glutBitmapWidth( void* font, int character );
void     glutStrokeCharacter( void* font, int character );
int      glutStrokeWidth( void* font, int character );
GLfloat  glutStrokeWidthf( void* font, int character ); /* GLUT 3.8 */
int      glutBitmapLength( void* font, const unsigned char* string );
int      glutStrokeLength( void* font, const unsigned char* string );
GLfloat  glutStrokeLengthf( void* font, const unsigned char *string ); /* GLUT 3.8 */

int     glutBitmapHeight( void* font );
GLfloat glutStrokeHeight( void* font );
void    glutBitmapString( void* font, const unsigned char *string );
void    glutStrokeString( void* font, const unsigned char *string );


#endif
