using System;
using System.Drawing;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using OpenTKGLUT;
using Core = Dibuixos.Core;
using OpenTK.Graphics;
using System.Collections;


namespace Dibuixos
{
    public class DibuixWindowBase : GameWindow
    {
		protected readonly Core.ManagerRenderFrame mRenderFrame=new Core.ManagerRenderFrame();

        public Core.Arguments Args { get; private set; }
        public Matrix4 ProjectionMatrix { get; private set; }

		public DibuixWindowBase(Core.Arguments argArgs) : base(argArgs.Width,argArgs.Height,GraphicsMode.Default,"mathematical-drawings",(argArgs.FullScreen) ? GameWindowFlags.Fullscreen : GameWindowFlags.Default)
        {
            Args = argArgs;
        }

        protected override void OnLoad(EventArgs e)
        {			
			GLUT.glutInit(Args.Args);
        }

        protected override void OnResize(EventArgs e)
        {
            var pClientRectangle = ClientRectangle;

            GL.Viewport(pClientRectangle.X, pClientRectangle.Y, pClientRectangle.Width, pClientRectangle.Height);
            ProjectionMatrix = Matrix4.CreateOrthographicOffCenter(pClientRectangle.X, pClientRectangle.Width, pClientRectangle.Y, pClientRectangle.Height, -1.0f, 1.0f);

            base.OnResize(e);
        }

		protected override void OnRenderFrame (FrameEventArgs e)
		{
			mRenderFrame.RenderFrame (e);
			SwapBuffers ();
		}

		protected bool IsAnyKey()
		{
			return OpenTK.Input.Keyboard.GetState ().IsAnyKeyDown;
		}

		protected void ExitIfAnyKey()
		{
			if (IsAnyKey ())
				Exit ();
		}
    }
}

