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

#ifndef __DIBUIXOS_H__

#define	__DIBUIXOS_H__

#include <string>

#include "ErrOrOk.h"
#include "CCamera.h"

class CDibuixosApp
{
public:
	static int Run(int _argc, char **_argv);
private:
	static glm::vec3 g_InitialCameraPosition;
	static glm::quat g_InitialCameraRotation;
	static CCamera g_Camera;
	static int g_iWindowWidth;
	static int g_iWindowHeight;
	static int g_iWindowHandle;

	static ErrOrOk Init(int argc, char* argv[]);
	static void InitGL(int argc, char* argv[]);
	static ErrOrOk InitGLEW();
	static void ErrMsgDisplayGL();
	static void ReshapeGL(int w, int h);
	static void DisplayGL();
};

#endif // !__CDibuixos_