using System;

#if !MINIMAL
using System.Drawing;
#endif
using OpenTK;
using OpenTK.Platform;
using OpenTK.Graphics;

#if GLES10
using OpenTK.Graphics.ES10

#elif GLES11
using OpenTK.Graphics.ES11;

#elif GLES20
using OpenTK.Graphics.ES20;

#elif GLES30
using OpenTK.Graphics.ES30;

#elif GLES31
using OpenTK.Graphics.ES31;

#else
using OpenTK.Graphics.OpenGL;
#endif

namespace Dibuixos.Shared.Dibuix.Presentacio
{
	public class DibPresentacio : DibuixBase
	{
		public DibPresentacio ()
		{
		}

		#region implemented abstract members of DibuixBase

		public override void Load (EventArgs e)
		{			
		}

		public override void Unload (EventArgs e)
		{			
		}

		public override void RenderFrame (OpenTK.FrameEventArgs e)
		{			
		}

		public override void UpdateFrame (OpenTK.FrameEventArgs e)
		{
		}

		#endregion
	}
}

