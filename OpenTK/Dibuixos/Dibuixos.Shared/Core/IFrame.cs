using System;
using OpenTK;

namespace Dibuixos.Shared.Core
{
	public interface IFrame
	{
		void RenderFrame(FrameEventArgs e);
		void UpdateFrame(FrameEventArgs e);
	}
}

