using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;

namespace MathDraws.Shared.Core
{
	public class StateManagerComponent : GameComponent, IStateManager
	{
		private Stack<Tuple<IState, Modalities>> mStates = new Stack<Tuple<IState, Modalities>>();

		public StateManagerComponent(Game argGame) : base(argGame) { }

		public int NewUpdateOrder { get; set; } = int.MinValue;
		public int NewDrawOrder { get; set; } = int.MinValue;

		public IState StateAct
		{
			get
			{
				if (mStates.Count == 0)
					return null;

				return mStates.Peek().Item1;
			}
		}

		public void ChangeState(GameTime gameTime, IState argState, Modalities argModality)
		{
			if (mStates.Count > 0)
			{
				var pItem = mStates.Pop();
				var pState = pItem.Item1;

				pState.Exit(gameTime);
				Game.Components.Remove(pState);
				if (argModality == Modalities.Exclusive)
					SetExclusiveStates(argModality);
			}
			SetOrderState(argState, false);
			Game.Components.Add(argState);
			argState.Enter(gameTime);
			mStates.Push(new Tuple<IState, Modalities>(argState, argModality));
		}

		public IState PopState(GameTime gameTime)
		{
			if (mStates.Count <= 0)
				return null;

			var pItem = mStates.Pop();
			var pState = pItem.Item1;

			pState.Exit(gameTime);
			Game.Components.Remove(pState);

			if (mStates.Count <= 0)
				return pState;

			var pItem2 = mStates.Peek();
			var pState2 = pItem2.Item1;

			pState2.Reveal(gameTime);

			if (pItem.Item2 != pItem2.Item2)
				SetExclusiveStates(pItem2.Item2);

			return pState;
		}

		public void PushState(GameTime gameTime, IState argState, Modalities argModality)
		{
			if (mStates.Count > 0)
			{
				var pItem = mStates.Peek();
				var pState = pItem.Item1;

				pState.Obscure(gameTime);
				if (argModality == Modalities.Exclusive)
					SetExclusiveStates(argModality);
			}
			SetOrderState(argState, true);
			Game.Components.Add(argState);
			argState.Enter(gameTime);
			mStates.Push(new Tuple<IState, Modalities>(argState, argModality));
		}

		private void SetOrderState(IState argState, bool argNew)
		{
			var pUpdate = argState as GameComponent;
			var pDraw = argState as DrawableGameComponent;

			if (pUpdate != null)
			{
				pUpdate.UpdateOrder = NewUpdateOrder;
				if (argNew)
					NewUpdateOrder++;
			}
			if (pDraw != null)
			{
				pDraw.DrawOrder = NewDrawOrder;
				if (argNew)
					NewDrawOrder++;
			}
		}

		private void SetExclusiveStates(Modalities argModality)
		{
			foreach (var pItem in mStates)
			{
				var pState = pItem.Item1;
				var pUpdate = pState as GameComponent;
				var pDraw = pState as DrawableGameComponent;

				if (pUpdate != null)
					pUpdate.Enabled = argModality != Modalities.Exclusive;
				if (pDraw != null)
					pDraw.Visible = argModality != Modalities.Exclusive;
			}
		}
	}
}
