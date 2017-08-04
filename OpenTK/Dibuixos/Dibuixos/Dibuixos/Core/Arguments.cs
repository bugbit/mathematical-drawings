using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Core
{
    public class Arguments
    {
        public static readonly string[] cArgsHelp = new string[] { "--help", "-h", "/?" };
        public static readonly string[] cArgsResolution = new string[] { "--resolution", "-r" };

        public const string cArghelp = "-h";
        public int Width { get; set; } = 800;
        public int Height { get; set; } = 600;

        public bool FullScreen { get; set; } = false;
        public bool Help { get; set; } = false;
        public string Dibuix { get; set; }
        public string[] Args { get; set; }

        public static Arguments Parse(string[] args)
        {
            var pArgs = new Arguments();
            int pIdxApp = 0;
            var pLen = args.Length;

            pArgs.Dibuix = null;
            pArgs.Args = new string[0];
            for (; pIdxApp < pLen; pIdxApp++)
            {
                var pArg = args[pIdxApp];

                if (cArgsHelp.Contains(pArg, StringComparer.InvariantCultureIgnoreCase))
                {
                    pArgs.Help = true;

                    break;
                }
                else if (cArgsResolution.Contains(pArg, StringComparer.InvariantCultureIgnoreCase))
                {
                    var pRes = args[++pIdxApp];
                    var pDims = pRes.Split('x');

                    if (pDims.Length != 2)
                        throw new Exception("Format error");

                    pArgs.Width = int.Parse(pDims[0]);
                    pArgs.Height = int.Parse(pDims[1]);
                }
                else
                {
                    if (!pArg.StartsWith("-"))
                    {
                        pArgs.Dibuix = pArg;
                        pIdxApp++;
                    }
                    pArgs.Args = args.Skip(pIdxApp).ToArray();
                }
            }


            return pArgs;
        }
    }
}
