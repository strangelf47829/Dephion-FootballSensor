using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;


namespace TechSense
{
    public class SerialManager
    {
        public static SerialPort ret;
        public static SerialPort GetConnection(int addr) 
        {
            ret = new SerialPort("COM7", 9600);
            ret.Open();
            ret.WriteLine("connect:" + addr);

            ret.DataReceived += Read;

            ret.ReadTimeout = 500;
            ret.WriteTimeout = 500;

            return ret;
        }


        public static void Read(object sender, SerialDataReceivedEventArgs args) 
        {
            try
            {
                string s = ret.ReadLine();
                MessageBox.Show(s);

            }
            catch(TimeoutException e) { }
        }

    }
}
