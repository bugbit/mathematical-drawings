using System;
using System.Drawing;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using OpenTKGLUT;
using Core = Dibuixos.Core;


namespace Dibuixos
{
    public class DibuixosBaseWindow : GameWindow
    {
        public Core.Arguments Args { get; private set; }
        public Matrix4 ProjectionMatrix { get; private set; }

        public DibuixosBaseWindow(Core.Arguments argArgs) : base()
        {
            Args = argArgs;
        }

        protected override void OnLoad(EventArgs e)
        {
            GLUT.glutInit(Args.Args);
            base.OnLoad(e);
        }

        protected override void OnResize(EventArgs e)
        {
            var pClientRectangle = ClientRectangle;

            GL.Viewport(pClientRectangle.X, pClientRectangle.Y, pClientRectangle.Width, pClientRectangle.Height);
            ProjectionMatrix = Matrix4.CreateOrthographicOffCenter(pClientRectangle.X, pClientRectangle.Width, pClientRectangle.Y, pClientRectangle.Height, -1.0f, 1.0f);

            base.OnResize(e);
        }
    }
}

