using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Core = MathDraws.Shared.Core;

namespace MathDraws.Shared.Components
{
	/// <summary>
	/// This is a game component that implements IUpdateable.
	/// </summary>
	public class FramesIntoComponent : Microsoft.Xna.Framework.DrawableGameComponent
	{
		private Core.ManagerFrameImages mIntoFrames;
		private Vector2 mPos;

		public FramesIntoComponent(Game game)
			: base(game)
		{
			// TODO: Construct any child components here
		}

		/// <summary>
		/// Allows the game component to perform any initialization it needs to before starting
		/// to run.  This is where it can query for any required services and load content.
		/// </summary>
		public override void Initialize()
		{
			var pDemo = Game;

			mIntoFrames = new Core.ManagerFrameImages { FPS = 25 };
			mPos = new Vector2((pDemo.GraphicsDevice.Viewport.Width - 320) / 2, (pDemo.GraphicsDevice.Viewport.Height - 200) / 2);

			base.Initialize();
		}

		protected override void LoadContent()
		{
			mIntoFrames.LoadImages(Game.Content, @"Images\Intro\into{0}", 1, 12);
			base.LoadContent();
		}

		/// <summary>
		/// Allows the game component to update itself.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		public override void Update(GameTime gameTime)
		{
			mIntoFrames.Update(gameTime);

			base.Update(gameTime);
		}

		public override void Draw(GameTime gameTime)
		{
			using (var pSP = new SpriteBatch(Game.GraphicsDevice))
			{
				pSP.Begin();
				pSP.Draw(mIntoFrames.TextureCurrent, mPos, Color.White);
				pSP.End();
			}
			base.Draw(gameTime);
		}
	}
}
