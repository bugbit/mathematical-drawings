using System;

using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.ES20;
using OpenTK.Platform.Android;

using Android.Content;
using Android.Util;

using Dibuixos.Shared;

namespace Dibuixos.Android
{
	class DibuixosView : AndroidGameView
	{
		private DibuixosApp mApp;

		public DibuixosView(Context context) : base(context)
		{
			// New GL "world" object
			// Do not set context on render frame as we will be rendering
			// on separate thread and thus Android will not set GL context
			// behind our back
			AutoSetContextOnRenderFrame = false;

			// Render on separate thread. This gains us
			// fluent rendering. Be careful to not use GL calls on UI thread.
			// OnRenderFrame is called from rendering thread, so do all
			// the GL calls there
			RenderOnUIThread = false;
			mApp = new DibuixosApp(this, new Arguments());
		}

		// This gets called when the drawing surface is ready
		protected override void OnLoad(EventArgs e)
		{
			base.OnLoad(e);

			// Run the render loop
			Run();
		}

		// This method is called everytime the context needs
		// to be recreated. Use it to set any egl-specific settings
		// prior to context creation
		//
		// In this particular case, we demonstrate how to set
		// the graphics mode and fallback in case the device doesn't
		// support the defaults
		protected override void CreateFrameBuffer()
		{
			ContextRenderingApi = GLVersion.ES2;

			// The default GraphicsMode that is set consists of (16, 16, 0, 0, 2, false)
			try
			{
				Log.Verbose("GLTemplateES20", "Loading with default settings");

				// If you don't call this, the context won't be created
				base.CreateFrameBuffer();
				return;
			}
			catch (Exception ex)
			{
				Log.Verbose("GLTemplateES20", "{0}", ex);
			}

			// This is a graphics setting that sets everything to the lowest mode possible so
			// the device returns a reliable graphics setting.
			try
			{
				Log.Verbose("GLTemplateES20", "Loading with custom Android settings (low mode)");
				GraphicsMode = new AndroidGraphicsMode(0, 0, 0, 0, 0, false);

				// If you don't call this, the context won't be created
				base.CreateFrameBuffer();
				return;
			}
			catch (Exception ex)
			{
				Log.Verbose("GLTemplateES20", "{0}", ex);
			}
			throw new Exception("Can't load egl, aborting");
		}
	}
}

