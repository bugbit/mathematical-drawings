using System;

namespace Dibuixos.Core
{
	public class RenderFrameNull : IRenderFrame
	{
		private static Lazy<RenderFrameNull> mInstance=new Lazy<RenderFrameNull>(()=>new RenderFrameNull());

		private RenderFrameNull(){}

		public static RenderFrameNull Instance=>mInstance.Value;

		#region IRenderFrame implementation
		public void GLInit ()
		{
		}
		public void RenderFrame (OpenTK.FrameEventArgs e)
		{
		}
		public void GLDone ()
		{
		}
		#endregion
		
	}
}

