using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Windows.Forms;

namespace Windows_System_Application.source
{
    public struct ConfigCaptureFile
    {
        public static string imagePath = "Image_";
        public static string imageExtendtion = ".png";

    }
    internal class Capture
    {

        #region Capture
        public static int captureTime = 1000;
        static int imageCount = 0;

        /// <summary>
        /// Capture al screen then save into ImagePath
        /// </summary>
        static public void CaptureScreen()
        {
            //Create a new bitmap.
            var bmpScreenshot = new Bitmap(Screen.PrimaryScreen.Bounds.Width,
                                           Screen.PrimaryScreen.Bounds.Height,
                                           PixelFormat.Format32bppArgb);

            // Create a graphics object from the bitmap.
            var gfxScreenshot = Graphics.FromImage(bmpScreenshot);

            // Take the screenshot from the upper left corner to the right bottom corner.
            gfxScreenshot.CopyFromScreen(Screen.PrimaryScreen.Bounds.X,
                                        Screen.PrimaryScreen.Bounds.Y,
                                        0,
                                        0,
                                        Screen.PrimaryScreen.Bounds.Size,
                                        CopyPixelOperation.SourceCopy);


            string directoryy = $"{ConfigLogFile.rootLogSave}\\{DateTime.Now.ToLongDateString()}\\Image\\";

            if (!Directory.Exists(directoryy))
            {
                Directory.CreateDirectory(directoryy);
            }
            // Save the screenshot to the specified path that the user has chosen.
            string imageName = string.Format("{0}\\{1}{2}", directoryy, DateTime.Now.ToLongDateString() + imageCount, ConfigCaptureFile.imageExtendtion);

            try
            {
                bmpScreenshot.Save(imageName, ImageFormat.Png);
            }
            catch
            {

            }
            imageCount++;
        }

        #endregion

    }
}
