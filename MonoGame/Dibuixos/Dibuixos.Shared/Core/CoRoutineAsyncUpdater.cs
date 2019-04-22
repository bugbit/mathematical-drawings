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
        private TaskCompletionSource<GameTime> mSetUpdateCompleted;
        private TaskCompletionSource<bool> mSetFinishCompleted;

        public CoRoutineAsyncUpdater(Func<ICtrCoRoutineAsyncUpdater, Task> argUpdater)
        {
            mUpdater = argUpdater;
            mSetUpdateCompleted = new TaskCompletionSource<GameTime>();
            mSetFinishCompleted = new TaskCompletionSource<bool>();
        }

        public bool Finished { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        public GameTime GameTime => throw new NotImplementedException();

        public async Task Update(GameTime gameTime)
        {
            var pCompleted = mSetUpdateCompleted;

            mSetUpdateCompleted.SetResult(gameTime);

            var pFinishTask = mSetFinishCompleted?.Task;

            await pFinishTask;
        }

        public Task Yield(bool argFinished)
        {
            throw new NotImplementedException();
        }
    }
}
