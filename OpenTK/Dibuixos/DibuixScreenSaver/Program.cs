using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DibuixScreenSaver
{
    static class Program
    {
        /// <summary>
        /// Punto de entrada principal para la aplicación.
        /// </summary>
        [STAThread]
        static void Main(string[] argArgs)
        {
            if (argArgs.Length == 0 || argArgs.Contains("/s"))
                Process.Start(Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().FullName), "Dibuixos.exe"), "-screensaver -cycle 1").WaitForExit();
        }
    }
}
