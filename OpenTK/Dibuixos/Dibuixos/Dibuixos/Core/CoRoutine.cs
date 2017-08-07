using System;
using System.Collections.Generic;
using System.Collections;

namespace Dibuixos.Core
{
	public class CoRoutine
	{
		private Stack<IEnumerator> mCoRoutines=new Stack<IEnumerator>();

		public bool Finish { get; private set; }

		public CoRoutine ()
		{
		}

		public void Start(IEnumerator argCoRoutine)
		{
			mCoRoutines.Push (argCoRoutine);
		}

		public bool Loop(Action<CoRoutine,object> argLoopValue=null)
		{
			for(;;)
			{
				if (mCoRoutines.Count == 0) {
					Finish = true;

					return false;
				}

				var pCoRoutine = mCoRoutines.Peek ();

				if (!pCoRoutine.MoveNext ()) {
					mCoRoutines.Pop();
					continue;
				}

				var pValue= pCoRoutine.Current;
				var pCoRoutineNew = pValue as IEnumerator;

				if (pCoRoutineNew != null) {
					Start (pCoRoutineNew);
				} else
					argLoopValue?.Invoke (this, pValue);

				return true;
			}
		}
	}
}

