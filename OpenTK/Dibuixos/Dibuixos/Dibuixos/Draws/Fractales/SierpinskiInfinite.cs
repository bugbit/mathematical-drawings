using OpenTK;
using OpenTK.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Dibuixos.Draws.Fractales
{
    [Core.Dibuix("SierpinskiInfinite", "SierpinskiInfiniteTitle")]
    class SierpinskiInfinite : Core.DibuixGameWindow
    {

        public SierpinskiInfinite(Core.DibuixArgs argArgs) :
            base(argArgs.GetWidth(800), argArgs.GetHeight(600), argArgs.GraphicsMode, null, argArgs.GameWindowFlags, DisplayDevice.Default, 3, 2, GraphicsContextFlags.Default)
        {
            Args = argArgs;
        }

        public SierpinskiInfinite() : base(800, 600, GraphicsMode.Default, "", GameWindowFlags.Default, DisplayDevice.Default, 3, 2, GraphicsContextFlags.Default)
        { }

        //[STAThread]
        static internal void Main(string[] argArgs)
        {
            var pArgs = Core.DibuixArgs.Parse(argArgs);

            using (var pDibuix = new SierpinskiInfinite(pArgs))
            {
                pDibuix.ApplyArgsAndProperties();
                pDibuix.Run();
            }
        }
    }
}
