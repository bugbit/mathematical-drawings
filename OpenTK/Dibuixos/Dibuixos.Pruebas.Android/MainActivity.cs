using System;
using System.IO;
using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using Android.Content.PM;
using Dibuixos.Pruebas.Shared;

namespace Dibuixos.Pruebas.Android
{
    // the ConfigurationChanges flags set here keep the EGL context
    // from being destroyed whenever the device is rotated or the
    // keyboard is shown (highly recommended for all GL apps)
    [Activity(Label = "Dibuixos.Pruebas.Android",
                    ConfigurationChanges = ConfigChanges.KeyboardHidden,
                    ScreenOrientation = ScreenOrientation.SensorLandscape,
                    MainLauncher = true,
                    Icon = "@mipmap/icon")]
    public class MainActivity : Activity
    {
        GLDrawStrokeString view;
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            //using (StreamReader sr = new StreamReader(Assets.Open("fgFonts.xml")))
            //{
            //    var content = sr.ReadToEnd();
            //}
            // Create our OpenGL view, and display it
            view = new GLDrawStrokeString(this);
            SetContentView(view);
        }

        protected override void OnPause()
        {
            // never forget to do this!
            base.OnPause();
            view.Pause();
        }

        protected override void OnResume()
        {
            // never forget to do this!
            base.OnResume();
            view.Resume();
        }
    }
}