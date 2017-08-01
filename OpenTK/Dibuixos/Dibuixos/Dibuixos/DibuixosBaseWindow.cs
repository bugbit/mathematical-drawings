using System;
using System.Drawing;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace Dibuixos
{
	public class DibuixosBaseWindow : GameWindow
	{
		public Matrix4 ProjectionMatrix { get; private set; }

		public DibuixosBaseWindow ()
		{
		}

		protected override void OnResize (EventArgs e)
		{
			var pClientRectangle = ClientRectangle;

			GL.Viewport(pClientRectangle.X, pClientRectangle.Y, pClientRectangle.Width, pClientRectangle.Height);
			ProjectionMatrix=Matrix4.CreateOrthographicOffCenter(pClientRectangle.X, pClientRectangle.Width, pClientRectangle.Y, pClientRectangle.Height, -1.0f, 1.0f);
		
			base.OnResize (e);
		}
	}
}

