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
	ref class SFG_StrokeVertex
	{
	public:
		property float X;
		property float Y;
	};

	ref class SFG_StrokeStrip
	{
	public:
		property int Number;
		property array<SFG_StrokeVertex^>^ Vertices;
	};

	ref class SFG_StrokeChar
	{
	public:
		property float Right;
		property int Number;
		property array<SFG_StrokeStrip^>^ Strips;
	};

	ref class SFG_StrokeFont
	{
	public:
		property System::String^ Name;                       /* The source font name      */
		property int Quantity;                   /* Number of chars in font   */
		property float Height;                     /* Height of the characters  */
		property array<SFG_StrokeChar^>^ Characters;          /* The characters mapping    */
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
		property SFG_StrokeFont^ StrokeRoman;
		property SFG_StrokeFont^ StrokeMonoRoman;
	};

	GLUT();
	static void CreateAndWriteFonts();

private:
	static SFG_Font^ CreateFont(::SFG_Font *f);
	static void CreateFontsBitMap(SFG_Fonts^ pFonts);
	static SFG_StrokeFont^ CreateFont(::SFG_StrokeFont *f);
	static void CreateFontStrokeMonoRoman(SFG_Fonts^ pFonts);
	static void CreateFontStrokeRoman(SFG_Fonts^ pFonts);
};

