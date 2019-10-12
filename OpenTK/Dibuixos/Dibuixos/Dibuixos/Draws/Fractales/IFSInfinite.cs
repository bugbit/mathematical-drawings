using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Dibuixos.Draws.Fractales
{
    [Core.Dibuix("SierpinskiInfinite", "SierpinskiInfiniteTitle")]
    class IFSInfinite : Core.DibuixGameWindow
    {
        private int imageW = 0;
        private int imageH = 0;
        private IntPtr h_Src = IntPtr.Zero;
        private int gl_Tex = 0;
        private int gl_PBO = 0;
        private int gl_VS = 0;
        private int gl_FS = 0;
        private int gl_Shader = 0;

        //private fixed char fixedBuffer[128];

        public IFSInfinite(Core.DibuixArgs argArgs) :
            base(argArgs.GetWidth(800), argArgs.GetHeight(600), argArgs.GraphicsMode, null, argArgs.GameWindowFlags, DisplayDevice.Default, 3, 2, GraphicsContextFlags.Default)
        {
            Args = argArgs;
        }

        public IFSInfinite() : base(800, 600, GraphicsMode.Default, "", GameWindowFlags.Default, DisplayDevice.Default, 3, 2, GraphicsContextFlags.Default)
        { }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);

            GL.Viewport(0, 0, Width, Height);

            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(-1, 1, -1, 1, -1, 1);
            InitOpenGLBuffers(Width, Height);
        }

        private void InitOpenGLBuffers(int w, int h)
        {
            imageW = w;
            imageH = h;
            if (h_Src != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(h_Src);
                h_Src = IntPtr.Zero;
            }
            if (gl_Tex != 0)
            {
                GL.DeleteTextures(1, ref gl_Tex);
                gl_Tex = 0;
            }
            if (gl_PBO != 0)
            {
                GL.DeleteBuffers(1, ref gl_PBO);
                gl_PBO = 0;
            }

            // check for minimized window
            if ((w == 0) && (h == 0))
            {
                return;
            }

            h_Src = Marshal.AllocHGlobal(4 * w * h);

            GL.Enable(EnableCap.Texture2D);
            GL.GenTextures(1, out gl_Tex);
            GL.BindTexture(TextureTarget.Texture2D, gl_Tex);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);
            //GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)TextureWrapMode.Clamp);
            //GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)TextureWrapMode.Clamp);
            //GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Nearest);
            //GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Nearest);
            //GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba8, w, h, 0, PixelFormat.Rgba, PixelType.UnsignedByte, h_Src);

            //GL.GenBuffers(1, out gl_PBO);
            //GL.BindBuffer(BufferTarget.PixelUnpackBuffer, gl_PBO);
            //GL.BufferData(BufferTarget.PixelUnpackBuffer, w * h * 4, h_Src, BufferUsageHint.StreamCopy);

            //Core.GLUtil.CreateShaders(Properties.Resources.Shaders_Simple_VS, Properties.Resources.Shaders_Simple_FS, out gl_VS, out gl_FS, out gl_Shader);

            unsafe
            {
                var ptr = (UInt32*)h_Src;

                for (var i = w * h; i-- > 0;)
                    *ptr++ = 0xFF00FF00; // rgra 0xAARRGGRR

                GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba8, w, h, 0, PixelFormat.Rgba, PixelType.UnsignedByte, h_Src);

            }
            //gl_Shader=GL.
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            GL.Clear(ClearBufferMask.ColorBufferBit);

            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();

            GL.BindTexture(TextureTarget.Texture2D, gl_Tex);
            //GL.TexSubImage2D(TextureTarget.Texture2D, 0, 0, 0, imageW, imageH, PixelFormat.Rgba, PixelType.UnsignedByte, IntPtr.Zero);
            //  glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

            // fragment program is required to display floating point texture
            //GL.UseProgram(gl_Shader);
            //GL.Enable( GL_FRAGMENT_PROGRAM_ARB);
            GL.Disable(EnableCap.DepthTest);

            GL.Begin(PrimitiveType.Quads);
            GL.TexCoord2(0.0f, 0.0f);
            GL.Vertex2(0.0f, 0.0f);
            GL.TexCoord2(1.0f, 0.0f);
            GL.Vertex2(1.0f, 0.0f);
            GL.TexCoord2(1.0f, 1.0f);
            GL.Vertex2(1.0f, 1.0f);
            GL.TexCoord2(0.0f, 1.0f);
            GL.Vertex2(0.0f, 1.0f);
            GL.End();

            GL.BindTexture(TextureTarget.Texture2D, 0);
            //glDisable(GL_FRAGMENT_PROGRAM_ARB);
            SwapBuffers();
        }

        protected override void OnUnload(EventArgs e)
        {
            base.OnUnload(e);
            if (h_Src != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(h_Src);
                h_Src = IntPtr.Zero;
            }
            if (gl_Tex != 0)
            {
                GL.DeleteTextures(1, ref gl_Tex);
                gl_Tex = 0;
            }
            if (gl_PBO != 0)
            {
                GL.DeleteBuffers(1, ref gl_PBO);
                gl_PBO = 0;
            }
            if (gl_Shader != 0)
                GL.DeleteProgram(gl_Shader);
            if (gl_VS != 0)
                GL.DeleteShader(gl_VS);
            if (gl_FS != 0)
                GL.DeleteShader(gl_FS);
        }

        //[STAThread]
        static internal void Main(string[] argArgs)
        {
            var pArgs = Core.DibuixArgs.Parse(argArgs);

            using (var pDibuix = new IFSInfinite(pArgs))
            {
                pDibuix.ApplyArgsAndProperties();
                pDibuix.Run();
            }
        }
    }
}
