using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using OpenTK.Platform;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Dibuixos.Pruebas.Desktop
{
    public partial class frmWndSaversTest : Form
    {
        private IWindowInfo mWndInfo;
        private IGraphicsContext mContext;

        public frmWndSaversTest()
        {
            InitializeComponent();
            mWndInfo = Utilities.CreateWindowsWindowInfo(panel1.Handle);
            mContext = new GraphicsContext(GraphicsMode.Default, mWndInfo);
            mContext.LoadAll();
        }

        private void frmWndSaversTest_Load(object sender, EventArgs e)
        {

        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            mContext.MakeCurrent(mWndInfo);
            GL.ClearColor(Color4.Yellow);
            GL.Clear(ClearBufferMask.ColorBufferBit);
            mContext.SwapBuffers();
        }
    }
}
