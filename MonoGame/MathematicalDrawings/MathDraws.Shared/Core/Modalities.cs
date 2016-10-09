using System;
namespace MathDraws.Shared.Core
{
	public enum Modalities : int
	{
		/// <summary>
		///   The game state takes exclusive ownership of the screen does not require the state
		///   below it in the stack to be updated as long as it's active.
		/// </summary>
		Exclusive,

		/// <summary>
		///   The game state sits on top of the state below it in the stack, but does
		///   not completely obscure it or requires it to continue being updated.
		/// </summary>
		Popup
	}
}
