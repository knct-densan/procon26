using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;
using System.Net;

///
/// プログラム全体で用いる定数やメソッドを定義(予定)
///

namespace airi
{
    static class Util
    {
        public static Core _window;

        public static void updateStatus(String status)
        {
            _window.Invoke((Action)(() => _window.updateLogStatus(status)));
        }

        // プロセスの非同期処理まわり
        // http://www.levibotelho.com/development/async-processes-with-taskcompletionsource/
        public static Task<String> RunProcessAsync(string processPath, string option)
        {
            try
            {
                var tcs = new TaskCompletionSource<string>();
                var process = new Process
                {
                    EnableRaisingEvents = true,
                    StartInfo = new ProcessStartInfo(processPath, option)
                    {
                        Arguments = option,
                        CreateNoWindow = true,
                        UseShellExecute = false,
                        RedirectStandardInput = true,
                        RedirectStandardOutput = true
                    }
                };

                StringBuilder res = new StringBuilder();
                int stoneCount = -1, stringCount = 0, score = -1;

                process.OutputDataReceived += async (object sender, DataReceivedEventArgs e) =>
                {
                    if (e.Data != null)
                    {
                        res.AppendLine(e.Data);
                        /*
                        if (stoneCount == -1)
                        {
                            stoneCount = int.Parse(e.Data);
                        }
                        else if (score == -1)
                        {
                            score = int.Parse(e.Data);
                        }
                        else if (stoneCount != stringCount)
                        {
                            stringCount++;
                            res.AppendLine(e.Data);
                        }
                        else
                        {
                            
                            int maxScore = getScoreFromHttpServer(localServerAddress);
                            if (maxScore > score)
                            {
                                updateStatus(maxScore + " > " + score);
                                updateStatus("[Util] POSTします");
                                await Poster.Post(localServerAddress, res.ToString());
                                HttpServer._maxScore = score;
                            }
                            
                            res.Clear();
                            stringCount = 0;
                            score = -1;
                             */ 
                        //}
                    }
                };

                process.Exited += (object sender, EventArgs e) =>
                {
                    tcs.SetResult(res.ToString());
                    process.Dispose();
                };

                process.Start();
                StreamWriter sw = process.StandardInput;
                sw.WriteLine(option);
                process.BeginOutputReadLine();

                return tcs.Task;
            }
            catch
            {
                return null;
            }
        }

        /*
        private static int getScoreFromHttpServer(string localServerAddress)
        {
            WebClient wc = new WebClient();
            string maxScore = null;

            updateStatus("LocalServerにスコアを尋ねています");

            maxScore = wc.DownloadString(localServerAddress);

            updateStatus("LocalServer Score: " + maxScore);

            return int.Parse(maxScore);
        }
        */
    }
}
