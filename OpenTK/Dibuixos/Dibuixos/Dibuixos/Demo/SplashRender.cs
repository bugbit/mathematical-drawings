using System;
using OpenTK.Graphics.OpenGL;
using OpenTKGLUT;
using System.Drawing;

namespace Dibuixos.Demo
{
	public class SplashRender : Core.IRenderFrame
	{
		private Renders.TitleFontStrokeRender mTileRender=new Renders.TitleFontStrokeRender();

		#region IRenderFrame implementation

		public void GLInit ()
		{	
			var pGameWindow = Dibuixos.DibuixosMain.GameWindow;

			mTileRender.X = mTileRender.Y = 0;
			mTileRender.Width = pGameWindow.Width;
			mTileRender.Height = pGameWindow.Height;
			mTileRender.Title = "Hello\nWorld";
			mTileRender.Font = GLUT.GLUT_STROKE_ROMAN;
			Core.GLUtil.OrthoWindow ();
			mTileRender.GLInit ();
		}

		public void RenderFrame (OpenTK.FrameEventArgs e)
		{
			GL.ClearColor (Color.Black);
			GL.Clear(ClearBufferMask.ColorBufferBit);
			mTileRender.RenderFrame (e);
		}

		public void GLDone ()
		{
			mTileRender.GLDone();
		}

		#endregion
	}
}

