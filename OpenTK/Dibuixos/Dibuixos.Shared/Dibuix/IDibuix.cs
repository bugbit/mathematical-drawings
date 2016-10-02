using System;

using OpenTK;

namespace Dibuixos.Shared.Dibuix
{
	public interface IDibuix
	{
		DibuixOptions Options{ get;}
		IEndDib EndDib { get; set;}
		void Load(EventArgs e);
		void Unload(EventArgs e);
		void RenderFrame(FrameEventArgs e);
		void UpdateFrame(FrameEventArgs e);
	}
}

