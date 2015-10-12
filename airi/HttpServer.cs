using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Http;
using System.Threading;

namespace airi
{
    static class HttpServer
    {
        private static string _submitUrl;
        public static int _maxScore;
        private static HttpListener listener = new HttpListener();

        public static async void Run(string address, string submitUrl, int maxScore)
        {
            _submitUrl = submitUrl;
            _maxScore = maxScore;
            //HttpListener listener = new HttpListener();
            //listener.Prefixes.Add("http://localhost:8000/");
            listener.Prefixes.Add(address);
            listener.Start();

            try
            {
                while (true)
                {
                    var content = await listener.GetContextAsync();
                    Util.updateStatus("connected");

                    var req = content.Request;

                    var res = content.Response;

                    res.StatusCode = 200;

                    var stream = res.OutputStream;
                    var writer = new StreamWriter(stream);
                    writer.WriteLine(_maxScore);
                    writer.Close();

                    res.Close();
                    Util.updateStatus("closed");
                }
            }
            catch(Exception e)
            {

            }
        }

        public static void PostScore(int newScore)
        {
            if (_maxScore < newScore)
            {
                Util.updateStatus(_maxScore + "<" + newScore);
                Util.updateStatus("提出しませんでした.");

                return;
            }
            _maxScore = newScore;
        }
    }
}
