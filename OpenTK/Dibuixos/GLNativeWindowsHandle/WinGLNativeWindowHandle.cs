using OpenTK.Graphics;
using OpenTK.Platform;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace OpenTK.GLNativeWindowsHandle
{
    internal class WinGLNativeWindowHandle : IGLNativeWindowHandle
    {
        private struct MSG
        {
            public IntPtr HWnd;
            public uint Message;
            public IntPtr WParam;
            public IntPtr LParam;
            public uint Time;
            public POINT Point;
            //internal object RefObject;

            public override string ToString()
            {
                return String.Format("msg=0x{0:x} ({1}) hwnd=0x{2:x} wparam=0x{3:x} lparam=0x{4:x} pt=0x{5:x}", (int)Message, Message.ToString(), HWnd.ToInt32(), WParam.ToInt32(), LParam.ToInt32(), Point);
            }
        }

        private struct POINT
        {
            public int X;
            public int Y;

            public POINT(int x, int y)
            {
                this.X = x;
                this.Y = y;
            }

            public System.Drawing.Point ToPoint()
            {
                return new System.Drawing.Point(X, Y);
            }

            public override string ToString()
            {
                return "Point {" + X.ToString() + ", " + Y.ToString() + ")";
            }
        }

        [System.Security.SuppressUnmanagedCodeSecurity]
        [System.Runtime.InteropServices.DllImport("User32.dll")]
        private static extern bool PeekMessage(ref MSG msg, IntPtr hWnd, int messageFilterMin, int messageFilterMax, int flags);

        private MSG msg = new MSG();
        private GraphicsMode mode;

        public WinGLNativeWindowHandle(GraphicsMode mode, IntPtr handle)
        {
            this.mode = mode;

            WindowInfo = Utilities.CreateWindowsWindowInfo(handle);
        }

        public IGraphicsContext CreateContext(int major, int minor, GraphicsContextFlags flags)
        {
            return new GraphicsContext(mode, WindowInfo, major, minor, flags);
        }

        public bool IsIdle
        {
            get { return !PeekMessage(ref msg, IntPtr.Zero, 0, 0, 0); }
        }

        public IWindowInfo WindowInfo { get; }
    }
}
