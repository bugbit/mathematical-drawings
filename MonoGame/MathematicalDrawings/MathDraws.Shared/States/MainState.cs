using System;
using Microsoft.Xna.Framework;
using Core = MathDraws.Shared.Core;

namespace MathDraws.Shared.States
{
	public class MainState : Core.GameComponentState
	{
		private MathDraws.Shared.Components.SplashComponent mSplash;
		private MathDraws.Shared.Components.FramesIntoComponent mFrames;

		public MainState(Game argGame):base(argGame)
		{
		}

		public override void Enter(GameTime gameTime)
		{
			mSplash = new MathDraws.Shared.Components.SplashComponent (Game);
			Game.Components.Add (mSplash);
			//mFrames = new MathDraws.Shared.Components.FramesIntoComponent(Game);
			//Game.Components.Add(mFrames);
			base.Enter(gameTime);
		}

		public override void Exit(GameTime gameTime)
		{
			Game.Components.Remove(mFrames);
			base.Exit(gameTime);
		}
	}
}
