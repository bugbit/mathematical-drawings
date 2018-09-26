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
            {
                var pFileAssembly = Assembly.GetExecutingAssembly().Location;
                var pFileExe = Path.Combine(Path.GetDirectoryName(pFileAssembly), "Dibuixos.exe");

                //MessageBox.Show($"{pFileAssembly}\n{pFileExe}"); 
                Process.Start(pFileExe, "-screensaver -cycle 1").WaitForExit();
            }
        }
    }
}
