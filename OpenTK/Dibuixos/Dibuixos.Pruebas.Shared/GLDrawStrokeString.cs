using OpenTK;
using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
#if ANDROID
using OpenTK.Platform.Android;
using Android.Content;
using Android.Util;
#endif

namespace Dibuixos.Pruebas.Shared
{
    class GLDrawStrokeString
#if ANDROID
        : AndroidGameView
#elif DESKTOP
        : GameWindow
#endif
    {

#if ANDROID
        public GLDrawStrokeString(Context context) : base(context)
        {
            // do not set context on render frame as we will be rendering
            // on separate thread and thus Android will not set GL context
            // behind our back
            AutoSetContextOnRenderFrame = false;

            // render on separate thread. this gains us
            // fluent rendering. be careful to not use GL calls on UI thread.
            // OnRenderFrame is called from rendering thread, so do all
            // the GL calls there
            //RenderOnUIThread = false;
        }
#elif DESKTOP
        public GLDrawStrokeString() : base() { }
#endif

#if ANDROID
        // This method is called everytime the context needs
        // to be recreated. Use it to set any egl-specific settings
        // prior to context creation
        //
        // In this particular case, we demonstrate how to set
        // the graphics mode and fallback in case the device doesn't
        // support the defaults
        protected override void CreateFrameBuffer()
        {
            //GLContextVersion = GLContextVersion.Gl1_1;

            // the default GraphicsMode that is set consists of (16, 16, 0, 0, 2, false)
            try
            {
                Log.Verbose("TexturedCube", "Loading with default settings");

                // if you don't call this, the context won't be created
                base.CreateFrameBuffer();
                return;
            }
            catch (Exception ex)
            {
                Log.Verbose("TexturedCube", "{0}", ex);
            }

            // Fallback modes
            // If the first attempt at initializing the surface with a default graphics
            // mode fails, then the app can try different configurations. Devices will
            // support different modes, and what is valid for one might not be valid for
            // another. If all options fail, you can set all values to 0, which will
            // ask for the first available configuration the device has without any
            // filtering.
            // After a successful call to base.CreateFrameBuffer(), the GraphicsMode
            // object will have its values filled with the actual values that the
            // device returned.


            // This is a setting that asks for any available 16-bit color mode with no
            // other filters. It passes 0 to the buffers parameter, which is an invalid
            // setting in the default OpenTK implementation but is valid in some
            // Android implementations, so the AndroidGraphicsMode object allows it.
            try
            {
                Log.Verbose("TexturedCube", "Loading with custom Android settings (low mode)");
                GraphicsMode = new AndroidGraphicsMode(16, 0, 0, 0, 0, false);

                // if you don't call this, the context won't be created
                base.CreateFrameBuffer();
                return;
            }
            catch (Exception ex)
            {
                Log.Verbose("TexturedCube", "{0}", ex);
            }

            // this is a setting that doesn't specify any color values. Certain devices
            // return invalid graphics modes when any color level is requested, and in
            // those cases, the only way to get a valid mode is to not specify anything,
            // even requesting a default value of 0 would return an invalid mode.
            try
            {
                Log.Verbose("TexturedCube", "Loading with no Android settings");
                GraphicsMode = new AndroidGraphicsMode(0, 4, 0, 0, 0, false);

                // if you don't call this, the context won't be created
                base.CreateFrameBuffer();
                return;
            }
            catch (Exception ex)
            {
                Log.Verbose("TexturedCube", "{0}", ex);
            }
            throw new Exception("Can't load egl, aborting");
        }
#endif

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
#if ANDROID
            using (StreamReader sr = new StreamReader(Context.Assets.Open("fgFonts.xml")))
            {
                var content = sr.ReadToEnd();
            }
            Run();
#endif
        }
    }
}
