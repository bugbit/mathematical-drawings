using System;

namespace Dibuixos.Shared.Core
{
	public interface IFrameLoad
	{
		void Load(EventArgs e);
		void Unload(EventArgs e);
	}
}

