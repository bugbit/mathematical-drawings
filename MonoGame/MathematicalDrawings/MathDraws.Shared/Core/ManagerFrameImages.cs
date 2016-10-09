using System;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace MathDraws.Shared.Core
{
	public class ManagerFrameImages
	{
		public List<Texture2D> Textures { get; private set; }

		public int FPS
		{
			get
			{
				return 1000 / mFPSElapsed;
			}
			set
			{
				mFPSElapsed = 1000 / value;
			}
		}

		public Texture2D TextureCurrent
		{
			get
			{
				return Textures[mNumTextureAct];
			}
		}

		private int mFPSElapsed;
		private int mFrameElapsed = 0;
		private int mNumTextureAct = 0;

		public ManagerFrameImages()
		{
			FPS = 24;
		}

		public void LoadImages(ContentManager argContent, string argFileFormat, int argIni, int argFin)
		{
			if (Textures == null)
				Textures = new List<Texture2D>();

			for (int i = argIni; i <= argFin; i++)
			{
				var pFile = string.Format(argFileFormat, i);

				Textures.Add(argContent.Load<Texture2D>(pFile));
			}
		}

		public void Update(GameTime gameTime)
		{
			var pElapsed = mFrameElapsed + gameTime.ElapsedGameTime.Milliseconds;
			var pSumFrame = Math.DivRem(pElapsed, mFPSElapsed, out mFrameElapsed);

			mNumTextureAct = ((mNumTextureAct + pSumFrame) % Textures.Count);
		}
	}
}
