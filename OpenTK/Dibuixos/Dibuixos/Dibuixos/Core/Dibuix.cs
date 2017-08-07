using System;
using System.Collections;

namespace Dibuixos.Core
{
	public class Dibuix
	{
		public string[] Args { get; private set;}

		public Dibuix (string[] argArgs)
		{
			Args = argArgs;
		}

		virtual public IEnumerator CoRoutineLoad()
		{
			yield break;
		}
	}
}

