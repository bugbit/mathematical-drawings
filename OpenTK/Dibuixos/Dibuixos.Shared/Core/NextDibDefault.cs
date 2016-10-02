using System;
using Dibuix=Dibuixos.Shared.Dibuix;

namespace Dibuixos.Shared.Core
{
	public class NextDibDefault : NextDibBase
	{
		public NextDibDefault (DibuixosApp argApp):base(argApp)
		{
		}

		#region implemented abstract members of NextDibBase

		public override Dibuix.IDibuix FirstDib ()
		{
			return Dibuix.FactoryDibuixos.Instance.Presentacio.Invoke();
		}

		public override Dibuix.IDibuix NextDib ()
		{
			return null;
		}

		#endregion
	}
}

