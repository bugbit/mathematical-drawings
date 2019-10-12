using System;
using OpenTK.Graphics.OpenGL;
using OpenTKGLUT;
using System.Linq;

namespace Dibuixos.Core
{
    public static class GLUtil
    {
        public static void CreateShaders(string argVS, string argFS, out int argGLVS, out int argGLFS, out int argProgram)
        {
            int status_code;
            string info;

            argGLVS = GL.CreateShader(ShaderType.VertexShader);
            argGLFS = GL.CreateShader(ShaderType.FragmentShader);
            // Compile vertex shader
            GL.ShaderSource(argGLVS, argVS);
            GL.CompileShader(argGLVS);
            GL.GetShaderInfoLog(argGLVS, out info);
            GL.GetShader(argGLVS, ShaderParameter.CompileStatus, out status_code);

            if (status_code != 1)
                throw new ApplicationException(info);

            // Compile vertex shader
            GL.ShaderSource(argGLFS, argFS);
            GL.CompileShader(argGLFS);
            GL.GetShaderInfoLog(argGLFS, out info);
            GL.GetShader(argGLFS, ShaderParameter.CompileStatus, out status_code);

            if (status_code != 1)
                throw new ApplicationException(info);

            argProgram = GL.CreateProgram();
            GL.AttachShader(argProgram, argGLFS);
            GL.AttachShader(argProgram, argGLVS);

            GL.LinkProgram(argProgram);
        }

        public static void CreateShaders(byte[] argVS, byte[] argFS, out int argGLVS, out int argGLFS, out int argProgram)
        {
            var pVS = System.Text.Encoding.Default.GetString(argVS);
            var pFS = System.Text.Encoding.Default.GetString(argFS);

            CreateShaders(pVS, pFS, out argGLVS, out argGLFS, out argProgram);
        }

        //public static void OrthoW()
        //{
        //    var pGameWindow = Dibuixos.DibuixosMain.GameWindow;

        //    GL.LoadIdentity();
        //    GL.Ortho(0, pGameWindow.Width, 0, pGameWindow.Height, -1, 1);
        //}

        //public static void OrthoWindow()
        //{
        //    //Initialize Projection Matrix
        //    GL.MatrixMode(MatrixMode.Projection);
        //    OrthoW();

        //    //Initialize Modelview Matrix
        //    GL.MatrixMode(MatrixMode.Modelview);
        //    GL.LoadIdentity();
        //}

        public static float StrokeHeight(int font)
        {
            var h = (font == GLUT.GLUT_STROKE_MONO_ROMAN || font == GLUT.GLUT_STROKE_ROMAN) ? 119.05f + 33.33f : 119.05f;

            return h;
        }

        public static float StrokeHeight(int fontID, string str)
        {
            var pLines = str.Count(s => s == '\n') + 1;

            return GLUT.glutStrokeHeight(fontID) * (float)pLines;
        }

        public static float StrokeHeightFree(int fontID)
        {
            return (fontID == GLUT.GLUT_STROKE_MONO_ROMAN || fontID == GLUT.GLUT_STROKE_ROMAN) ? 33.33f : 0.0f;
        }

        public static int StrokeMinWidth(int font, string str)
        {
            int w = 999;

            foreach (var car in str)
                w = Math.Min(w, GLUT.glutStrokeWidth(font, car));

            return w;
        }

        public static float StrokeMinHeight(int f, string str)
        {
            return StrokeHeight(f);
        }

        public static float StrokeStrHeight(int f, string str)
        {
            return StrokeHeight(f);
        }

        public static int StrokeStrWidth(int font, string str)
        {
            int w = 0;

            foreach (var car in str)
                w += GLUT.glutStrokeWidth(font, car);

            return w;
        }
    }
}

