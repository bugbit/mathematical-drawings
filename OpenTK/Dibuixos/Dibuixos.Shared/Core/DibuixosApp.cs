using System;
#if !MINIMAL
using System.Drawing;
#endif
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

namespace Dibuixos.Shared
{
	public class DibuixosApp
	{
		private IGameWindow mWindow;
		private Arguments mArgs;

		public DibuixosApp(IGameWindow argWindow, Arguments argArgs)
		{
			mWindow = argWindow;
			mArgs = argArgs;
			argWindow.Load += DibuixosApp_Load;
			//argWindow.Run(60);
		}

		private void DibuixosApp_Load(object sender, EventArgs e)
		{
			mWindow.RenderFrame += (s, e2) =>
			{
				GL.ClearColor(Color4.Purple);
				GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

				//#if !ANDROID
				mWindow.SwapBuffers();
				//#endif
			};
		}
	}
}
