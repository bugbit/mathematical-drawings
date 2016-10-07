using System;

using OpenTK;

namespace Dibuixos.Shared.Dibuix
{
	public interface IDibuix : Core.IFrame,Core.IFrameEnd,Core.IFrameLoad
	{
		DibuixOptions Options{ get; set;}
	}
}

