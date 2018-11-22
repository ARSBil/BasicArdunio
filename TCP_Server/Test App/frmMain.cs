using System;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Windows.Forms;

namespace testerApp
{
    public partial class frmMain : Form
    {
        public delegate void invokeDelegate();
        public frmMain()
        {
            InitializeComponent();
        }


        private void openTcpPort()
        {
            tcpServer1.Close();
            tcpServer1.Port = 3001;
            tcpServer1.Open();

            displayTcpServerStatus();
        }

        private void displayTcpServerStatus()
        {
            if (tcpServer1.IsOpen)
            {
                lblStatus.Text = "Server Açık";
                lblStatus.BackColor = Color.Lime;
                IPHostEntry host;
                string localIP = "?";
                host = Dns.GetHostEntry(Dns.GetHostName());
                foreach (IPAddress ip in host.AddressList)
                {
                    if (ip.AddressFamily.ToString() == "InterNetwork")
                    {
                        localIP = ip.ToString();
                    }
                }
                serverIP.Text = localIP;
            }
            else
            {
                lblStatus.Text = "Server Kapalı";
                lblStatus.BackColor = Color.Red;
            }
            
        }

        private void btnSend_Click(object sender, EventArgs e)
        {

            
            if(txtText.Text.Length > 0)
                send();
            txtText.Text = "";
        }

        private void send()
        {
            string data = "";

            foreach (string line in txtText.Lines)
            {
                data = data + line.Replace("\r", "").Replace("\n", "") + "\r\n";
            }
            data = data.Substring(0, data.Length - 2);

            tcpServer1.Send(data);

            logData(true, data);
        }

       
        private void sendData(char temp)
        {
            string data = "";
            data = temp.ToString() + "\r\n";
            data = data.Substring(0, data.Length - 2);
            tcpServer1.Send(data);
        }

        public void logData(bool sent, string text)
        {
            txtLog.Text += "\r\n" + DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss tt") + (sent ? " YOLLANDI:\r\n" : " ALINDI:\r\n");
            txtLog.Text += text;
            txtLog.Text += "\r\n";
            if (txtLog.Lines.Length > 500)
            {
                string[] temp = new string[500];
                Array.Copy(txtLog.Lines, txtLog.Lines.Length - 500, temp, 0, 500);
                txtLog.Lines = temp;
            }
            txtLog.SelectionStart = txtLog.Text.Length;
            txtLog.ScrollToCaret();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            tcpServer1.Close();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            openTcpPort();
            timer1.Enabled = true;

            
        }

        private void tcpServer1_OnDataAvailable(tcpServer.TcpServerConnection connection)
        {
            byte[] data = readStream(connection.Socket);

            if (data != null)
            {
                string dataStr = Encoding.ASCII.GetString(data);

                invokeDelegate del = () =>
                {
                    logData(false, dataStr);
                };
                Invoke(del);

                data = null;
            }
        }

        protected byte[] readStream(TcpClient client)
        {
            NetworkStream stream = client.GetStream();
            if (stream.DataAvailable)
            {
                byte[] data = new byte[client.Available];

                int bytesRead = 0;
                try
                {
                    bytesRead = stream.Read(data, 0, data.Length);
                }
                catch (IOException)
                {
                }

                if (bytesRead < data.Length)
                {
                    byte[] lastData = data;
                    data = new byte[bytesRead];
                    Array.ConstrainedCopy(lastData, 0, data, 0, bytesRead);
                }
                return data;
            }
            return null;
        }

        private void tcpServer1_OnConnect(tcpServer.TcpServerConnection connection)
        {
            invokeDelegate setText = () => lblConnected.Text = tcpServer1.Connections.Count.ToString();

            Invoke(setText);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            displayTcpServerStatus();
            lblConnected.Text = tcpServer1.Connections.Count.ToString();
        }


        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            timer1.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            sendData('w');
        }

        private void button5_Click(object sender, EventArgs e)
        {
            sendData('x');
        }

        private void button2_Click(object sender, EventArgs e)
        {
            sendData('a');
        }

        private void button3_Click(object sender, EventArgs e)
        {
            sendData('d');
        }

        private void button4_Click(object sender, EventArgs e)
        {
            sendData('s');
        }

    }
}
