using System;
using Dibuix=Dibuixos.Shared.Dibuix;

namespace Dibuixos.Shared.Core
{
	public interface INextDibBase : Dibuix.IEndDib
	{
		Dibuix.IDibuix FirstDib();
		Dibuix.IDibuix NextDib();
	}
}

