using System;
using OpenTK;
using OpenTK.Graphics;
using Dibuixos.Shared;
using Core=Dibuixos.Shared.Core;

namespace Dibuixos.Desktop
{
	public class DibuixosWindowDesktop : GameWindow
	{
		private Core.DibuixosApp mApp;

		public DibuixosWindowDesktop(Core.Arguments argArgs):base(argArgs.Width,argArgs.Height,GraphicsMode.Default,"mathematical-drawings",(argArgs.Flags.HasFlag(Core.Arguments.EFlags.FullScreen)) ? GameWindowFlags.Fullscreen : GameWindowFlags.Default)
		{
			mApp = new Core.DibuixosApp(this, argArgs);
			mApp.DoExit += (sender, e) => Exit();
		}

		[STAThread]
		public static void Main(string[] args)
		{
			Console.WriteLine("Dibuixos - mathematical-drawings for C# .NET/Mono OpenTK\nCopyright 1995-2015-2016 Oscar Hernández Bañó");

			Core.Arguments pArgs = null;

			try
			{
				pArgs = Core.Arguments.Parse(args);
			}
			catch (Exception ex)
			{
				Console.Error.WriteLine(ex.Message);
				Environment.Exit(1);
			}

			if (pArgs.Flags.HasFlag(Core.Arguments.EFlags.Help))
			{
				Console.WriteLine(@"
dibuixos [options] [dibuixo]\n\n""
options:\n""
   --help : show usage\n""
   -r<width>x<height>x[bpp] : resolucion. Por defecto es -r800x600\n""
   -f : fullscreen""
   -l : play demo in infinite loop\n\n""
dibuixo:\n""
   demo : All of dibuixos""
   <dibuixo> : one of dibuixo (see README for more help)
");
				return;
			}

			using (var pWindow = new DibuixosWindowDesktop(pArgs))
			{
				pWindow.Run();
			}
		}
	}
}
