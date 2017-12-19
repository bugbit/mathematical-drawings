using System;
using System.Collections.Generic;
using System.Text;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.ES11;
#if ANDROID
using OpenTK.Platform.Android;
using Android.Content;
using Android.Util;
using Android.Graphics;
using Android.Opengl;
#elif DESKTOP
using System.Drawing;
using System.Drawing.Imaging;
#endif

namespace Dibuixos.Pruebas.Shared
{
    class GLDrawCuadView
#if ANDROID
        : AndroidGameView
#elif DESKTOP
        : GameWindow
#endif
    {
        int[] textureIds;
#if ANDROID
        public GLDrawCuadView(Context context) : base(context)
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
        public GLDrawCuadView() : base() { }
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

            GL.ClearColor(1f, .5f, .3f, .4f);

            GL.Hint(All.PerspectiveCorrectionHint, All.Nicest);

            textureIds = new int[1];

            // create texture ids
            GL.Enable(All.Texture2D);
            GL.GenTextures(1, textureIds);

            GL.BindTexture(All.Texture2D, textureIds[0]);

#if ANDROID
            // setup texture parameters
            GL.TexParameterx(All.Texture2D, All.TextureMagFilter, (int)All.Linear);
            GL.TexParameterx(All.Texture2D, All.TextureMinFilter, (int)All.Linear);
            GL.TexParameterx(All.Texture2D, All.TextureWrapS, (int)All.ClampToEdge);
            GL.TexParameterx(All.Texture2D, All.TextureWrapT, (int)All.ClampToEdge);

            Bitmap b = BitmapFactory.DecodeResource(Context.Resources, Dibuixos.Pruebas.Android.Resource.Drawable.texture);

            GLUtils.TexImage2D((int)All.Texture2D, 0, b, 0);
#elif DESKTOP
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);

            var b = Dibuixos.Pruebas.Desktop.Properties.Resources.texture;

            BitmapData data = b.LockBits(new System.Drawing.Rectangle(0, 0, b.Width, b.Height),
                ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb);

            GL.TexImage2D(All.Texture2D, 0, (int)All.Rgba, data.Width, data.Height, 0, All.Bgra, All.UnsignedByte, data.Scan0);

            b.UnlockBits(data);
#endif
            SetupCamera();
#if ANDROID
            Run();
#endif

        }

        void SetupCamera()
        {
            GL.Viewport(0, 0, Width, Height);

            GL.MatrixMode(All.Projection);
            GL.LoadIdentity();
            GL.Ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 4.0f);
        }

        /// <summary>
        /// Respond to resize events here.
        /// </summary>
        /// <param name="e">Contains information on the new GameWindow size.</param>
        /// <remarks>There is no need to call the base implementation.</remarks>
        protected override void OnResize(EventArgs e)
        {
            SetupCamera();
        }

        protected override void OnUnload(EventArgs e)
        {
            GL.DeleteTextures(1, textureIds);
            base.OnUnload(e);
        }

        // This gets called on each frame render
        protected override void OnRenderFrame(FrameEventArgs e)
        {
            // you only need to call this if you have delegates
            // registered that you want to have called
            base.OnRenderFrame(e);

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.MatrixMode(All.Modelview);
            GL.LoadIdentity();
            //GL.Rotate(3.0f, 0.0f, 0.0f, 1.0f);

            //GL.ClearColor(0.5f, 0.5f, 0.5f, 1.0f);


            GL.BindTexture(All.Texture2D, textureIds[0]);
            GL.VertexPointer(2, All.Float, 0, square_vertices);
            GL.EnableClientState(All.VertexArray);
            //GL.ColorPointer(4, All.Float, 0, square_colors);
            //GL.EnableClientState(All.ColorArray);

            GL.TexCoordPointer(2, All.Float, 0, square_textcoord);
            GL.EnableClientState(All.TextureCoordArray);

#if DESKTOP
            GL.DrawArrays(All.Quads, 0, 4);
#elif ANDROID
            GL.DrawArrays(All.TriangleFan, 0, 4);
#endif
            GL.Finish();
            GL.DisableClientState(All.VertexArray);
            GL.DisableClientState(All.TextureCoordArray);

            SwapBuffers();
        }

        float[] square_vertices = {
            -0.5f, -0.5f,
            -0.5f, 0.5f,
            0.5f, 0.5f,
            0.5f, -0.5f,
        };

        byte[] square_colors = {
            255, 255,   0, 255,
            0,   255, 255, 255,
            0,     0,    0,  0,
            255,   0,  255, 255,
        };

        float[] square_textcoord =
            {
            0, 1,
            1, 1,
            1, 0,
            0, 0
        };
    }
}
