/*
MIT License

Copyright (c) 2019 Sistema Solar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "pch.h"

#include "CDibuixosApp.h"

glm::vec3 CDibuixosApp::g_InitialCameraPosition;
glm::quat CDibuixosApp::g_InitialCameraRotation;
CCamera CDibuixosApp::g_Camera;
int CDibuixosApp::g_iWindowWidth = 1280;
int CDibuixosApp::g_iWindowHeight = 720;
int CDibuixosApp::g_iWindowHandle = 0;

void CDibuixosApp::ErrMsgDisplayGL()
{
	glViewport(0, 0, (GLsizei)g_iWindowWidth, (GLsizei)g_iWindowHeight); // set view to ALL
	glMatrixMode(GL_PROJECTION); // use PROJECTION matrix
	glLoadIdentity(); // and load it...
	// set to whole screen
	gluOrtho2D(0.0, (GLdouble)g_iWindowWidth, 0.0, (GLdouble)g_iWindowHeight);

	// Borrar buffers de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0); // output the string, in red
	glRasterPos2d(100, 100);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char *) "Error");
	glutSwapBuffers();
}

int CDibuixosApp::Run(int _argc, char **_argv)
{
	ErrOrOk ok = Init(_argc, _argv);

	if (!IsOk(ok))
	{
#ifdef _WINDOWS
		//MessageBox(NULL, std::wstring(ok->begin(), ok->end()).c_str(), L"Sistema Solar", MB_OK);
		std::cerr << *ok << std::endl;
#else

#endif // _Windows
		return EXIT_FAILURE;
	}

	glutMainLoop();

	return EXIT_SUCCESS;
}

ErrOrOk CDibuixosApp::Init(int _argc, char* _argv[])
{
	ErrOrOk err = __OK__;

	// Inicializamos la camara
	g_InitialCameraPosition = glm::vec3(0, 0, 100);
	g_Camera.SetPosition(g_InitialCameraPosition);
	g_Camera.SetRotation(g_InitialCameraRotation);

	// Inicializar Opengl
	InitGL(_argc, _argv);
	if (!IsOk((err = InitGLEW())))
		return err;

	return err;
}

void CDibuixosApp::InitGL(int _argc, char* _argv[])
{
	glutInit(&_argc, _argv);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	// Create an OpenGL 3.3 core forward compatible context.
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitWindowPosition((iScreenWidth - g_iWindowWidth) / 2, (iScreenHeight - g_iWindowHeight) / 2);
	glutInitWindowSize(g_iWindowWidth, g_iWindowHeight);

	g_iWindowHandle = glutCreateWindow("Sistema Solar");

	// Register GLUT callbacks.
	glutDisplayFunc(DisplayGL);
	glutReshapeFunc(ReshapeGL);
}

ErrOrOk CDibuixosApp::InitGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return ThrowError("There was a problem initializing GLEW. Exiting...");

	// Check for 3.3 support.
   // I've specified that a 3.3 forward-compatible context should be created.
   // so this parameter check should always pass if our context creation passed.
   // If we need access to deprecated features of OpenGL, we should check
   // the state of the GL_ARB_compatibility extension.
	if (!GLEW_VERSION_3_3)
		return ThrowError("OpenGL 3.3 required version support not present.");

#ifdef _WIN32
	if (WGLEW_EXT_swap_control)
	{
		wglSwapIntervalEXT(0); // Disable vertical sync
	}
#endif

	return __OK__;
}

void CDibuixosApp::ReshapeGL(int w, int h)
{
	if (h == 0)
	{
		h = 1;
	}

	g_iWindowWidth = w;
	g_iWindowHeight = h;

	g_Camera.SetViewport(0, 0, w, h);
	g_Camera.SetProjectionRH(30.0f, w / (float)h, 0.1f, 200.0f);

	glutPostRedisplay();
}

void CDibuixosApp::DisplayGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}