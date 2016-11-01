using System;
using Microsoft.Xna.Framework;

namespace MathDraws.Shared
{
	public class TimeStuffUpdate : GameComponent
	{
		public int Rate { get; set; }
		public int EllapseTime { get; set; }
		public Action<GameTime> UpdateRate{ get; set; }
		public Action<GameTime> UpdateFinish{ get; set; }

		private int mRateAct;
		private int mTime;

		public TimeStuffUpdate (Game argGame):base(argGame)
		{
			mRateAct = mTime = 0;
		}

		public override void Update (GameTime gameTime)
		{
			mRateAct += gameTime.ElapsedGameTime.Milliseconds;
			mTime +=gameTime.ElapsedGameTime.Milliseconds;

			if (mRateAct > Rate) {
				mRateAct = mRateAct % Rate;
				UpdateRate?.Invoke (gameTime);
			}
			if (mTime > EllapseTime) {
				mTime = mTime % EllapseTime;
				UpdateFinish?.Invoke (gameTime);
			}
		}
	}
}

