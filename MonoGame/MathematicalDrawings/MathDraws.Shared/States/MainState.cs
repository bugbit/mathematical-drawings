using System;
using Microsoft.Xna.Framework;
using Core = MathDraws.Shared.Core;
using Microsoft.Xna.Framework.Graphics;
using System.Threading.Tasks;
using MathDraws.Shared.Core;
using MathDraws.Shared.States.Intro;

namespace MathDraws.Shared.States
{
	public class MainState : Core.GameComponentState
	{
		//private MathDraws.Shared.Components.SplashComponent mSplash;
		//private MathDraws.Shared.Components.FramesIntoComponent mFrames;

		public MainState(Game argGame):base(argGame)
		{
		}

		public override void Enter(GameTime gameTime)
		{
			var pDibuixos = Game.Services.GetService<IDibuixosService> ();

			pDibuixos.StateManager.PushState (gameTime, new IntroState (Game), Modalities.Exclusive);
			base.Enter(gameTime);
		}

		public override void Exit(GameTime gameTime)
		{
			//Game.Components.Remove(mFrames);
			base.Exit(gameTime);
		}
	}
}
