﻿using OpenTK;
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
        private const string shader_code =
@"!!ARBfp1.0\n
TEX result.color, fragment.texcoord, texture[0], 2D; \n
END";
        private IntPtr h_Src = IntPtr.Zero;
        private int gl_Tex = 0;
        private int gl_PBO = 0;
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
            GL.Ortho(0, Width, 0, Height, -1, 1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            InitOpenGLBuffers(Width, Height);
        }

        private void InitOpenGLBuffers(int w, int h)
        {
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
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)TextureWrapMode.Clamp);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)TextureWrapMode.Clamp);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Nearest);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Nearest);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba8, w, h, 0, PixelFormat.Rgba, PixelType.UnsignedByte, h_Src);
            //gl_Shader=GL.
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