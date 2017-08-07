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
		public static readonly string[] cArgsFullScreen = new string[] { "--fullscreen", "-f" };
		public static readonly string[] cArgsDibuix = new string[] { "--dibuix", "-d" };

		public int Width { get; set; } = 800;

		public int Height { get; set; } = 600;

		public bool FullScreen { get; set; } = false;

		public bool Help { get; set; } = false;

		public string Dibuix { get; set; }

		public int NumPart{ get; set; }

		public string[] Args { get; set; }

		public static Arguments Parse (string[] args)
		{
			var pArgs = new Arguments ();
			int pIdxArgs = 0;
			var pLen = args.Length;

			pArgs.Dibuix = null;
			pArgs.Args = new string[0];
			for (; pIdxArgs < pLen; pIdxArgs++) {
				var pArg = args [pIdxArgs];
				int pNumPart;

				if (cArgsHelp.Contains (pArg, StringComparer.InvariantCultureIgnoreCase)) {
					pArgs.Help = true;

					break;
				} else if (cArgsResolution.Contains (pArg, StringComparer.InvariantCultureIgnoreCase)) {
					var pRes = args [++pIdxArgs];
					var pDims = pRes.Split ('x');

					if (pDims.Length != 2)
						throw new Exception ("Format error");

					pArgs.Width = int.Parse (pDims [0]);
					pArgs.Height = int.Parse (pDims [1]);
				} else if (cArgsFullScreen.Contains (pArg, StringComparer.InvariantCultureIgnoreCase)) {
					pArgs.FullScreen = true;
				} else if (cArgsDibuix.Contains (pArg, StringComparer.InvariantCultureIgnoreCase)) {
					pIdxArgs++;
					if (pIdxArgs >= pLen)
						throw new Exception ("Format error");
					pArgs.Dibuix = args [pIdxArgs++];
				} else if (int.TryParse (pArg, out pNumPart))
					pArgs.NumPart = pNumPart;
				else
					break;
			}
			pArgs.Args = args.Skip (pIdxArgs).ToArray ();

			return pArgs;
		}
	}
}
