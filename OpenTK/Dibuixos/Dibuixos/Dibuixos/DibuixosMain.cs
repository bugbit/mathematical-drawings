using System;
using Core = Dibuixos.Core;

namespace Dibuixos
{
    class DibuixosMain
    {
		public static DibuixWindowBase GameWindow = null;

		public static void Main(string[] args)
        {
            Console.WriteLine("Dibuixos - mathematical-drawings for C# .NET/Mono OpenTK\nCopyright 1995-2015-2016-2017 Oscar Hernández Bañó");

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
			if (pArgs.Help)
			{
				ShowUsage ();

				return;
			}
			using (var pGameWindow = new Dibuixos.Demo.DibuixWindowDemo(pArgs))
            {
				GameWindow = pGameWindow;
                pGameWindow.Run();
            }
        }

		private static void ShowUsage()
		{
			var pUsage = new string[] {
				"Usage:",
				"",
				$"   {string.Join(",", Core.Arguments.cArgsHelp)} : show usage",
				$"   {string.Join(",", Core.Arguments.cArgsResolution)} : resolution. Defect 800x600",
				$"   {string.Join(",", Core.Arguments.cArgsFullScreen)} : fullscreen",
				"",
				"List of Dibuixs:",
				"demo [numpart]: demoscene.",
			};

			Console.WriteLine();

			int y=Console.CursorTop,h=Console.WindowHeight-1;
			var pContinue=false;

			foreach(var pLine in pUsage)
			{
				Console.WriteLine(pLine);
				if (!pContinue && (y++ % h)==0)
				{
					y=17;
					for(;;)
					{
						Console.Write("Continue? (Y/AY/Q)");
						switch(Console.ReadLine().ToLower())
						{
							case "q":
								return;
							case "y":
								break;
							case "ay":
								pContinue=true;
								break;
						}
					}
				}
			}
		}
    }
}
