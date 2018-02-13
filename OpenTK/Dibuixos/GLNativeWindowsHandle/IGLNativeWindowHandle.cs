using OpenTK.Graphics;
using OpenTK.Platform;
using System;
using System.Collections.Generic;
using System.Text;

namespace OpenTK.GLNativeWindowsHandle
{
    internal interface IGLNativeWindowHandle
    {
        IGraphicsContext CreateContext(int major, int minor, GraphicsContextFlags flags);
        bool IsIdle { get; }
        IWindowInfo WindowInfo { get; }
    }
}
