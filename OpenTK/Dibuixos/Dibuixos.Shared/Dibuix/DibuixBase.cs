using System;
using OpenTK;

namespace Dibuixos.Shared.Dibuix
{
	public abstract class DibuixBase: IDibuix
	{
		public DibuixOptions Options{ get; set; }
		public IEndDib EndDib { get; set;}
		public abstract void Load(EventArgs e);
		protected abstract void UnloadInternal ();
		public abstract void RenderFrame (FrameEventArgs e);
		public abstract void UpdateFrame(FrameEventArgs e);

		public virtual void OnEnd(EventArgs e)
		{
			EndDib.End (this);
		}	

		public virtual void Unload(EventArgs e)
		{
			UnloadInternal ();
			OnEnd (e);
		}	
	}
}

