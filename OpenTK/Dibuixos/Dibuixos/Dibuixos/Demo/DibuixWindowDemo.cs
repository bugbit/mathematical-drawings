using System;
using Core=Dibuixos.Core;

namespace Dibuixos.Demo
{
	internal class DibuixWindowDemo : Dibuixos.DibuixWindowBase
	{
		public DibuixWindowDemo (Core.Arguments argArgs):base(argArgs)
		{
		}

		protected override void OnLoad (EventArgs e)
		{
			base.OnLoad (e);
			mRenderFrame.Render = new SplashRender ();
		}

		protected override void OnUpdateFrame (OpenTK.FrameEventArgs e)
		{
			base.OnUpdateFrame (e);
			ExitIfAnyKey ();
		}
	}
}

