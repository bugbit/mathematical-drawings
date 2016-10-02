using System;

namespace Dibuixos.Shared.Core
{
	public class DibuixosException : Exception
	{
		public DibuixosException ()
		{
		}

		public DibuixosException(Exception ex, string argMsg):base(argMsg,ex){}

		public DibuixosException(string argMsg):base(argMsg){}
	}
}

