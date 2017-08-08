using System;
using OpenTK;

namespace Dibuixos.Core
{
	public class ManagerRenderFrame
	{
		private IRenderFrame mRender = RenderFrameNull.Instance;

		public IRenderFrame Render { 
			get { return mRender; } 
			set 
			{ 
				if (value == null)
					throw new ArgumentNullException ("value");
				mRender.GLDone ();
				value.GLInit();
				mRender = value; 
			}
		}

		public void RenderFrame (FrameEventArgs e)
		{
			mRender.RenderFrame (e);
		}
	}
}

