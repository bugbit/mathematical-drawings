using Dibuixos.Core;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using OpenTK.Input;
using OpenTKGLUT;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dibuixos.Draws.Text
{
    class TextInSpiralCenterFontStroken : GameWindow
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

        private int mFont = GLUT.GLUT_STROKE_MONO_ROMAN;
        private List<Caracter> mCars = new List<Caracter>();
        private double cx, cy;
        private IEnumerable<Caracter> mCarsAct;
        private int mIdxCar = 0;
        private double mCountTime;
        private double mSpeed = 1;

        public TextInSpiralCenterFontStroken() : base(800, 600, GraphicsMode.Default, "Texts", GameWindowFlags.FixedWindow) { }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            GLUT.glutInit(new string[0]);
            CreateCarsTexto(new[] { "DIBUIXOS", "MATEMATICS", });
            mCarsAct = mCars;
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
            arad = rad / (double)argTexto.Length;
            arad += arad / 2.0d;
            anc = 120.0d * rad / 348.0d;

            foreach (var str2 in argTexto)
            {
                ncars = str2.Length;
                divx = GLUtil.StrokeMinWidth(mFont, str2);
                divy = GLUtil.StrokeMinHeight(mFont, str2);
                div = Math.Min(divx, divy);
                alfa = Math.Atan
                    (
                        (double)(GLUtil.StrokeStrWidth(mFont, str2) / 2.0d)
                        / (double)(GLUtil.StrokeStrHeight(mFont, str2))
                    );
                beta = Math.PI / 2 - alfa;
                alfa /= (double)(ncars >> 1);
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

        /// <summary>
        /// Respond to resize events here.
        /// </summary>
        /// <param name="e">Contains information on the new GameWindow size.</param>
        /// <remarks>There is no need to call the base implementation.</remarks>
        protected override void OnResize(EventArgs e)
        {
            GL.Viewport(0, 0, Width, Height);

            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(0, Width, 0, Height, -1, 1);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            GL.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            GL.Clear(ClearBufferMask.ColorBufferBit);
            GL.Color3(1, 1, 1);

            var cars = (from c in mCars where c.modo != Modos.O_OCULTO select c);

            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            foreach (var c in cars)
            {
                GL.PushMatrix();
                GL.Translate(c.x, c.y, 0);
                GL.Scale(c.scale, c.scale, 0);
                GLUT.glutStrokeCharacter(mFont, c.car);
                GL.PopMatrix();
            }
            //GL.PopMatrix();
            SwapBuffers();
        }
        protected override void OnUpdateFrame(FrameEventArgs e)
        {
            if (Keyboard[Key.Escape])
                Exit();

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
                        mCarsAct = mCars.Where(c => c.modo != Modos.O_NOMOV);
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
                        mCarsAct = mCars;
                    }
                    cars.anc = Math.Min(cars.anc + cars.aanc, cars.anc0);
                    calc_car_xy(cars);
                }
            }
        }


        [STAThread]
        static void Main()
        {
            using (var pDibuix = new TextInSpiralCenterFontStroken())
            {
                pDibuix.Run();
            }
        }
    }
}
