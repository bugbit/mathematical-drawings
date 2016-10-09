using System;
using Microsoft.Xna.Framework;

namespace MathDraws.Shared.Core
{
	public interface IDibuixosService
	{
		bool IsLoop { get; set; }
		IStateManager StateManager { get; }
	}
}
