using System;
using Microsoft.Xna.Framework;
using MathDraws.Shared.Core;

namespace MathDraws.Shared.States.Intro
{
	public class IntroState: Core.GameComponentState
	{
		public IntroState (Game argGame) : base (argGame)
		{
		}

		public override void Enter (GameTime gameTime)
		{
			var pDibuixos = Game.Services.GetService<IDibuixosService> ();

			//mSplash = new MathDraws.Shared.Components.SplashComponent (Game);
			//Game.Components.Add (mSplash);
			//mFrames = new MathDraws.Shared.Components.FramesIntoComponent(Game);
			//Game.Components.Add(mFrames);
			pDibuixos.Chars.Font = pDibuixos.FontChars;
			pDibuixos.CharsPi = new MathDraws.Shared.Entity.clsCharsPi { X = 0, Y = 0, Pos = 0 };
			pDibuixos.TheTimeStuffUpdate.Rate = 90;
			pDibuixos.TheTimeStuffUpdate.EllapseTime = 9000;
			pDibuixos.TheTimeStuffUpdate.UpdateRate = SlowPiUpdate;
			pDibuixos.TheTimeStuffUpdate.UpdateFinish = (g) => pDibuixos.TheTimeStuffUpdate.Rate -= 10;
			Game.Components.Add (pDibuixos.Chars);
			Game.Components.Add (pDibuixos.TheTimeStuffUpdate);
			base.Enter (gameTime);
		}

		public void SlowPiUpdate(GameTime gameTime)
		{
			var pDibuixos = Game.Services.GetService<IDibuixosService> ();
			var pChar = pDibuixos.Chars;
			var pCharPi = pDibuixos.CharsPi;

			pChar.Texts [pCharPi.Y, pCharPi.X] = pDibuixos.PiStr [pCharPi.Pos++];
			if (pCharPi.X++ >= pChar.DimTotal.X-1) {
				pCharPi.X = 0;
				if (pCharPi.Y++ > pChar.DimTotal.Y)
					pCharPi.Y = 0;
			}
		}
	}
}

