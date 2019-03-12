using System;

namespace Dibuixos.Desktop
{
    /// <summary>
    /// The main class.
    /// </summary>
    public static class DibuixosProgram
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            using (var game = new DibuixosGame())
                game.Run();
        }
    }
}
