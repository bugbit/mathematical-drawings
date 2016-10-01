using System;
namespace Dibuixos.Shared
{
	public class ArgumentException : Exception
	{
		public ArgumentException()
		{
		}

		public ArgumentException(Exception ex, string argMsg) : base(argMsg, ex) { }
	}
}
