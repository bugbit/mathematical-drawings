using System;
namespace OpenTKGLUT
{
	public static partial class GLUT
	{
		private static SFG_StrokeFont fgStrokeMonoRoman;

		private static void Makefgstroke_mono_roman()
		{
			SFG_StrokeStrip[] ch32st =
						new SFG_StrokeStrip[]
						{
							new SFG_StrokeStrip ( 0,new SFG_StrokeVertex[0] )
						};
			SFG_StrokeChar[] chars =
				new  SFG_StrokeChar[]
				{
					SFG_StrokeCharNull
				};

			fgStrokeMonoRoman= new SFG_StrokeFont("MonoRoman",128,152.381f,chars);
		}
		/* char: 0x20 */

//		private static readonly SFG_StrokeStrip[] ch32st =
//		new SFG_StrokeStrip[]
//		{
//			new SFG_StrokeStrip ( 0,new SFG_StrokeVertex[0] )
//		};

		//private static readonly SFG_StrokeChar ch32 = {104.762f,0,ch32st};
	}
}

