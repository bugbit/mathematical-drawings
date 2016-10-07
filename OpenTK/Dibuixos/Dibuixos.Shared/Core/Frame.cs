using System;
using OpenTK;

namespace Dibuixos.Shared.Core
{
	public abstract class Frame : IFrame,IFrameEnd,IFrameLoad
	{
		public event EventHandler FrameEnd;

		public abstract void RenderFrame(FrameEventArgs e);
		public abstract void UpdateFrame(FrameEventArgs e);
		public abstract void Load(EventArgs e);
		public abstract void Unload(EventArgs e);

		virtual protected void OnFrameEnd()
		{
			FrameEnd.Invoke (this, EventArgs.Empty);
		}
	}
}

