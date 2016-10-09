using System;
using Microsoft.Xna.Framework;

namespace MathDraws.Shared.Core
{
	public class GameComponentState : GameComponent, IState
	{
		public GameComponentState(Game argGame) : base(argGame) { }

		virtual public void Enter(GameTime gameTime)
		{
		}

		virtual public void Exit(GameTime gameTime)
		{
		}

		virtual public void Obscure(GameTime gameTime)
		{
		}

		virtual public void Reveal(GameTime gameTime)
		{
		}
	}
}
