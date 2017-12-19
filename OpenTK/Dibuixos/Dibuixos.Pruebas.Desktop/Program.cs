using Dibuixos.Pruebas.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Pruebas.Desktop
{
    class Program
    {
        static void Main()
        {
            using (var pWindow = new GLDrawStrokeString())
            {
                pWindow.Run();
            }
        }
    }
}
