using System;
using Dibuix=Dibuixos.Shared.Dibuix;

namespace Dibuixos.Shared.Core
{
	public abstract class NextDibBase : INextDibBase
	{
		protected DibuixosApp mApp;

		public NextDibBase (DibuixosApp argApp)
		{
			mApp = argApp;
		}

		#region IEndDib implementation

		public void End (Dibuix.IDibuix argDib)
		{
			mApp.DeAsign ();

			var pDib = NextDib ();

			if (pDib == null)
				mApp.Exit ();
			else
				mApp.Asign (pDib);
		}

		public abstract Dibuix.IDibuix FirstDib ();
		public abstract Dibuix.IDibuix NextDib ();

		#endregion
	}
}

