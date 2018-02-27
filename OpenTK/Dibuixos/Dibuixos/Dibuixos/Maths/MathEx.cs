using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Maths
{
    public static class MathEx
    {
        public static dynamic SumaDeGauss(dynamic n, dynamic a1, dynamic an)
        {
            return n * (a1 + an) / 2;
        }
    }
}
