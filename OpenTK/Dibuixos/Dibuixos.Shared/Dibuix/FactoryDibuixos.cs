using System;
using System.Collections.Generic;

namespace Dibuixos.Shared.Dibuix
{
	public class FactoryDibuixos
	{
		private static readonly Lazy<FactoryDibuixos> mInstance=new Lazy<FactoryDibuixos>(()=>new FactoryDibuixos());

		private static readonly Func<IDibuix> mPresentacio=()=>new  Presentacio.DibPresentacio();
		private static readonly Func<IDibuix> mMenu = () => new Menu.DibMenu ();

		public Func<IDibuix> Presentacio=>mPresentacio;
		public Func<IDibuix> Menu=>mMenu;

		private Dictionary<string,Func<IDibuix>> mMapNameDibuixos=new Dictionary<string, Func<IDibuix>>
		{
			{ "presentacio",mPresentacio  }
		};

		private List<Func<IDibuix>> mDibuixosDemo= new List<Func<IDibuix>>
		{
		};

		public static FactoryDibuixos Instance=> mInstance.Value;

		private FactoryDibuixos ()
		{
		}

		public IList<Func<IDibuix>> DibuixosDemo=>mDibuixosDemo;

		public IDibuix GetDibuix(string argName)
		{
			Func<IDibuix> pDib;

			if (!mMapNameDibuixos.TryGetValue(argName,out pDib))
				throw new Core.DibuixosException($"Dibuix '{argName}' not found");

			return pDib.Invoke();
		}
	}
}

