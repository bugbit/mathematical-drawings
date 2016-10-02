using System;
using Dibuix=Dibuixos.Shared.Dibuix;

namespace Dibuixos.Shared.Core
{
	/// <summary>
	///
	///
	/// dibuixos[options] [dibuixo]
	///
	///
	/// options:
	///  --help : show usage
	///  -r<width> x<height>x[bpp] : resolucion.Por defecto es -r800x600
	///  -f : fullscreen
	///  -l : play demo in infinite loop
	///
	/// dibuixo:
	///  demo : All of dibuixos
	///  <dibuixo> : one of dibuixo (see README for more help)
	/// 
	/// </summary>
	public class Arguments
	{
		[Flags]
		public enum EFlags
		{
			Help = 0x1,
			FullScreen = 0x2,
			Loop = 0x4,
			Demo = 0x8,
			Default = 0x0
		};

		public int Width { get; set; } = 800;
		public int Height { get; set; } = 600;

		public bool FullScreen { get; set; }
		public EFlags Flags { get; set; } = EFlags.Default;
		public Dibuix.IDibuix DibArg { get; set; }

		public Arguments()
		{
		}

		public static Arguments Parse(string[] args)
		{
			var pArgs = new Arguments();

			foreach(var pArg in args)
			{
				try
				{
					if (pArg.StartsWith("--"))
					{
						var pArg2 = pArg.Substring(2);

						switch (pArg2)
						{
							case "help":
								pArgs.Flags |= EFlags.Help;

								return pArgs;
							case "r":
								var pDims = pArg2.Split('x');

								if (pDims.Length != 2)
									throw new Exception("Format error");

								pArgs.Width = int.Parse(pDims[0]);
								pArgs.Height = int.Parse(pDims[1]);
								break;
							case "f":
								pArgs.Flags |= EFlags.FullScreen;
								break;
							case "l":
								pArgs.Flags |= EFlags.Loop;
								break;
						}
					}
					else if (pArg == "demo")
						pArgs.Flags = EFlags.Demo;
					else
						pArgs.DibArg = Dibuix.FactoryDibuixos.Instance.GetDibuix(pArg);
				}
				catch (Exception ex)
				{
					throw new ArgumentException(ex, $"{pArg} optional error: {ex.Message}");
				}
			}

			return pArgs;
		}
	}
}
