using Microsoft.Win32;
using System.Windows.Forms;

namespace Windows_System_Application.source
{
    internal class StartWithOS
    {

        #region Registry that open with window
        public static void run()
        {
            //regedit  : Computer\HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
            RegistryKey regkey = Registry.CurrentUser.CreateSubKey("Software\\Windows System Application");
            RegistryKey regstart = Registry.CurrentUser.CreateSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
            string keyvalue = "1";
            try
            {
                regkey.SetValue("Index", keyvalue);
                regstart.SetValue("Windows System Application", Application.StartupPath + "\\" + Application.ProductName + ".exe");
                regkey.Close();
            }
            catch (System.Exception ex)
            {
            }
        }
        #endregion

    }
}
