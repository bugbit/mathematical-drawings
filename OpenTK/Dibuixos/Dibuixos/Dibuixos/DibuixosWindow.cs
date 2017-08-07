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
    public class DibuixosWindow : GameWindow
    {
		private Core.Dibuix mDibuix = null;
		private Core.CoRoutine mCoRoutineLoad=new Core.CoRoutine();

        public Core.Arguments Args { get; private set; }
        public Matrix4 ProjectionMatrix { get; private set; }

		public DibuixosWindow(Core.Arguments argArgs) : base(argArgs.Width,argArgs.Height,GraphicsMode.Default,"mathematical-drawings",(argArgs.FullScreen) ? GameWindowFlags.Fullscreen : GameWindowFlags.Default)
        {
            Args = argArgs;
        }

        protected override void OnLoad(EventArgs e)
        {			
            base.OnLoad(e);

			mCoRoutineLoad.Start (CoRoutineLoad ());
			do
			{
				RenderSplash();
			} while ( mCoRoutineLoad.Loop());
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
			base.OnRenderFrame (e);
		}

		virtual protected void RenderSplash()
		{
			GL.ClearColor (Color.MidnightBlue);
			GL.Clear(ClearBufferMask.ColorBufferBit);
			SwapBuffers ();
		}

		virtual protected IEnumerator CoRoutineLoad()
		{
			GLUT.glutInit(Args.Args);

			yield return null;

			mDibuix = new Dibuixos.Demo.DibuixDemo (Args.Args);

			yield return mDibuix.CoRoutineLoad ();

			yield break;
		}
    }
}

