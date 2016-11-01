using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using MathDraws.Shared.Entity;

namespace MathDraws.Shared.Core
{
	public interface IDibuixosService
	{
		bool IsLoop { get; set; }
		IStateManager StateManager { get; }
		string PiStr{ get; }
		MathDraws.Shared.Components.CharsComponent Chars{ get; }
		SpriteFont FontChars{ get; }
		clsCharsPi CharsPi { get;set;}
		TimeStuffUpdate TheTimeStuffUpdate{ get;}
	}
}
