using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Dibuixos.Core
{
    public class DibuixArgOption
    {
        public string Option { get; private set; }
        public string OptionShort { get; private set; }
        public int NumArgs { get; private set; } = 1;

        public DibuixArgOption(string argOption, int argNumArgs = 1)
        {
            var pSplitOpt = argOption.Split('|');

            Option = pSplitOpt[0];
            if (pSplitOpt.Length == 2)
                OptionShort = pSplitOpt[1];
            NumArgs = argNumArgs;
        }
    }
}
