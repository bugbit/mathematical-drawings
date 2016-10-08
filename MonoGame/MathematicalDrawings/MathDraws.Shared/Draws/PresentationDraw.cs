using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MathDraws.Shared.Draws
{
	public class PresentationDraw : DrawableGameComponent
	{
		private SpriteFont mFont;
		private SpriteBatch mBatch;

		public PresentationDraw(Game argGame):base(argGame)
		{
		}

		public override void Initialize()
		{
			base.Initialize();
			mBatch = new SpriteBatch(Game.GraphicsDevice);
		}

		protected override void LoadContent()
		{
			mFont = Game.Content.Load<SpriteFont>("Fonts/Presentation");

			base.LoadContent();
		}

		public override void Draw(GameTime gameTime)
		{
			mBatch.Begin();
			mBatch.DrawString(mFont, "HelloWord", new Vector2(0, 0), Color.Red, 0, new Vector2(0, 0), 1f, SpriteEffects.None,0);
			mBatch.End();
			base.Draw(gameTime);
		}
	}
}
