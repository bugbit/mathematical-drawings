using Core = Dibuixos.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenTK;

namespace Dibuixos.GameObjects
{
    public class GOTextInSpiralCenterFontStroken : Core.IRenderFrame, Core.IUpdateFrame
    {
        public enum Modos { O_OCULTO, O_MOV, O_NOMOV, O_FIN }

        public class Caracter
        {
            public double rad0, rad, arad, x, y, div, scale, anc, anc0, aanc;
            public double ang0, ang, aang;
            public int car, steps, modo;
        }

        public string[] Texto;
        public float Width { get; set; }
        public float Height { get; set; }
        public int Font { get; set; }

        public void GLInit()
        {
            throw new NotImplementedException();
        }

        public void RenderFrame(FrameEventArgs e)
        {
            throw new NotImplementedException();
        }

        public void UpdateFrame(FrameEventArgs e)
        {
            throw new NotImplementedException();
        }

        public void GLDone()
        {
            throw new NotImplementedException();
        }
    }
}
