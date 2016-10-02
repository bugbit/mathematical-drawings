using System;
using System.Collections.Generic;

using Dibuix=Dibuixos.Shared.Dibuix;

namespace Dibuixos.Shared.Core
{
	public class NextDibDemo : NextDibBase
	{
		private IEnumerator<Func<Dibuix.IDibuix>> mEnum;

		public NextDibDemo (DibuixosApp argApp):base(argApp)
		{
			mEnum = Dibuix.FactoryDibuixos.Instance.DibuixosDemo.GetEnumerator();
		}

		#region implemented abstract members of NextDibBase

		public override Dibuix.IDibuix FirstDib ()
		{
			mEnum.MoveNext ();

			return mEnum.Current.Invoke ();
		}

		public override Dibuix.IDibuix NextDib ()
		{
			if (!mEnum.MoveNext ()) 
			{
				if (mApp.Args.Flags.HasFlag (Arguments.EFlags.Loop)) {
					mEnum.Reset ();

					return FirstDib ();
				}
			}

			return mEnum.Current.Invoke ();
		}

		#endregion
	}
}

