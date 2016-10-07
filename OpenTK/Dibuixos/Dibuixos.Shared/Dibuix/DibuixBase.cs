using System;
using OpenTK;

namespace Dibuixos.Shared.Dibuix
{
	public abstract class DibuixBase: Core.Frame,IDibuix
	{
		public DibuixOptions Options{ get; set; }
	}
}

