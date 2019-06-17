using System;
using System.Diagnostics;
using Newtonsoft.Json;

namespace CmdCaller
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(CallCmd("ping.exe", "127.0.0.1"));
        }

        static string CallCmd(string cmdPath, string argString)
        {
            var proc = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = cmdPath,
                    Arguments = argString,
                    UseShellExecute = false,
                    RedirectStandardInput = false,
                    RedirectStandardOutput = true,
                    RedirectStandardError = true,
                    CreateNoWindow = true,
                }
            };

            string clientStdout = "";
            string clientStderr = "";
            int? exitCode = null;
            string exceptionMessage = "";
            try
            {
                using (proc)
                {
                    proc.Start();
                    clientStdout = proc.StandardOutput.ReadToEnd();
                    clientStderr = proc.StandardError.ReadToEnd();
                    proc.WaitForExit();
                    exitCode = proc.ExitCode;
                }
            }
            catch (Exception e)
            {
                exceptionMessage = e.Message;
            }

            return JsonConvert.SerializeObject(new
            {
                exitCode,
                clientStdout,
                clientStderr,
                exceptionMessage
            });
        }
    }
}
