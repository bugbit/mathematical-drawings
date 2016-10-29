using System;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace MathDraws.Shared.Components
{
	public class SplashComponent : Microsoft.Xna.Framework.DrawableGameComponent
	{
		Texture2D mTexture;

		public SplashComponent (Game argGame):base(argGame)
		{
		}

		protected override void LoadContent ()
		{
			mTexture = Game.Content.Load<Texture2D> (@"Images/cartadeajuste");
		}

		public override void Draw (Microsoft.Xna.Framework.GameTime gameTime)
		{
			using (var pSP = new SpriteBatch(Game.GraphicsDevice))
			{
				pSP.Begin();
				pSP.Draw(mTexture, Vector2.Zero, Color.White);
				pSP.End();
			}
			base.Draw (gameTime);
		}

		protected override void UnloadContent ()
		{
			mTexture.Dispose ();
		}
	}
}

