using System;
using OpenTK;

namespace Dibuixos.Shared.Dibuix
{
	public class DibuixOptions
	{
		[Flags]
		public enum EFlags
		{
			Demo = 0x1,
		}

		public EFlags Flags{ get; set; }

		public Matrix4 ProjectionMatrix { get; set; }
	}
}

