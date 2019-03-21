using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Core
{
    public interface ICtrCoRoutineAsyncUpdater
    {
        bool Finished { get; set; }
        GameTime GameTime { get; }

        Task Yield(bool argFinished);
    }
}
