#pragma once

ref class GLUT
{
private:
	ref class SFG_Font
	{
		System::String^ Name;         /* The source font name             */
		int             Quantity;     /* Number of chars in font          */
		int             Height;       /* Height of the characters         */
		const GLubyte** Characters;   /* The characters mapping           */

		float           xorig, yorig; /* Relative origin of the character */
	};
public:
	GLUT();
};

