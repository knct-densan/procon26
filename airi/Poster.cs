using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using System.Net.Http.Headers;

namespace airi
{
    /// <summary>
    /// サーバへ投稿を行うためのメソッド群
    /// </summary>
    static class Poster
    {
        private static String _submitUrl, _token;

        public static void Init(String submitUrl, String token)
        {
            _submitUrl = submitUrl;
            _token = token;
        }

        public static async Task<String> Post(String address, String answer)
        {
            Util.updateStatus("POST開始");
            try
            {
                using (HttpClient client = new HttpClient())
                {
                    using (var content = new MultipartFormDataContent())
                    {
                        content.Add(new StringContent(_token), @"""token""");

                        FileStream fs = File.OpenRead(answer);
                        var answercontent = new StreamContent(fs);

                        //var answercontent = new StringContent(answer);

                        // 謎記法. nameとfilenameを付ける.
                        answercontent.Headers.ContentDisposition = new ContentDispositionHeaderValue("form-data")
                        {
                            Name = "answer",
                            FileName = "answer.txt"
                        };

                        content.Add(answercontent);

                        var res = await client.PostAsync(address, content);

                        Util.updateStatus(await res.Content.ReadAsStringAsync());
                        return res.ToString();
                    }
                }
            }
            catch (Exception e)
            {
                Util.updateStatus(e.ToString());
                Util.updateStatus("Posterが死にました");
                return null;
            }

        }
        
    }
}
