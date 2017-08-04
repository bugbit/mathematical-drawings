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
        private static SFG_Fonts fgFonts = null;
        private static void fgLoadFonts()
        {
            using (var pFile = new MemoryStream(Dibuixos.Properties.Resources.fgFonts_xml))
            {
                using (var pZip = new GZipStream(pFile, CompressionMode.Decompress))
                {
                    var pXml = new XmlSerializer(typeof(SFG_Fonts));

                    fgFonts = (SFG_Fonts)pXml.Deserialize(pZip);
                }
            }
        }
    }
}
