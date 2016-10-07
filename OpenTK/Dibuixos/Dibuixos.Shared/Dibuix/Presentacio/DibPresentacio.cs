using System;
using QuickFont;
using QuickFont.Configuration;

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

namespace Dibuixos.Shared.Dibuix.Presentacio
{
	public class DibPresentacio : DibuixBase
	{
		private QFontDrawing mFontDraw;
		private QFont mFont;

		public DibPresentacio ()
		{
		}

		#region implemented abstract members of DibuixBase

		public override void Load (EventArgs e)
		{
			mFontDraw = new QFontDrawing ();
			mFont = new QFont ("Data/Fonts/times.ttf", 10, new QFontBuilderConfiguration (true));
		}

		public override void Unload (EventArgs e)
		{
			mFont?.Dispose ();
			mFont = null;
			mFontDraw?.Dispose ();
			mFontDraw = null;
		}

		public override void RenderFrame (OpenTK.FrameEventArgs e)
		{
			GL.ClearColor (Color4.Purple);
			GL.Clear (ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
			mFontDraw.ProjectionMatrix = Options.ProjectionMatrix;
			mFontDraw.Print (mFont, "Hello World", new Vector3 (10, 100,0), QFontAlignment.Left);
			mFontDraw.RefreshBuffers ();
			mFontDraw.Draw ();
		}

		public override void UpdateFrame (OpenTK.FrameEventArgs e)
		{
		}

		#endregion
	}
}

