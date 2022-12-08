using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Lab2
{
    public partial class Form1 : Form
    {
        SerialPort port = null;
        string data_rx = "";

        public Form1()
        {
            InitializeComponent();
            refresh_com();
            label1.Text = "Disconnected";
            label1.ForeColor = Color.Red;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            refresh_com();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            port = new SerialPort(comboBox1.SelectedItem.ToString());
            initConfig();
            connect();
        }
        private void initConfig()
        {
            port.StopBits = StopBits.One;
            port.BaudRate = 9600;
            port.DataBits = 8;
        }
        private void button3_Click(object sender, EventArgs e)
        {
            disconnect();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            send();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            textBox2.Text = data_rx;
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            {
                send();
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            disconnect();
        }

        private void connect()
        {
            try
            {
                if (!port.IsOpen)
                {
                    port.Open();
                    port.DataReceived += new SerialDataReceivedEventHandler(data_rx_handler);
                    label1.Text = "Connected";
                    label1.ForeColor = Color.Green;
                }
            }
            catch (Exception e)
            {

            }
        }

        private void disconnect()
        {
            if (port == null)
            {
                return;
            }
            try
            {
                if (port.IsOpen)
                {
                    port.Close();
                    label1.Text = "Disconnected";
                    label1.ForeColor = Color.Red;
                }
            }
            catch (Exception e)
            {

            }
        }

        private void refresh_com()
        {
            comboBox1.DataSource = SerialPort.GetPortNames();
        }

        private void send()
        {
            String data = textBox1.Text.ToString();
            sendSerialData(data);
        }
        private void sendSerialData(String data)
        {
            port.Write(data);
        }

        private void data_rx_handler(object sender , SerialDataReceivedEventArgs e)
        { 
  
            SerialPort sp = (SerialPort)sender;
            string tmp = sp.ReadExisting();
            if (tmp.Contains("$") && tmp.Contains("#"))  
            {
          
                tmp = tmp.Remove(0, 2);
                tmp = tmp.Remove(tmp.Length - 3, 3);
                temp.Invoke((Action)(() =>
                {
                    if (tmp != "")
                        temp.Text = "Current Temprature is : " + tmp + "C";
                }));
                data_rx = tmp;
            } 
                    

            
        }

        private void button6_Click(object sender, EventArgs e)
        {
            port.Write('1'.ToString());
        }

        private void label3_Click(object sender, EventArgs e)
        {
            
        }

        private void button7_Click(object sender, EventArgs e)
        {
            port.Write('2'.ToString());
        }

        private void button9_Click(object sender, EventArgs e)
        {
            port.Write('+'.ToString());
        }

        private void button8_Click(object sender, EventArgs e)
        {
            port.Write('-'.ToString());
        }
    }
}
