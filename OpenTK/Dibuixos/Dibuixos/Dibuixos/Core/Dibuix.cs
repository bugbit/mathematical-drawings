using OpenTK;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Core
{
    public class Dibuix
    {
        private static Dictionary<GameWindow, Double> mGamesInTime = new Dictionary<GameWindow, double>();

        public static void ApplyArgsAndProperties(GameWindow argGame, DibuixArgs argArgs)
        {
            var pDibuixAttr = GetDibuixAttr(argGame);

            if (pDibuixAttr != null)
            {
                argGame.Title = Properties.Resources.ResourceManager.GetString(pDibuixAttr.ResTitle);
                if (pDibuixAttr.DefaultCycle && argArgs.IsScreenSaver)
                {
                    int pCycle = argArgs.Cycle * 60;

                    argGame.UpdateFrame += (s, e) =>
                    {
                        var pGame = (GameWindow)s;

                        if (GetGameInTime(pGame, e.Time) > pCycle)
                            pGame.Exit();
                    };
                }
            }
        }

        public static DibuixAttribute GetDibuixAttr(object argDibuix)
        {
            return argDibuix.GetType().GetCustomAttributes(typeof(DibuixAttribute), false).Cast<DibuixAttribute>().FirstOrDefault();
        }

        public static double GetGameInTime(GameWindow argGame, double argUpdateTime = 0)
        {
            double pTime;

            mGamesInTime.TryGetValue(argGame, out pTime);
            if (argUpdateTime > 0)
            {
                pTime += argUpdateTime;
                mGamesInTime[argGame] = pTime;
            }

            return pTime;
        }
    }
}
