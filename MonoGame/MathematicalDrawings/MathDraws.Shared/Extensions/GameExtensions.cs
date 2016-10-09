using System;
using Microsoft.Xna.Framework;
using Core=MathDraws.Shared.Core;

namespace MathDraws.Shared.Extensions
{
	public static class GameExtensions
	{
		public static void Attach<T>(this Game argGame,T argService)
		{
			argGame.Services.AddService(argService);

			var pComponent=argService as IGameComponent;

			if (pComponent!=null)
				argGame.Components.Add(pComponent);
		}
	}
}

