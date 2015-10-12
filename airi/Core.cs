using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Threading.Tasks;
using System.Net;
using System.Net.Http;  // 参照追加. HttpClient使うならそのまま. 使わないなら参照から外そうかな
using System.Diagnostics;


namespace airi
{
    /// <summary>
    /// 競技用の画面
    /// </summary>
    public partial class Core : Form
    {     
        /// <summary>
        /// 問題情報
        /// </summary>
        private String _problemUrl, _problemNum, _token, _submitUrl;

        /// <summary>
        /// ファイルの保存用ディレクトリ
        /// </summary>
        private String _workingDirectoryPath;

        /// <summary>
        /// 解答ファイルの保存用ディレクトリ
        /// </summary>
        private String _answerDirectoryPath;

        /// <summary>
        /// 解答した問題のスコア
        /// </summary>
        private int _score = int.MaxValue;

        /// <summary>
        /// HttpServerのアドレス
        /// </summary>
        private String _localServerAddress;

        /// <summary>
        /// クライアント情報
        /// </summary>
        private String _solverPath = "", _solverParams = "";
        private int _maxScore = int.MaxValue, _paramNum = 1;

        /// <summary>
        /// 問題DLをしているか
        /// </summary>
        private bool _dlFlag = false;


        /// <summary>
        /// コンストラクタ
        /// </summary>
        public Core()
        {
            InitializeComponent();

            Util._window = this;
            updateServerSettings();  // Settingsの情報をメンバに代入

            this.AcceptButton = this.btnSolve;

            this._localServerAddress = "http://" + this.txtLocalServerAddress.Text + "/";
            //HttpServer.Run(_localServerAddress, _submitUrl, _score);
            this._solverPath = this.txtSolverPath.Text;
            p1.Checked = true;
            this._solverParams = txtParams1.Text;
            this._paramNum = 1;
            radioButton2.Checked = true;
        }


        /// <summary>
        /// サーバ接続情報の更新
        /// </summary>
        private void updateServerSettings()
        {
            this._problemUrl = "http://" + this.txtServerAddress.Text + "/";
            this._problemNum = this.txtProblemNum.Text;
            this._token = this.txtToken.Text;
            this._submitUrl = "http://" + this.txtServerAddress.Text + "/answer";
            this._solverParams = txtParams1.Text;
        }

        /// <summary>
        /// txtDLStatus.Textを更新
        /// </summary>
        /// <param name="status"></param>
        private void updateDLStatus(String status)
        {
            txtDLStatus.Text = status;
            txtDLStatus.Update();
        }

        /// <summary>
        /// listBoxLogにログを書き込む
        /// </summary>
        /// <param name="status"></param>
        public void updateLogStatus(String status)
        {
            listBoxLog.Items.Add(status);
            listBoxLog.TopIndex = listBoxLog.Items.Count - 1;  // listBoxLogの一番下の項目を表示(自動スクロール)
        }

        public void updateMaxScoreStatus(string status)
        {
            txtScore.Text = status;
            txtScore.Update();
        }

        /// <summary>
        /// 問題保存用ディレクトリの作成
        /// </summary>
        /// <returns>ディレクトリパス</returns>
        private String createWorkingDirectory()
        {
            String parent = Path.GetFullPath(@".\quest\");

            if (!Directory.Exists(parent))
            {
                updateLogStatus("問題用ディレクトリの作成中");
                Directory.CreateDirectory(parent);
                updateLogStatus("問題用ディレクトリの作成完了");
            }

            return parent;
        }

        /// <summary>
        /// 解答保存用ディレクトリの作成
        /// </summary>
        /// <returns></returns>
        private String createAnswerDirectory()
        {
            String parent = Path.GetFullPath(@".\answer\");

            if (!Directory.Exists(parent))
            {
                updateLogStatus("解答用ディレクトリの作成中");
                Directory.CreateDirectory(parent);
                updateLogStatus("解答用ディレクトリの作成完了");
            }

            return parent;
        }

        /// <summary>
        /// 問題ファイルのダウンロード
        /// </summary>
        /// <returns>
        /// 問題ファイルへのパスを返す. 失敗した場合はnullを返す.
        /// </returns>
        private String downloadProblem()
        {
            updateDLStatus("問題ファイルのダウンロード中");

            WebClient wc = new WebClient();
            String problemFile = "quest" + _problemNum + ".txt";
            String url = _problemUrl + problemFile + "?token=" + _token;
            String ret = _workingDirectoryPath + @"\" + problemFile;  // ダウンロード先

            bool failure = true;
            while (failure)
            {
                try
                {
                    wc.DownloadFile(url, ret);
                    failure = false;
                }
                catch (WebException wex)
                {
                    if (MessageBox.Show(
                        "[Download ERROR: " + wex.Message + "]\n" + "続行しますか?"
                        , ""
                        , MessageBoxButtons.YesNo)
                        == DialogResult.No)
                    {
                        // 終了する
                        return null;
                    }
                }
            }

            updateDLStatus("問題ファイルのダウンロード完了");
            return ret;   
        }
       
        /// <summary>
        /// ボタン押下で問題のダウンロード開始
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDLquest_Click(object sender, EventArgs e)
        {
            updateServerSettings();

            _workingDirectoryPath = createWorkingDirectory();

            String problemPath = downloadProblem();

            if (problemPath == null)
            {
                updateLogStatus("問題取得に失敗しました");
                return;
            }
            else
            {
                _dlFlag = true;
                updateLogStatus("問題ファイルのダウンロード完了");
            }
        }

        /// <summary>
        /// ソルバのパラメータの選択
        /// </summary>
        /// <returns></returns>
        private int selectParamNum()
        {
            if (p1.Checked)
                return 1;
            else if (p2.Checked)
                return 2;
            else if (p3.Checked)
                return 3;
            else if (p4.Checked)
                return 4;
            else if (p5.Checked)
                return 5;
            else if (p6.Checked)
                return 6;

            return 1;  // 選択しなかったら
        }

        /// <summary>
        /// ソルバのパラメータの設定
        /// </summary>
        private void selectSolverParams()
        {
            int param = selectParamNum();

            switch (param)
            {
                case 1:
                    _solverParams = txtParams1.Text;
                    _paramNum = 1;
                    break;
                case 2:
                    _solverParams = txtParams2.Text;
                    _paramNum = 2;
                    break;
                case 3:
                    _solverParams = txtParams3.Text;
                    _paramNum = 3;
                    break;
                case 4:
                    _solverParams = txtParams4.Text;
                    _paramNum = 4;
                    break;
                case 5:
                    _solverParams = txtParams5.Text;
                    _paramNum = 5;
                    break;
                case 6:
                    _solverParams = txtParams6.Text;
                    _paramNum = 6;
                    break;
                default:
                    _solverParams = txtParams1.Text;
                    _paramNum = 1;
                    break;
            }
        }
          

        /// <summary>
        /// ボタン押下でソルバ実行
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void btnSolve_Click(object sender, EventArgs e)
        {

            // 問題DLがされていないなら
            if (!_dlFlag)
            {
                updateServerSettings();

                _workingDirectoryPath = createWorkingDirectory();

                String problemPath = downloadProblem();

                if (problemPath == null)
                {
                    updateLogStatus("問題取得に失敗しました");
                    return;
                }
                else
                {
                    _dlFlag = true;
                    updateLogStatus("問題ファイルのダウンロード完了");
                }
            }

            selectSolverParams();  // Solverのparam設定

            Poster.Init(_submitUrl, _token);  // Posterの初期化

            _answerDirectoryPath = createAnswerDirectory();

            string args = _workingDirectoryPath + "quest" + _problemNum + ".txt " + _answerDirectoryPath + "ans" + _problemNum + ".txt " + _solverParams;
            string res = await runSolver(_solverPath, args);
            _score = int.Parse(res);  // score(だいたい4桁のやつ)をintに
            
            if (_maxScore > _score)
            {
                _maxScore = _score;
                txtScore.Text = res;
            }

            updateLogStatus("Solve終了. 割ったスコア : " + (int.Parse(res) / 257));

            updateLogStatus("Param: " + _paramNum + " score: " +res.ToString());
        }
   
        /// <summary>
        /// Postの際に警告
        /// </summary>
        /// <returns></returns>
        private bool postConfirm()
        {
            if (_maxScore < _score)
            {
                DialogResult result =  MessageBox.Show(
                        "[Warning!] 現在最高: " + _maxScore + "\nPostしますか?"
                        , ""
                        , MessageBoxButtons.YesNo);

                if (result == DialogResult.Yes)
                    return true;
                else
                    return false;
            }

            return true;
        }
        
        /// <summary>
        /// ボタン押下でPost
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void btnPost_Click(object sender, EventArgs e)
        {
            string anspath = _answerDirectoryPath + "ans" + _problemNum + ".txt";

            if (postConfirm())
                await Poster.Post(_submitUrl, anspath);
        }

        /// <summary>
        /// 問題DL, 解答, 提出をすべて実行
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void btnAllRun_Click(object sender, EventArgs e)
        {
            if (radioButton1.Checked)
            {
                //HttpServer.Run(_localServerAddress, _score);
                // 問題DL
                updateServerSettings();
                this._localServerAddress = "http://" + txtLocalServerAddress.Text + "/";  // ローカルサーバアドレス設定

                _workingDirectoryPath = createWorkingDirectory();

                String problemPath = downloadProblem();

                if (problemPath == null)
                {
                    updateLogStatus("問題取得に失敗しました");
                    return;
                }
                else
                {
                    updateLogStatus("問題ファイルのダウンロード完了");
                }


                // sataticクラスの初期化
                Poster.Init(_localServerAddress, _token);

                // Solver
                _answerDirectoryPath = createAnswerDirectory();

                updateLogStatus("Solve開始");

                string args = _workingDirectoryPath + "quest" + _problemNum + ".txt " + _answerDirectoryPath + "ans" + _problemNum + ".txt " + _solverParams;

                string res = await runSolver(_solverPath, args);

                updateLogStatus("Solve終了. スコア : " + int.Parse(res) % 257);
                _score = int.Parse(res.ToString());

                string anspath = _answerDirectoryPath + "ans" + _problemNum + ".txt";

                // Post
                HttpServer.PostScore(_score);

                await Poster.Post(_localServerAddress, anspath);
            }
            else
            {
                updateServerSettings();

                _workingDirectoryPath = createWorkingDirectory();

                String problemPath = downloadProblem();

                if (problemPath == null)
                {
                    updateLogStatus("問題取得に失敗しました");
                    return;
                }
                else
                {
                    updateLogStatus("問題ファイルのダウンロード完了");
                }

                // staticクラスの初期化
                Poster.Init(_submitUrl, _token);

                _answerDirectoryPath = createAnswerDirectory();

                string args = _workingDirectoryPath + "quest" + _problemNum + ".txt " + _answerDirectoryPath + "ans" + _problemNum + ".txt " + _solverParams;
                string res = await runSolver(_solverPath, args);
                _score = int.Parse(res);  // score(だいたい4桁のやつ)をintに

                if (_maxScore > _score)
                {
                    _maxScore = _score;
                    txtScore.Text = res;
                }

                updateLogStatus("Solve終了. スコア : " + (int.Parse(res) / 257));

                updateLogStatus("[Core : サーバ不使用] " + res.ToString());

                string anspath = _answerDirectoryPath + "ans" + _problemNum + ".txt";

                if (postConfirm())
                    await Poster.Post(_submitUrl, anspath);
            }
        }
        
        /// <summary>
        /// ソルバを非同期で走らせる
        /// </summary>
        /// <param name="solverPath"></param>
        /// <param name="args"></param>
        /// <returns></returns>
        private async Task<string> runSolver(string solverPath, string args)
        {
            var res = await Util.RunProcessAsync(solverPath, args);

            return res.ToString();
        }

        /// <summary>
        /// ソルバを選択
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSolverPath_Click(object sender, EventArgs e)
        {
            if (File.Exists(_solverPath))
            {
                selectSolverDialog.InitialDirectory = Path.GetFullPath(_solverPath);
            }
            selectSolverDialog.Filter = "exe files (*.exe)|*.exe|All files (*.*)|*.*";
            selectSolverDialog.ShowDialog();
        }

        private void selectSolverDialog_FileOk(object sender, EventArgs e)
        {
            txtSolverPath.Text = _solverPath = selectSolverDialog.FileName;
        }

        /// <summary>
        /// Nextボタン押下で次の問題
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnNext_Click(object sender, EventArgs e)
        {
            _dlFlag = false;
            listBoxLog.Items.Clear();
            _problemNum = (int.Parse(txtProblemNum.Text) + 1).ToString();

            txtProblemNum.Text = _problemNum;
        }
        
    }
}
