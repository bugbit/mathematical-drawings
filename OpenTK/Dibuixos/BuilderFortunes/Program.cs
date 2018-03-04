using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.IO.Compression;

namespace BuilderFortunes
{
    class Program
    {
        static void Main(string[] args)
        {
            var pFortunes = new List<string[]>();

            using (var pReader = new StringReader(Properties.Resources.fortunes))
            {
                string[] pFortune;

                while (ReadFortune(pReader, out pFortune))
                    pFortunes.Add(pFortune);
            }

            var pXmlSerializer = new XmlSerializer(pFortunes.GetType());

            using (var pFile = File.Create(Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "fortunes.xml.gz")))
            {
                using (var pZip = new GZipStream(pFile, CompressionMode.Compress))
                {
                    pXmlSerializer.Serialize(pZip, pFortunes);
                }
            }

            Console.WriteLine("fortune file write");
            Console.WriteLine("press ENTER to exit");
            Console.ReadLine();
        }

        private static bool ReadFortune(TextReader argReader, out string[] argFortune)
        {
            var pFortune = new List<string>();
            string pLine;

            while ((pLine = argReader.ReadLine()) != null && !pLine.Equals("%"))
            {
                pFortune.Add(pLine);
            }

            argFortune = pFortune.ToArray();

            return pFortune.Count > 0;
        }
    }
}
