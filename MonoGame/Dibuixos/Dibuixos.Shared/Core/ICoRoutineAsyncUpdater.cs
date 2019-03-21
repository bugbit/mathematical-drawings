using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Core
{
    public interface ICoRoutineAsyncUpdater : ICtrCoRoutineAsyncUpdater
    {
        Task Update(GameTime gameTime);
    }
}
