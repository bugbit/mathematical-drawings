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
		private INextDibBase mNextDib;
		private Dibuix.IDibuix mDibAct;

		public Arguments Args { get; private set;}
		public event EventHandler DoExit;

		public DibuixosApp (IGameWindow argWindow, Arguments argArgs)
		{
			mWindow = argWindow;
			Args = argArgs;
			mDibOpts = new Dibuix.DibuixOptions ();
			mNextDib= (argArgs.DibArg!=null) ? (INextDibBase) new NextDibDibArg(this) : (INextDibBase) new NextDibDefault(this);
			if (argArgs.Flags.HasFlag (Arguments.EFlags.Demo))
				mDibOpts.Flags |= Dibuix.DibuixOptions.EFlags.Demo;
			argWindow.Load += DibuixosApp_Load;
			//argWindow.Run(60);
		}

		private void DibuixosApp_Load (object sender, EventArgs e)
		{
			Asign( mNextDib.FirstDib ());
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

		private void DibuixosApp_UpdateFrame (object sender, FrameEventArgs e)
		{
			mDibAct?.UpdateFrame (e);
		}

		private void DibuixosApp_RenderFrame (object sender, FrameEventArgs e)
		{
			mDibAct?.RenderFrame (e);
			mWindow.SwapBuffers ();
		}

		private void OnDoExit(EventArgs e)
		{
			DoExit?.Invoke (this, e);
		}

		public void Asign(Dibuix.IDibuix argDib)
		{
			argDib.Load (EventArgs.Empty);
			mDibAct = argDib;
		}

		public void DeAsign()
		{
			mDibAct.Unload (EventArgs.Empty);
			mDibAct = null;
		}

		public void Exit()
		{
			OnDoExit (EventArgs.Empty);
		}
	}
}
