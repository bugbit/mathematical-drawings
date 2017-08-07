using System;

namespace OpenTKGLUT
{
	public static partial class GLUT
	{
		public static bool Inicializated { get; private set; }

		public static void glutInit (string[] args)
		{
			try {
				fgLoadFonts ();
			} finally {
				Inicializated = true;
			}
		}
	}
}

