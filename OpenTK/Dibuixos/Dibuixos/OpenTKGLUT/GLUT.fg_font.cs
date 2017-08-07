using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.Compression;
using System.Xml.Serialization;

namespace OpenTKGLUT
{
	static partial class GLUT
	{
		public const int GLUT_STROKE_ROMAN = 0;
		public const int GLUT_STROKE_MONO_ROMAN = 1;

		private static SFG_Fonts fgFonts = null;

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
			if (font == GLUT_STROKE_ROMAN)
				return fgFonts.StrokeRoman;
			if (font == GLUT_STROKE_MONO_ROMAN)
				return fgFonts.StrokeMonoRoman;

			return null;
		}



		/*
 * Draw a stroke character
 */
		public static void glutStrokeCharacter (int fontID, int character)
		{
			/*
			const SFG_StrokeChar *schar;
			const SFG_StrokeStrip *strip;
			int i, j;
			SFG_StrokeFont* font;

			font = fghStrokeByID( fontID );
			if (!font)
			{
				return;
			}
			freeglut_return_if_fail( character >= 0 );
			freeglut_return_if_fail( character < font->Quantity );

			schar = font->Characters[ character ];
			freeglut_return_if_fail( schar );
			strip = schar->Strips;

			for( i = 0; i < schar->Number; i++, strip++ )
			{
				glBegin( GL_LINE_STRIP );
				for( j = 0; j < strip->Number; j++ )
					glVertex2f( strip->Vertices[ j ].X, strip->Vertices[ j ].Y );
				glEnd( );

				if (StrokeFontDrawJoinDots)
				{
					glBegin( GL_POINTS );
					for( j = 0; j < strip->Number; j++ )
						glVertex2f( strip->Vertices[ j ].X, strip->Vertices[ j ].Y );
					glEnd( );
				}
			}
			glTranslatef( schar->Right, 0.0, 0.0 );
			*/
		}
	}
}
