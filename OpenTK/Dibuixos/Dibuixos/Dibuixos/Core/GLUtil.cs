﻿using System;
using OpenTK.Graphics.OpenGL;
using OpenTKGLUT;
using System.Linq;

namespace Dibuixos.Core
{
    public static class GLUtil
    {
        public static void OrthoW()
        {
            var pGameWindow = Dibuixos.DibuixosMain.GameWindow;

            GL.LoadIdentity();
            GL.Ortho(0, pGameWindow.Width, 0, pGameWindow.Height, -1, 1);
        }

        public static void OrthoWindow()
        {
            //Initialize Projection Matrix
            GL.MatrixMode(MatrixMode.Projection);
            OrthoW();

            //Initialize Modelview Matrix
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
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

    }
}

