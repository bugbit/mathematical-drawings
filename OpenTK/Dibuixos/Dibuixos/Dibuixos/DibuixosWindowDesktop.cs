using System;
using OpenTKGLUT;

namespace Dibuixos
{
	class DibuixosWindowDesktop
	{
		public static void Main (string[] args)
		{
			Console.WriteLine("Dibuixos - mathematical-drawings for C# .NET/Mono OpenTK\nCopyright 1995-2015-2016-2017 Oscar Hernández Bañó");

			GLUT.glutInit (args);
			using (var pGameWindow = new DibuixosBaseWindow ()) 
			{
				pGameWindow.Run ();
			}
		}
	}
}
