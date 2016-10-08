using System;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using Draws = MathDraws.Shared.Draws;

namespace MathDraws.Shared.Core
{
	/// <summary>
	/// This is the main type for your game.
	/// </summary>
	public class MathDrawsGame : Game, IParams
	{
		private GraphicsDeviceManager mGraphics;
		private string mDibArg;

		public bool IsHelp { get; set; }
		public bool IsLoop { get; set; }
		public bool IsDemo { get; set; }

		public MathDrawsGame()
		{
			mGraphics = new GraphicsDeviceManager(this);
			Content.RootDirectory = "Content";
		}

		/// <summary>
		/// Allows the game to perform any initialization it needs to before starting to run.
		/// This is where it can query for any required services and load any non-graphic
		/// related content.  Calling base.Initialize will enumerate through any components
		/// and initialize them as well.
		/// </summary>
		protected override void Initialize()
		{
			this.Services.AddService<IParams>(this);
			mDibArg = null;
			ReadParams();
			Components.Add(new Draws.PresentationDraw(this));
			// TODO: Add your initialization logic here

			base.Initialize();
		}

		/// <summary>
		///
		///
		/// dibuixos[options] [dibuixo]
		///
		///
		/// options:
		///  --help : show usage
		///  -r <width> x<height>x[bpp] : resolucion.Por defecto es -r800x600
		///  -f : fullscreen
		///  -l : play demo in infinite loop
		///	 -d : dibuixo:
		///    demo : All of dibuixos
		///    <dibuixo> : one of dibuixo (see README for more help)
		/// 
		/// </summary>
		private void ReadParams()
		{
			var pParams = this.LaunchParameters;
			string pArg;

			IsHelp = pParams.ContainsKey("--help");
			mGraphics.IsFullScreen = pParams.ContainsKey("-f");
			IsLoop = pParams.ContainsKey("-l");
			if (pParams.TryGetValue("-d", out pArg))
			{
				IsDemo = pArg == "demo";
				if (!IsDemo)
					mDibArg = pArg;
			}
			else
				IsDemo = false;
			if (pParams.TryGetValue("-r", out pArg))
			{
				var pDims = pArg.Split('x');

				if (pDims.Length == 2)
				{
					mGraphics.PreferredBackBufferWidth = int.Parse(pDims[0]);
					mGraphics.PreferredBackBufferHeight = int.Parse(pDims[1]);
				}
			}
		}

		/// <summary>
		/// LoadContent will be called once per game and is the place to load
		/// all of your content.
		/// </summary>
		protected override void LoadContent()
		{
			//TODO: use this.Content to load your game content here 
		}

		/// <summary>
		/// Allows the game to run logic such as updating the world,
		/// checking for collisions, gathering input, and playing audio.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Update(GameTime gameTime)
		{
			// For Mobile devices, this logic will close the Game when the Back button is pressed
			// Exit() is obsolete on iOS
#if !__IOS__ && !__TVOS__
			if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
				Exit();
#endif

			// TODO: Add your update logic here

			base.Update(gameTime);
		}

		/// <summary>
		/// This is called when the game should draw itself.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Draw(GameTime gameTime)
		{
			mGraphics.GraphicsDevice.Clear(Color.CornflowerBlue);

			//TODO: Add your drawing code here

			base.Draw(gameTime);
		}
	}
}
