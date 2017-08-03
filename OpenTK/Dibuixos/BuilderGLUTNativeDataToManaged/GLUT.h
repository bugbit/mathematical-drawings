#pragma once

#include "fg.h"

static public ref class GLUT
{
public:
	ref class SFG_Font
	{
	public:
		property System::String^ Name;         /* The source font name             */
		property int Quantity;     /* Number of chars in font          */
		property int  Height;       /* Height of the characters         */
		property array<array<System::Byte>^>^ Characters;   /* The characters mapping           */

		property float xorig;
		property float yorig; /* Relative origin of the character */
	};
	ref class SFG_Fonts
	{
	public:
		property SFG_Font^ FontFixed8x13;
		property SFG_Font^ FontFixed9x15;
		property SFG_Font^ FontHelvetica10;
		property SFG_Font^ FontHelvetica12;
		property SFG_Font^ FontHelvetica18;
		property SFG_Font^ FontTimesRoman10;
		property SFG_Font^ FontTimesRoman24;
	};

	GLUT();
	static void CreateAndWriteFonts();

private:
	static SFG_Font^ CreateFont(::SFG_Font *f);
	static void CreateFontsBitMap(SFG_Fonts^ pFonts);
};

