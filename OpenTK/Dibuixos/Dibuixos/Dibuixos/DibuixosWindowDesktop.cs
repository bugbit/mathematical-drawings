using System;
using Core = Dibuixos.Core;

namespace Dibuixos
{
    class DibuixosWindowDesktop
    {
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

            using (var pGameWindow = new DibuixosBaseWindow(pArgs))
            {
                pGameWindow.Run();
            }
        }
    }
}
