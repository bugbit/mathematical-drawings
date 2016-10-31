using System;

#if !MINIMAL
using System.Drawing;
using System.Drawing.Imaging;
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
using Android.Graphics;

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
			argWindow.Unload += DibuixosApp_UnLoad;
			argWindow.Resize += DibuixosApp_Resize;
			//argWindow.Run(60);
		}

		private int texture;

		private void DibuixosApp_Load (object sender, EventArgs e)
		{
			/*
			mDib = Dibuix.FactoryDibuixos.Instance.Presentacio.Invoke ();
			mDib.Options = mDibOpts;
			mDib.FrameEnd += (s, e2) => OnDoExit(e2) ;
			mDib.Load (e);
			*/

			using (var bitmap = new Bitmap (@"Data/Textures/dosemu.bmp")) {
				GL.ClearColor (Color.MidnightBlue);
				GL.Enable (EnableCap.Texture2D);

				GL.Hint (HintTarget.PerspectiveCorrectionHint, HintMode.Nicest);

				GL.GenTextures (1, out texture);
				GL.BindTexture (TextureTarget.Texture2D, texture);
				GL.TexParameter (TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
				GL.TexParameter (TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);

				BitmapData data = bitmap.LockBits (new System.Drawing.Rectangle (0, 0, bitmap.Width, bitmap.Height),
					                 ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb);

				GL.TexImage2D (TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, data.Width, data.Height, 0,
					OpenTK.Graphics.OpenGL.PixelFormat.Bgra, PixelType.UnsignedByte, data.Scan0);

				bitmap.UnlockBits (data);
			}
			mWindow.Resize += (s, e2) => 
			{
				var pClientRectangle = mWindow.ClientRectangle;

				GL.Viewport(pClientRectangle.X, pClientRectangle.Y, pClientRectangle.Width, pClientRectangle.Height);
				GL.MatrixMode(MatrixMode.Projection);
				GL.LoadIdentity();
				GL.Ortho(-1.0, 1.0, -1.0, 1.0, 0.0, 4.0);
			};
			mWindow.RenderFrame += (s, e2) => 
			{
				GL.Clear(ClearBufferMask.ColorBufferBit);

				GL.MatrixMode(MatrixMode.Modelview);
				GL.LoadIdentity();
				GL.BindTexture(TextureTarget.Texture2D, texture);

				GL.Begin(BeginMode.Quads);

				GL.TexCoord2(0.0f, 1.0f); GL.Vertex2(-0.6f, -0.4f);
				GL.TexCoord2(1.0f, 1.0f); GL.Vertex2(0.6f, -0.4f);
				GL.TexCoord2(1.0f, 0.0f); GL.Vertex2(0.6f, 0.4f);
				GL.TexCoord2(0.0f, 0.0f); GL.Vertex2(-0.6f, 0.4f);

				GL.End();


				mWindow.SwapBuffers ();
			};
			/*mWindow.RenderFrame += (s, e2) => {
				GL.ClearColor (Color4.Purple);
				GL.Clear (ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

				mWindow.SwapBuffers ();
			};*/
			//mWindow.RenderFrame += DibuixosApp_RenderFrame;
			//mWindow.UpdateFrame += DibuixosApp_UpdateFrame;
		}

		private void DibuixosApp_UnLoad (object sender, EventArgs e)
		{
			GL.DeleteTextures(1, ref texture);
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
