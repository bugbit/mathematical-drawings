// BuilderGLUTNativeDataToManaged.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include "GLUT.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	GLUT::CreateAndWriteFonts();
    Console::WriteLine(L"fonts file write");
	Console::WriteLine(L"press ENTER to exit");
	Console::ReadLine();

    return 0;
}
