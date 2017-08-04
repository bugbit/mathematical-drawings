using System;

namespace OpenTKGLUT
{
    public static partial class GLUT
    {
        public class SFG_Font
        {
            public string Name { get; set; }         /* The source font name             */
            public int Quantity { get; set; }    /* Number of chars in font          */
            public int Height { get; set; }       /* Height of the characters         */
            public byte[][] Characters { get; set; }   /* The characters mapping           */

            public float xorig { get; set; }
            public float yorig { get; set; } /* Relative origin of the character */
        };
        public class SFG_StrokeVertex
        {
            public float X { get; set; }
            public float Y { get; set; }
        }

        public class SFG_StrokeStrip
        {
            public int Number { get; set; }
            public SFG_StrokeVertex[] Vertices { get; set; }
        }

        public class SFG_StrokeChar
        {
            public float Right { get; set; }
            public int Number { get; set; }
            public SFG_StrokeStrip[] Strips { get; set; }
        }

        public class SFG_StrokeFont
        {
            public string Name { get; set; }
            /* The source font name      */
            public int Quantity { get; set; }
            /* Number of chars in font   */
            public float Height { get; set; }
            /* Height of the characters  */
            public SFG_StrokeChar[] Characters { get; set; }
        }

        public class SFG_Fonts
        {
            public SFG_Font FontFixed8x13 { get; set; }
            public SFG_Font FontFixed9x15 { get; set; }
            public SFG_Font FontHelvetica10 { get; set; }
            public SFG_Font FontHelvetica12 { get; set; }
            public SFG_Font FontHelvetica18 { get; set; }
            public SFG_Font FontTimesRoman10 { get; set; }
            public SFG_Font FontTimesRoman24 { get; set; }
            public SFG_StrokeFont StrokeRoman { get; set; }
            public SFG_StrokeFont StrokeMonoRoman { get; set; }
        };
    }
}

