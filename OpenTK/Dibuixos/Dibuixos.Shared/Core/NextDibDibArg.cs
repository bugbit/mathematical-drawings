using System;
using Dibuix=Dibuixos.Shared.Dibuix;

namespace Dibuixos.Shared.Core
{
	public class NextDibDibArg : NextDibBase
	{
		public NextDibDibArg (DibuixosApp argApp):base(argApp)
		{
		}

		#region implemented abstract members of NextDibBase

		public override Dibuix.IDibuix FirstDib ()
		{
			return mApp.Args.DibArg;
		}

		public override Dibuix.IDibuix NextDib ()
		{
			return null;
		}

		#endregion
	}
}

