using OpenTK;
using OpenTK.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Dibuixos.Draws.AboutIt
{
    public class DibuixAboutIt
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            var pWidth = 800;
            var pHeight = 600;
            var pMode = GameWindowFlags.Default;

            using (var pDibuix = new GameWindowAboutIt(pWidth, pHeight, pMode))
            {
                pDibuix.Run();
            }
        }
    }
}
