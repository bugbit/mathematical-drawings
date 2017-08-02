using System;

namespace OpenTKGLUT
{
	public static partial class GLUT
	{
		private struct SFG_StrokeVertex
		{
			public float X, Y;
		}

		private struct SFG_StrokeStrip
		{
			public int Number;
			public SFG_StrokeVertex[] Vertices;

			public SFG_StrokeStrip(int Number,SFG_StrokeVertex[] Vertices)
			{
				this.Number=Number;
				this.Vertices=Vertices;
			}
		}

		private struct SFG_StrokeChar
		{
			public float Right;
			public int             Number;
			public SFG_StrokeStrip[] Strips;

			//public SFG_StrokeChar() { this.Number=0; this.Strips=null;}
			public SFG_StrokeChar(float Right,int Number,SFG_StrokeStrip[] Strips)
			{
				this.Right=Right;
				this.Number=Number;
				this.Strips=Strips;
			}
		}

		private struct SFG_StrokeFont
		{
			public string Name;
			/* The source font name      */
			public int Quantity;
			/* Number of chars in font   */
			public float Height;
			/* Height of the characters  */
			public SFG_StrokeChar[] Characters;

			public SFG_StrokeFont(string Name,int Quantity,float Height,SFG_StrokeChar[] Characters)
			{
				this.Name=Name;
				this.Quantity=Quantity;
				this.Height=Height;
				this.Characters=Characters;
			}
		}

		private static readonly SFG_StrokeChar SFG_StrokeCharNull;
	}
}

