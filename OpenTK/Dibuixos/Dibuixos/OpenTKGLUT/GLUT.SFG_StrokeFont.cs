using System;

namespace OpenTKGLUT
{
	public static partial class GLUT
	{
		private struct SFG_StrokeFont
		{
			public string Name;
			/* The source font name      */
			public int Quantity;
			/* Number of chars in font   */
			public float Height;
			/* Height of the characters  */
			public SFG_StrokeChar[] Characters;
			/* The characters mapping    */
		}
	}
}

