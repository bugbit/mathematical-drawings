using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Dibuixos.Core
{
    public class Fortunes
    {
        private static readonly Lazy<Fortunes> mInstance = new Lazy<Fortunes>(() => new Fortunes());

        public static Fortunes Instance => mInstance.Value;

        public string[][] DbFortunes { get; private set; }

        private Fortunes()
        {
            var pXmlSerializer = new XmlSerializer(typeof(string[][]));

            using (var Stream = new MemoryStream(Properties.Resources.fortunes_xml))
            {
                using (var pZip = new GZipStream(Stream, CompressionMode.Decompress))
                {
                    DbFortunes = (string[][])pXmlSerializer.Deserialize(pZip);
                }
            }
        }
    }
}
