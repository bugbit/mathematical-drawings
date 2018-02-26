using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL4;
using OpenTK.Input;
using QuickFont;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
Dibuixos - mathematical-drawings for C# .NET/Mono OpenTK\nCopyright 1995-2015-2016 Oscar Hernández Bañó
*/

namespace Dibuixos
{
    public class TextInSpiralCenterFontQuickFont : GameWindow
    {
        private enum Modos { O_OCULTO, O_MOV, O_NOMOV, O_FIN }

        private class Caracter
        {
            public double rad0, rad, arad, x, y, div, scale, anc, anc0, aanc;
            public double ang0, ang, aang;
            public int steps;
            public char car;
            public Modos modo;
        }

        private Matrix4 mProjectionMatrix;
        private QFont mFont;
        private QFontDrawing mDrawingFont;
        private readonly List<Caracter> mCars = new List<Caracter>();
        private double cx, cy;
        private IEnumerable<Caracter> mCarsIni;
        private IEnumerable<Caracter> mCarsAct;
        private double mCountTime;
        private double mSpeed = .01;
        private double mCountTimeHide;
        private double mSpeedHide = .5;

        public TextInSpiralCenterFontQuickFont() : base(800, 600, GraphicsMode.Default, "QuickFont Example", GameWindowFlags.Default, DisplayDevice.Default, 3, 2, GraphicsContextFlags.Default)
        { }

        /// <summary>
        /// Called when your window is resized. Set your viewport here. It is also
        /// a good place to set up your projection matrix (which probably changes
        /// along when the aspect ratio of your window).
        /// </summary>
        /// <param name="e">Not used.</param>
        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);

            GL.Viewport(ClientRectangle.X, ClientRectangle.Y, ClientRectangle.Width, ClientRectangle.Height);

            mProjectionMatrix = Matrix4.CreateOrthographicOffCenter(ClientRectangle.X, ClientRectangle.Width, ClientRectangle.Y, ClientRectangle.Height, -1.0f, 1.0f);
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            mFont = new QFont("Fonts/HappySans.ttf", 30, new QuickFont.Configuration.QFontBuilderConfiguration(true));
            mDrawingFont = new QFontDrawing();
            GL.ClearColor(Color4.CornflowerBlue);
            CreateCarsTexto(new[] { "DIBUIXOS", "MATEMATICS", });
            mCarsAct = mCarsIni = mCars.AsEnumerable();
        }

        private void calc_car_xy(Caracter cars)
        {
            cars.x = cx - cars.rad * Math.Cos(cars.ang);
            cars.y = cy + cars.rad * Math.Sin(cars.ang) - cars.anc;
            cars.scale = cars.anc / cars.div;
        }

        private void CreateCarsTexto(string[] argTexto)
        {
            double rad, arad, divx, divy, div, anc, alfa, beta;
            int ncars;

            rad = Math.Min(Width, Height) / 2.0d;
            cx = Width / 2.0d;
            cy = Height / 2.0d;
            arad = rad / (2 * (double)argTexto.Length);
            arad += arad / 2.0d;
            anc = 120.0d * rad / 348.0d;

            foreach (var str2 in argTexto)
            {
                var pMesure = mFont.Measure(str2);

                anc = Math.PI * arad / str2.Length;
                ncars = str2.Length;
                divx = pMesure.Width / str2.Length;
                divy = pMesure.Height;
                div = Math.Min(divx, divy);
                alfa = Math.Atan
                    (
                        (double)(pMesure.Width / 2.0d)
                        / (double)(pMesure.Height)
                    );
                beta = (Math.PI / 2) - alfa;
                alfa /= (double)(ncars / 2);
                if ((ncars & 1) == 0)
                    beta += alfa / 2;
                foreach (var car in str2)
                {
                    var cars = new Caracter
                    {
                        car = car,
                        div = div,
                        ang0 = beta,
                        ang = Math.PI * 2.0d,
                        aang = alfa,
                        rad0 = rad,
                        rad = 0,
                        modo = Modos.O_OCULTO,
                        anc0 = anc,
                        anc = 1,
                    };

                    mCars.Add(cars);
                    cars.steps = (int)((cars.ang - cars.ang0) / cars.aang);
                    cars.arad = rad / (double)cars.steps;
                    cars.aanc = anc / ((double)cars.steps + 1.0d);
                    calc_car_xy(cars);
                    beta += alfa;
                }
                rad -= arad;
                anc /= 2.0d;
            }
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            base.OnRenderFrame(e);

            var cars = (from c in mCarsIni where c.modo != Modos.O_OCULTO select c);

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            mDrawingFont.DrawingPrimitives.Clear();

            //mDrawingFont.Print(mFont, "Hello Word", new Vector3((float)Width / 2, Height, 0), QFontAlignment.Centre);

            //var dp = new QFontDrawingPrimitive(mFont);

            //dp.ModelViewMatrix = Matrix4.CreateScale(0.5f) * Matrix4.CreateTranslation((float)Width / 2, Height - 100, 0);
            //dp.Print("Hello Word", Vector3.Zero, QFontAlignment.Centre);
            //mDrawingFont.DrawingPrimitives.Add(dp);

            foreach (var c in cars)
            {
                var pDrawP = new QFontDrawingPrimitive(mFont);

                pDrawP.ModelViewMatrix = Matrix4.CreateScale((float)c.scale) * Matrix4.CreateTranslation((float)c.x, (float)c.y, 0.0f);
                pDrawP.Print(c.car.ToString(), Vector3.Zero, QFontAlignment.Centre);
                mDrawingFont.DrawingPrimitives.Add(pDrawP);
            }
            // after all changes do update buffer data and extend it's size if needed.
            mDrawingFont.RefreshBuffers();

            mDrawingFont.ProjectionMatrix = mProjectionMatrix;
            mDrawingFont.Draw();
            SwapBuffers();
        }
        protected override void OnUpdateFrame(FrameEventArgs e)
        {
            if (Keyboard[Key.Escape])
                Exit();

            mCountTimeHide += e.Time;

            while (mCountTimeHide > mSpeedHide)
            {
                if (mCarsIni.First().modo == Modos.O_FIN)
                {
                    var pQuery = (from c in mCarsIni where c.modo == Modos.O_FIN select c).ToArray();

                    for (int i = pQuery.Length - 1; i > 0; i--)
                    {
                        var c = pQuery[i];
                        var c2 = pQuery[i - 1];

                        c.x = c2.x;
                        c.y = c2.y;
                        c.scale = c2.scale;
                    }
                    mCarsIni = mCarsIni.Skip(1);
                }
                mCountTimeHide -= mSpeedHide;
            }

            mCountTime += e.Time;

            while (mCountTime > mSpeed)
            {
                Caracter cars;

                mCountTime -= mSpeed;
                for (; ; )
                {
                    cars = mCarsAct.FirstOrDefault();

                    if (cars == null)
                    {
                        mCarsAct = mCarsIni.Where(c => c.modo != Modos.O_NOMOV && c.modo != Modos.O_FIN);
                        if (!mCarsAct.Any())
                        {
                            foreach (var c in mCarsIni)
                                c.modo = Modos.O_FIN;
                            CreateCarsTexto(new[] { "No hay caminos para la paz.", "La paz es el camino", "(Gandhi)" });
                        }
                    }
                    else
                        break;
                }
                if (cars != null)
                {
                    if (cars.modo == Modos.O_MOV)
                    {
                        cars.rad = Math.Min(cars.rad + cars.arad, cars.rad0);
                        cars.ang -= cars.aang;
                        while (cars.ang < 0) cars.ang += 2 * Math.PI;
                        if (cars.steps-- <= 0)
                        {
                            cars.rad = cars.rad0;
                            cars.anc = cars.anc0;
                            cars.ang = cars.ang0;
                            cars.modo = Modos.O_NOMOV;
                        }
                        mCarsAct = mCarsAct.Skip(1);
                    }
                    else
                    {
                        cars.modo = Modos.O_MOV;
                        mCarsAct = mCarsIni.Where(c => c.modo != Modos.O_FIN);
                    }
                    cars.anc = Math.Min(cars.anc + cars.aanc, cars.anc0);
                    calc_car_xy(cars);
                }
            }
        }


        [STAThread]
        static void Main()
        {
            using (var pDibuix = new TextInSpiralCenterFontQuickFont())
            {
                pDibuix.Run();
            }
        }
    }
}
