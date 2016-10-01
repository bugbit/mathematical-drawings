using System;

using Android.App;
using Android.Content;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Android.OS;
using Android.Content.PM;

namespace Dibuixos.Android
{
	// the ConfigurationChanges flags set here keep the EGL context
	// from being destroyed whenever the device is rotated or the
	// keyboard is shown (highly recommended for all GL apps)
	[Activity(Label = "Dibuixos",
				ConfigurationChanges = ConfigChanges.Orientation | ConfigChanges.KeyboardHidden,
				ScreenOrientation = ScreenOrientation.SensorLandscape,
				MainLauncher = true, LaunchMode = LaunchMode.SingleTask,
				Icon = "@mipmap/icon")]
	public class MainActivity : Activity
	{
		DibuixosView view;
		protected override void OnCreate(Bundle bundle)
		{
			base.OnCreate(bundle);

			var manager = GetSystemService(Context.ActivityService) as ActivityManager;
			if (manager.DeviceConfigurationInfo.ReqGlEsVersion >= 0x20000)
			{
				// Create our OpenGL view, and display it
				view = new DibuixosView(this);
				SetContentView(view);
			}
			else
				SetContentView(Resource.Layout.Main);
		}
	}
}

