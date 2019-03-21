using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;

namespace Dibuixos.Core
{
    public class CoRoutineAsyncUpdater : ICoRoutineAsyncUpdater
    {
        private Func<ICtrCoRoutineAsyncUpdater, Task> mUpdater;
        private Task<Func<ICtrCoRoutineAsyncUpdater, Task>> mUpdaterTask;

        public CoRoutineAsyncUpdater(Func<ICtrCoRoutineAsyncUpdater, Task> argUpdater)
        {
            mUpdater = argUpdater;
        }

        public bool Finished { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        public GameTime GameTime => throw new NotImplementedException();

        public Task Update(GameTime gameTime)
        {
            throw new NotImplementedException();
        }

        public Task Yield(bool argFinished)
        {
            throw new NotImplementedException();
        }
    }
}
