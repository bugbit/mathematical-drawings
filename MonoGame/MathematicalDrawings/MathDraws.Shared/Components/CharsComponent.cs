using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using MathDraws.Shared.Extensions;

namespace MathDraws.Shared.Components
{
	public class CharsComponent: DrawableGameComponent
	{
		public Vector2 DimChar { get; private set; }

		public Point DimTotal { get; private set; }

		public SpriteFont Font
		{ 
			get {
				return mFont;
			}
			set {
				mFont = value;
				var pDimMax = Font.MeasureMax ();
				var pGame = Game;

				DimChar = new Vector2 (pDimMax.X + 1, pDimMax.Y + 1);
				DimTotal = new Point ((int)pGame.GraphicsDevice.Viewport.Width / (int)DimChar.X, (int)pGame.GraphicsDevice.Viewport.Height / (int)DimChar.Y);
				Texts = new char[DimTotal.Y, DimTotal.X];
			}
		}

		private SpriteFont mFont;

		public char[,] Texts { get; private set; }

		public CharsComponent (Game argGame) : base (argGame)
		{
			Texts = null;
		}

		public override void Draw (GameTime gameTime)
		{
			var pPos = new Vector2 ();
			var pEnum = Texts.GetEnumerator ();

			using (var pBatch = new SpriteBatch (Game.GraphicsDevice)) {
				pBatch.Begin ();
				for (var h = DimTotal.Y; h > 0; h--, pPos.Y += DimChar.Y) {
					pPos.X = 0;
					for (var w = DimTotal.X; w > 0; w--, pPos.X += DimChar.X) {
						if (pEnum.MoveNext ()) {
							var pChar = (char)pEnum.Current;

							if (Font.Characters.Contains (pChar))
								pBatch.DrawString (Font, pChar.ToString (), pPos, Color.White);
						}
					}
				}
				pBatch.End ();
			}

			base.Draw (gameTime);
		}
	}
}

