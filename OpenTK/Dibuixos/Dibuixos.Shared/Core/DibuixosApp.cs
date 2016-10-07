using System;

#if !MINIMAL
using System.Drawing;
#endif
using OpenTK;
using OpenTK.Platform;
using OpenTK.Graphics;

#if GLES10
using OpenTK.Graphics.ES10

#elif GLES11
using OpenTK.Graphics.ES11;

#elif GLES20
using OpenTK.Graphics.ES20;

#elif GLES30
using OpenTK.Graphics.ES30;

#elif GLES31
using OpenTK.Graphics.ES31;

#else
using OpenTK.Graphics.OpenGL;
#endif

namespace Dibuixos.Shared.Core
{
	public class DibuixosApp
	{
		private IGameWindow mWindow;
		private Dibuix.DibuixOptions mDibOpts;
		private Dibuix.IDibuix mDib;

		public Arguments Args { get; private set;}
		public event EventHandler DoExit;

		public DibuixosApp (IGameWindow argWindow, Arguments argArgs)
		{
			mWindow = argWindow;
			Args = argArgs;
			mDibOpts = new Dibuix.DibuixOptions ();
			if (argArgs.Flags.HasFlag (Arguments.EFlags.Demo))
				mDibOpts.Flags |= Dibuix.DibuixOptions.EFlags.Demo;
			argWindow.Load += DibuixosApp_Load;
			argWindow.Resize += DibuixosApp_Resize;
			//argWindow.Run(60);
		}

		private void DibuixosApp_Load (object sender, EventArgs e)
		{
			mDib = Dibuix.FactoryDibuixos.Instance.Presentacio.Invoke ();
			mDib.Options = mDibOpts;
			mDib.FrameEnd += (s, e2) => OnDoExit(e2) ;
			mDib.Load (e);
			/*
			mWindow.RenderFrame += (s, e2) => {
				GL.ClearColor (Color4.Purple);
				GL.Clear (ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

				mWindow.SwapBuffers ();
			};
			*/
			mWindow.RenderFrame += DibuixosApp_RenderFrame;
			mWindow.UpdateFrame += DibuixosApp_UpdateFrame;
		}

		private void DibuixosApp_Resize(object sender, EventArgs e)
		{
			var pClientRectangle = mWindow.ClientRectangle;

			GL.Viewport(pClientRectangle.X, pClientRectangle.Y, pClientRectangle.Width, pClientRectangle.Height);
			mDibOpts.ProjectionMatrix=Matrix4.CreateOrthographicOffCenter(pClientRectangle.X, pClientRectangle.Width, pClientRectangle.Y, pClientRectangle.Height, -1.0f, 1.0f);
		}

		private void DibuixosApp_UpdateFrame (object sender, FrameEventArgs e)
		{
			mDib.UpdateFrame (e);
		}

		private void DibuixosApp_RenderFrame (object sender, FrameEventArgs e)
		{
			mDib.RenderFrame (e);
			mWindow.SwapBuffers ();
		}

		private void OnDoExit(EventArgs e)
		{
			mDib.Unload (e);
			DoExit?.Invoke (this, e);
		}
	}
}
