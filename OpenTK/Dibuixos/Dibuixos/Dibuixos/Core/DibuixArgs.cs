using OpenTK;
using OpenTK.Graphics;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Dibuixos.Core
{
    public class DibuixArgs
    {
        private readonly static DibuixArgOption[] mDefaultOptsNumArgs = new[]
        {
            new DibuixArgOption("resolution|r"),
            new DibuixArgOption("fullscreen|f",0),
            new DibuixArgOption("screensaver|f",0),
            new DibuixArgOption("cycle|f",1)
        };

        private Dictionary<string, string[]> mOpts = new Dictionary<string, string[]>();
        private int[] mResolution;

        public DibuixArgs(Dictionary<string, string[]> argOpts)
        {
            mOpts = argOpts;
            CreateOptResolution("resolution");
            GetOpt("fullscreen", v => FullScreen = v);
        }

        public bool FullScreen { get; private set; }

        public GameWindowFlags GameWindowFlags => (FullScreen) ? GameWindowFlags.Fullscreen : GameWindowFlags.Default;

        public GraphicsMode GraphicsMode
        {
            get
            {
                try
                {
                    return (FullScreen && mResolution.Length >= 3) ? new GraphicsMode(new ColorFormat(mResolution[2])) : GraphicsMode.Default;
                }
                catch
                {
                    return GraphicsMode.Default;
                }
            }
        }

        public bool GetOpt(string argOpt, Action<string> argLetOptValue)
        {
            string[] pValue;

            if (!mOpts.TryGetValue(argOpt, out pValue) || pValue.Length > 0)
                return false;

            argLetOptValue.Invoke(pValue[0]);

            return true;
        }

        public bool GetOpt(string argOpt, Action<bool> argLetValue)
        {
            var pRet = false;

            GetOpt
            (
                argOpt, delegate (string argValueStr)
                {
                    bool pValue;

                    pRet = bool.TryParse(argValueStr, out pValue);

                    if (pRet)
                        argLetValue.Invoke(pValue);
                }
            );

            return pRet;
        }

        public int Width(int argDefault, bool? argDefaultOnlyWindowed)
        {
            int? pWidth = mResolution?[0];

            if (!pWidth.HasValue)
            {
                if (!argDefaultOnlyWindowed.HasValue || argDefaultOnlyWindowed.Value == !FullScreen)
                    pWidth = argDefault;
            }

            return pWidth ?? DisplayDevice.Default.Width;
        }

        public int Height(int argDefault, bool? argDefaultOnlyWindowed)
        {
            int? pHeight = mResolution?[0];

            if (!pHeight.HasValue)
            {
                if (!argDefaultOnlyWindowed.HasValue || argDefaultOnlyWindowed.Value == !FullScreen)
                    pHeight = argDefault;
            }

            return pHeight ?? DisplayDevice.Default.Height;
        }

        public static DibuixArgs Parse(string[] argArgs, IEnumerable<DibuixArgOption> argOptsNumArgs = null)
        {
            var pOpts = new Dictionary<string, string[]>();
            var pQuery = (argOptsNumArgs == null) ? mDefaultOptsNumArgs : mDefaultOptsNumArgs.Concat(argOptsNumArgs);
            var pDict = new Dictionary<string, DibuixArgOption>();

            foreach (var q in pQuery)
            {
                if (!string.IsNullOrWhiteSpace(q.Option))
                    pDict.Add(q.Option, q);
                if (!string.IsNullOrWhiteSpace(q.OptionShort))
                    pDict.Add(q.OptionShort, q);
            }
            for (var i = 0; i < argArgs.Length; i++)
            {
                var pOpt = argArgs[i];

                if (pOpt.StartsWith("-"))
                {
                    var pOpt2 = pOpt.Substring(1);
                    DibuixArgOption pDOpt;

                    if (!pDict.TryGetValue(pOpt2, out pDOpt))
                    {
                        Trace.TraceWarning($"option {pOpt} unrecognized");

                        continue;
                    }

                    if (pDOpt.NumArgs == 0)
                        pOpts[pOpt2] = new string[] { Boolean.TrueString };
                    else
                    {
                        var pValue = new string[pDOpt.NumArgs];

                        argArgs.CopyTo(pValue, i);
                        pOpts[pOpt2] = pValue;

                        i += pDOpt.NumArgs;
                    }
                }
            }

            return new DibuixArgs(pOpts);
        }

        private bool CreateOptResolution(string argOpt)
        {
            string[] pValue;

            if (!mOpts.TryGetValue(argOpt, out pValue) || pValue.Length > 1)
                return false;

            var pSplit = pValue[0].Split('x');

            if (pSplit.Length < 2)
                return false;

            try
            {
                mResolution = pSplit.Select(v => int.Parse(v)).ToArray();

                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
