using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

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
        private IFS ifs = new IFS
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

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);

            GL.Viewport(0, 0, Width, Height);
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {


            //Matrix4.CreateOrthographicOffCenter(ifs.xmin,ifs.xmax,ifs.ymax,ifs.ymin,)
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(ifs.xmin, ifs.xmax, ifs.ymin, ifs.ymax, 0, 1);
            //GL.Ortho(-1.0, 1.0, -1.0, 1.0, 0.0, 4.0);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();

            GL.Clear(ClearBufferMask.ColorBufferBit);
            GL.Begin(PrimitiveType.Triangles);

            var p0 = new[] { 0.5d, 0.5d };
            var n = 10;

            renderifs(n, p0);
            /*
            //for (var i = 100; i-->0;)
            {
                //GL.Vertex2(p0);
                foreach (var pi in ifs.ps)
                //var pi = ifs.ps[pRandom.Next(ifs.ps.Length)];
                {
                    var p = new[] { pi.a * p0[0] + pi.c * p0[1] + pi.e, pi.b * p0[0] + pi.d * p0[1] + pi.f };

                    GL.Vertex2(p);
                    p0 = p;
                }
            }
            */
            //GL.Vertex2(0, 0);
            //GL.Vertex2(0.5, 1);
            //GL.Vertex2(1, 0);
            GL.End();
            SwapBuffers();

            //GL.DrawElements
        }

        private void renderifs(int n, double[] p0)
        {
            if (n <= 0)
                return;

            var c = (1d / 4d) * n;

            //GL.Color3(c, c, c);
            foreach (var pi in ifs.ps)
            {
                var p = new[] { pi.a * p0[0] + pi.c * p0[1] + pi.e, pi.b * p0[0] + pi.d * p0[1] + pi.f };

                if (n == 1)
                    GL.Vertex2(p);
                p0 = p;
                renderifs(n - 1, p0);
            }
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
