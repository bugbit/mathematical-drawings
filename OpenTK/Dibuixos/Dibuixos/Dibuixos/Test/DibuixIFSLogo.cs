using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL4;

/*
 # IFS code for a permuted Sierpinski triangle
#
# w     a     b     c     d     e     f     p
1   0.5   0.0   0.0   0.5   0.0   0.0  0.3333
2   0.5   0.0   0.0   0.5   0.5   0.0  0.3333
3   0.5   0.0   0.0   0.5   0.0   0.5  0.3333
window 0 0 1 1
 */

namespace Dibuixos.Dibuixos.Test
{
    struct IFSParam
    {
        public double a, b, c, d, e, f, p;

        public IFSParam(params double[] p)
        {
            a = p[0];
            b = p[1];
            c = p[2];
            d = p[3];
            e = p[4];
            f = p[5];
            this.p = p[6];
        }
    }
    struct IFS
    {
        public IFSParam[] ps;
        public double xmin, xmax, ymin, ymax;
    }
    class DibuixIFSLogo : GameWindow
    {
        public IFS ifs = new IFS
        {
            ps = new[]
            {
                new IFSParam(0.5,   0.0 ,  0.0 ,  0.5 ,  0.0 ,  0.0 , 0.3333),
                new IFSParam( 0.5 ,  0.0 ,  0.0 ,  0.5 ,  0.5,   0.0 , 0.3333),
                new IFSParam(0.5  , 0.0 ,  0.0 ,  0.5 ,  0.0,   0.5 , 0.3333)
            },
            ymin = 0,
            xmin = 0,
            ymax = 1,
            xmax = 1
        };

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            base.OnRenderFrame(e);
        }

        static internal void Main(string[] argArgs)
        {
            using (var pDibuix = new DibuixIFSLogo())
            {
                pDibuix.Run();
            }
        }
    }
}
