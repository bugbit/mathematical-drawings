using System;
using OpenTK;

namespace Dibuixos.Core
{
	public interface IRenderFrame
	{
		void GLInit();
		void RenderFrame(FrameEventArgs e);
		void GLDone();
	}
}

