using System;
using Microsoft.Xna.Framework;

namespace MathDraws.Shared.Core
{
	public interface IParams
	{
		bool IsHelp { get; set; }
		bool IsLoop { get; set; }
		bool IsDemo { get; set; }
	}
}
