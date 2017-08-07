using System;
using Core=Dibuixos.Core;
using OpenTK.Graphics.OpenGL;
using System.Drawing;

namespace Dibuixos.Demo
{
	internal class DibuixWindowDemo : Dibuixos.DibuixWindowBase
	{
		public DibuixWindowDemo (Core.Arguments argArgs):base(argArgs)
		{
		}

		protected override void RenderSplash ()
		{
			GL.ClearColor (Color.MidnightBlue);
			GL.Clear(ClearBufferMask.ColorBufferBit);
			SwapBuffers ();
		}

		protected override void LoopLoadValue (Core.CoRoutine argR, object argValue)
		{
			ExitIfAnyKey ();
		}

		private void ExitIfAnyKey()
		{
			if (IsAnyKey ())
				Exit ();
		}

		protected override System.Collections.IEnumerator CoRoutineLoad ()
		{
			yield return base.CoRoutineLoad ();

//			for (;;) {
//				ExitIfAnyKey ();
//				yield return null;
//			}
			yield break;
		}

		protected override void OnRenderFrame (OpenTK.FrameEventArgs e)
		{
			RenderSplash ();
		}

		protected override void OnUpdateFrame (OpenTK.FrameEventArgs e)
		{
			base.OnUpdateFrame (e);
			ExitIfAnyKey ();
		}
	}
}

