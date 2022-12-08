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
            sendRam('2');
        }

        private void button5_Click(object sender, EventArgs e)
        {
            sendRam('1');
            textBox2.Text = data_rx;
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
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

        private void sendRam(char RW)
        {
            char[] data = new char[6];
            data[0] = '@';
            data[1] = RW;
            if (Location.Text.ToString().Length > 1)
                data[2] = (char)Convert.ToInt32(Location.Text.ToString().Substring(0, 2), 16);
            else
                data[2] = (char)Convert.ToInt32(Location.Text.ToString(), 16);
            if (Location.Text.ToString().Length > 3)
            {
                string test = Location.Text.ToString().Substring(2, 2);
                data[3] = (char)Convert.ToInt32(Location.Text.ToString().Substring(2, 2), 16);
            }
                
            else
                data[3] = (char)Convert.ToInt32(Location.Text.ToString(), 16);
            if (RW == '2')
            {
                data[4] = (char)Convert.ToInt32(SendData.Text.ToString(), 16);
            }
                
            data[5] = ';';
            sendSerialData(data);
        }
        private void sendRom(char RW)
        {
            char[] data = new char[6];
            data[0] = '<';
            data[1] = RW; 
            if(Location.Text.ToString().Length > 1)
                data[2] = (char)Convert.ToInt32(Location.Text.ToString().Substring(0, 2), 16);
            else
                data[2] = (char)Convert.ToInt32(Location.Text.ToString(), 16);
            if(Location.Text.ToString().Length > 3)
                data[3] = (char)Convert.ToInt32(Location.Text.ToString().Substring(2, 2), 16);
            else
                data[3] = (char)Convert.ToInt32(Location.Text.ToString(), 16);
            if (RW == '2')
            {
                data[4] = (char)Convert.ToInt32(textBox4.Text.ToString(), 16);
            }

            data[5] = ';';
            sendSerialData(data);
        }
        private void sendSerialData(char[] data)
        {
            port.Write(data,0,data.Length);
        }

        private void data_rx_handler(object sender , SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string tmp = sp.ReadExisting();
            char b = 'Z';
            string t= "";
            try
            {
                b = (char)Convert.ToInt32(tmp, 10);
            }
            catch(Exception e2) {
                if (!char.TryParse(tmp, out b))
                    t = tmp;
            }
            if (b == 'Z')
                data_rx = t;
            else
            {
                int c = (int)b;
                data_rx = c.ToString();
            }

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            sendRom('2');
        }

        private void button6_Click(object sender, EventArgs e)
        {
            sendRom('1');
            textBox3.Text = data_rx;
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
