using System;
namespace Dibuixos.Shared.Core
{
	public class ArgumentException : DibuixosException
	{
		public ArgumentException()
		{
		}

		public ArgumentException(Exception ex, string argMsg) : base(ex, argMsg) { }
	}
}
