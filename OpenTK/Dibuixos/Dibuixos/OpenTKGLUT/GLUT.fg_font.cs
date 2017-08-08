using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.Compression;
using System.Xml.Serialization;
using OpenTK.Graphics.OpenGL;

namespace OpenTKGLUT
{
	static partial class GLUT
	{
		public const int GLUT_STROKE_ROMAN = 0;
		public const int GLUT_STROKE_MONO_ROMAN = 1;

		private static SFG_Fonts fgFonts = null;
		private static bool StrokeFontDrawJoinDots=false;

		private static void fgLoadFonts ()
		{
			using (var pFile = new MemoryStream (Dibuixos.Properties.Resources.fgFonts_xml)) {
				using (var pZip = new GZipStream (pFile, CompressionMode.Decompress)) {
					var pXml = new XmlSerializer (typeof(SFG_Fonts));

					fgFonts = (SFG_Fonts)pXml.Deserialize (pZip);
				}
			}
		}

		/*
 * Matches a font ID with a SFG_StrokeFont structure pointer.
 * This was changed to match the GLUT header style.
 */
		private	 static SFG_StrokeFont fghStrokeByID (int font)
		{
			if (fgFonts == null)
				return null;
			if (font == GLUT_STROKE_ROMAN)
				return fgFonts.StrokeRoman;
			if (font == GLUT_STROKE_MONO_ROMAN)
				return fgFonts.StrokeMonoRoman;

			return null;
		}

		/*
 * Draw a stroke character
 */
		public static bool glutStrokeCharacter (int fontID, int character)
		{
			SFG_StrokeChar schar;
			SFG_StrokeStrip strip;
			int i, j;
			SFG_StrokeFont font;

			font = fghStrokeByID( fontID );
			if (font==null)
			{
				return true;
			}
			if( !(character >= 0 ))
				return false;
			if (!(character < font.Quantity))
				return false;

			schar = font.Characters[ character ];
			if( schar==null )
				return false;
			

			for( i = 0; i < schar.Number; i++ )
			{
				strip = schar.Strips[i];
				GL.Begin(PrimitiveType.LineStrip);
				for( j = 0; j < strip.Number; j++ )
					GL.Vertex2( strip.Vertices[ j ].X, strip.Vertices[ j ].Y );
				GL.End( );

				if (StrokeFontDrawJoinDots)
				{
					GL.Begin( PrimitiveType.Points );
					for( j = 0; j < strip.Number; j++ )
						GL.Vertex2( strip.Vertices[ j ].X, strip.Vertices[ j ].Y );
					GL.End( );
				}
			}
			GL.Translate( schar.Right, 0.0, 0.0 );

			return true;
		}

		public static void glutStrokeString( int fontID, string str )
		{
			int i, j;
			float length = 0.0f;
			SFG_StrokeFont font;

			font = fghStrokeByID( fontID );
			if (font==null)
			{
				return;
			}

			/*
     * Step through the string, drawing each character.
     * A newline will simply translate the next character's insertion
     * point back to the start of the line and down one line.
     */
			foreach( var c in str )
				if( c < font.Quantity )
				{
					if( c == '\n' )
					{
						GL.Translate ( -length, -( float )( font.Height ), 0.0 );
						length = 0.0f;
					}
					else  /* Not an EOL, draw the bitmap character */
					{
						SFG_StrokeChar schar = font.Characters[ (int)c ];
						if( schar!=null )
						{
							for( i = 0; i < schar.Number; i++ )
							{
								SFG_StrokeStrip strip = schar.Strips[i];

								GL.Begin( PrimitiveType.LineStrip );
								for( j = 0; j < strip.Number; j++ )
									GL.Vertex2( strip.Vertices[ j ].X,
										strip.Vertices[ j ].Y);

								GL.End( );
							}

							length += schar.Right;
							GL.Translate( schar.Right, 0.0, 0.0 );
						}
					}
				}
		}

		/*
 * Return the width in pixels of a stroke character
 */
		public static float glutStrokeWidthf( int fontID, int character )
		{
			SFG_StrokeChar schar;
			SFG_StrokeFont font;

			font = fghStrokeByID( fontID );
			if (font==null)
			{
				return 0;
			}
			if( !(character >= 0 ))
				return 0;
			if (!(character < font.Quantity))
				return 0;
			
			schar = font.Characters[ character ];
			if( schar==null )
				return 0;

			return schar.Right;
		}
		public static int glutStrokeWidth(int fontID, int character)
		{
			return ( int )( glutStrokeWidthf(fontID,character) + 0.5f );
		}

		/*
 * Return the width of a string drawn using a stroke font
 */
		public static float glutStrokeLengthf( int fontID, string str )
		{
			float length = 0.0f;
			float this_line_length = 0.0f;
			SFG_StrokeFont font;

			font = fghStrokeByID( fontID );
			if (font==null)
			{
				return 0;
			}

			foreach(var c in str)
				if( c < font.Quantity )
				{
					if( c == '\n' ) /* EOL; reset the length of this line */
					{
						if( length < this_line_length )
							length = this_line_length;
						this_line_length = 0.0f;
					}
					else  /* Not an EOL, increment the length of this line */
					{
						SFG_StrokeChar schar = font.Characters[ (int)c ];
						if( schar!=null )
							this_line_length += schar.Right;
					}
				}
			if( length < this_line_length )
				length = this_line_length;
			return length;
		}

		public static int glutStrokeLength( int fontID, string str )
		{
			return( int )( glutStrokeLengthf(fontID,str) + 0.5f );
		}

		/*
 * Returns the height of a stroke font
 */
		public static float glutStrokeHeight( int fontID )
		{
			SFG_StrokeFont font;

			font = fghStrokeByID( fontID );
			if (font==null)
			{
				return 0.0f;
			}
			return font.Height;
		}
	}
}
