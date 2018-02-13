using OpenTK.Graphics.OpenGL;
using Dibuixos.Pruebas.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenTK.Graphics;
using OpenTK.Platform;

namespace Dibuixos.Pruebas.Desktop
{
    class Program
    {
        private IWindowInfo mWndInfo;
        private IGraphicsContext mContext;

        [STAThread]
        static void Main(string[] args)
        {

            //Application.Run(new frmWndSaversTest());
            //using (var pWindow = new GLDrawStrokeString())
            //{
            //    pWindow.Run();
            //}

            var pApp = new Program();

            if (args.Length >= 2 && args[0] == "/p")
            {
                var pHandle = new IntPtr(int.Parse(args[1]));

                pApp.mWndInfo = Utilities.CreateWindowsWindowInfo(pHandle);
                pApp.mContext = new GraphicsContext(GraphicsMode.Default, pApp.mWndInfo);
                pApp.mContext.LoadAll();

                return;
            }
        }

        private void Render()
        {
            mContext.MakeCurrent(mWndInfo);
            Render2();
            mContext.SwapBuffers();
        }

        private void Render2()
        {
            GL.ClearColor(Color4.Yellow);
            GL.Clear(ClearBufferMask.ColorBufferBit);
        }
    }
}
