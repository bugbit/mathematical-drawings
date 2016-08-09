#include "pch.h"

#include <error.h>
#include <GL/glut.h>

#include "dibuixos.h"

GLdouble aspectratio;

/*
 * 
 * dibuixos [options] [dibuixo]
 * 
 * options:
 *  --help : show usage
 *  -r<width>x<height>x[bpp] : resolucion. Por defecto es -r800x600
 *  -f : fullscreen
 *  -l : play demo in infinite loop
 *
 * dibuixo:
 *  demo : All of dibuixos
 *  <dibuixo> : one of dibuixo (see README for more help)
 * 
 */
 
static void changeSize(GLsizei w,GLsizei h)
{
	if (h==1)
		h=0;
	glViewport(0,0,w,h);
	aspectratio=(GLfloat)w/(GLfloat)h;
}

static void finish()
{
	setdibuixo(NULL);
}

void KeyboardFuncEscape(unsigned char key,int x, int y)
{
	if (key==27)
		exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    int exit;
    int ret=readargs(argc,argv,&exit);
    
    if (ret || exit)
    {
        showusage((ret) ? dib_error : NULL);
        
        return (!ret) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    
    glutInitWindowSize(width, height);
	
	/* initialize glut */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Dibuixos");
	glutReshapeFunc(changeSize);
    if (fullscreen)
        glutFullScreen();
    
    if (!setdibuixo((dibuixo_arg!=NULL) ? dibuixo_arg : (DIBUIXO *) &dib_presentacio ))
    {
		atexit(finish);
		if (demo || dibuixo_arg!=NULL)
			glutKeyboardFunc(KeyboardFuncEscape);
        glutMainLoop();
    }
    
	return EXIT_SUCCESS;
}
