using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace MathDraws.Shared.Extensions
{
	public static class SpriteFontExtensions
	{
		// Resumen:
		//     Returns the width and height of a string as a Vector2.
		//
		// Parámetros:
		//   text:
		//     The string to measure.
		public static Vector2 MeasureMax(this SpriteFont argFont)
		{
			var pMeasure = new Vector2();

			foreach (var pChar in argFont.Characters)
			{
				var pMeasureChar = argFont.MeasureChar(pChar);

				if (pMeasure.X < pMeasureChar.X)
					pMeasure.X = pMeasureChar.X;
				if (pMeasure.Y < pMeasureChar.Y)
					pMeasure.Y = pMeasureChar.Y;
			}

			return pMeasure;
		}

		public static Vector2 MeasureChar(this SpriteFont argFont, char argChar)
		{
			return argFont.MeasureString(argChar.ToString());
		}
	}
}

