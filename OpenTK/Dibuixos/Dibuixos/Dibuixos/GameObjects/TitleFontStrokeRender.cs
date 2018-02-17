using System;
using OpenTK.Graphics.OpenGL;
using OpenTKGLUT;
using System.Drawing;

namespace Dibuixos.GameObjects
{
    public class TitleFontStrokeRender : Core.IRenderFrame
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Width { get; set; }
        public float Height { get; set; }
        public string Title { get; set; }
        public int Font { get; set; }

        private float mX;
        private float mY;
        private float mScale;

        #region IRenderFrame implementation

        public void GLInit()
        {
            var w = GLUT.glutStrokeLengthf(Font, Title);
            var h = Core.GLUtil.StrokeHeight(Font, Title);
            var pScaleX = Width / w;
            var pScaleY = Height / h;
            var pScale = Math.Min(pScaleX, pScaleY);
            var ws = w * pScale;
            var hs = h * pScale;

            mX = (Width - ws) / 2.0f;
            mY = Height-(GLUT.glutStrokeHeight(Font)-(Core.GLUtil.StrokeHeightFree(Font)/2.0f))*pScale -((Height - hs) / 2.0f);
            mScale = pScale;
        }

        public void RenderFrame(OpenTK.FrameEventArgs e)
        {
            GL.PushMatrix();
            GL.Translate(mX, mY, 0);
            GL.Scale(mScale, mScale, 0);
            GLUT.glutStrokeString(GLUT.GLUT_STROKE_ROMAN, Title);
            GL.PopMatrix();
        }

        public void GLDone()
        {
        }

        #endregion
    }
}

