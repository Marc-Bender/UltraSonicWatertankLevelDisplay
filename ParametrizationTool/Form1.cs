using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Net;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace ParametrizationTool
{
    public partial class GUI : Form
    {
        private int messageCounter = 0;
        public GUI()
        {
            InitializeComponent();
            sensorTypeValue.SelectedIndex = 0;
        }

        private char[] makeCommandString(bool isWrite, UInt16 address, decimal value)
        {
            char valMSB = (char)((((short)value) & 0xFF00) >> 8);
            char valLSB = (char)((((short)value) & 0x00ff) >> 0);
            char addrMSB = (char)((address & 0xFF00) >> 8);
            char addrLSB = (char)((address & 0x00ff) >> 0);
            return  new char[] { ':', isWrite?'w':'r', addrMSB, addrLSB, isWrite?valMSB:(char)0x00, isWrite?valLSB:(char)0x00};
        }
        
        private void makeAndSendCommand(bool isWrite, UInt16 address, decimal value)
        {
            if(serialPort1.IsOpen == false)
            {
                serialPort1.PortName = "COM" + comPortToBeUsedValue.Value.ToString();
                serialPort1.Open();
            }

            char[] command = makeCommandString(isWrite, address, value);
            serialPort1.Write(command,0,6);
        }

        private char[] getResponse()
        {
            if(serialPort1.IsOpen == false)
            {
                serialPort1.PortName = "COM" + comPortToBeUsedValue.Value.ToString();
                serialPort1.NewLine = ((char)0xff).ToString();
                serialPort1.Open();
            }
            UInt32 timeout = 0;
            while(
                
                        (serialPort1.BytesToRead < 6)
#if SERIAL_IF_TIMEOUT
                     || (timeout < 65000)
#endif
                 )
            {
                ; // wait for MCU to fully send response
                timeout++;
            }
            //                   0    1    2    3    4    5
            char[] response = { ' ', ' ', ' ', ' ', ' ', ' ' };
            if(timeout >= 65000)
            {
                // loop ended with timeout not because data is available 
                // do not attempt to read data from the serial interface
#if SERIAL_IF_TIMEOUT
                return response;
#endif
            }
          
            for(uint i = 0;i<6;i++)
            {
                response[i] = (char)(serialPort1.ReadChar());
            }
            serialPort1.DiscardInBuffer();
            return response;
        }
        private void sendTankfullCmValueBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(true, 0x0000, tankfullCmValue.Value);
            char[] response = getResponse();
            if ((response[1] == 'W') && (response[2] == 0x00) && (response[3] == 0x00))
            {
                // positive response, and response fits the request
                log.Text = messageCounter + ")  W: 00 00";
                messageCounter++;
            }
        }

        private void tankfullCmReadoutBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(false, 0x0000, 0);
            char[] response = getResponse();
            if((response[1] == 'R') && (response[2] == 0x00) && (response[3] == 0x00))
            {
                // positive response, and response fits the request
                tankfullCmValue.Value = response[4] << 8 | response[5];
                log.Text = messageCounter + ")  R: 00 00";
                messageCounter++;
            }
        }

        private void tankEmptyCmSendBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(true, 0x0002, tankEmptyCmValue.Value);
            char[] response = getResponse();
            if ((response[1] == 'W') && (response[2] == 0x00) && (response[3] == 0x02))
            {
                // positive response, and response fits the request
                log.Text = messageCounter + ")  W: 00 02";
                messageCounter++;
            }
        }

        private void tankEmptyCmReadoutBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(false, 0x0002, 0);
            char[] response = getResponse();
            if ((response[1] == 'R') && (response[2] == 0x00) && (response[3] == 0x02))
            {
                // positive response, and response fits the request
                tankEmptyCmValue.Value = response[4] << 8 | response[5];
                log.Text = messageCounter + ")  R: 00 02";
                messageCounter++;
            }
        }

        private void numTanksParalellSendBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(true, 0x0004, numTanksParalellValue.Value);
            char[] response = getResponse();
            if ((response[1] == 'W') && (response[2] == 0x00) && (response[3] == 0x04))
            {
                // positive response, and response fits the request
                log.Text = messageCounter + ")  W: 00 04";
                messageCounter++;
            }
        }
        private void numOfTanksParallelReadoutBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(false, 0x0004, 0);
            char[] response = getResponse();
            if ((response[1] == 'R') && (response[2] == 0x00) && (response[3] == 0x04))
            {
                // positive response, and response fits the request
                numTanksParalellValue.Value = response[4] << 8 | response[5];
                log.Text = messageCounter + ")  R: 00 04";
                messageCounter++;
            }
        }

        private void numOfAreaEntriesSendBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(true, 0x0005, numOfAreaEntriesValue.Value);
            char[] response = getResponse();
            if ((response[1] == 'W') && (response[2] == 0x00) && (response[3] == 0x05))
            {
                // positive response, and response fits the request
                log.Text = messageCounter + ")  W: 00 05";
                messageCounter++;
            }
        }

        private void numOfAreaEntriesReadoutBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(false, 0x0005, 0);
            char[] response = getResponse();
            if ((response[1] == 'R') && (response[2] == 0x00) && (response[3] == 0x05))
            {
                // positive response, and response fits the request
                numOfAreaEntriesValue.Value = response[4] << 8 | response[5];
                log.Text = messageCounter + ")  R: 00 05";
                messageCounter++;
            }
        }
        private void areaEntrySpacingCmSendBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(true,0x0006, areaEntrySpacingCmValue.Value);
            char[] response = getResponse();
            if ((response[1] == 'W') && (response[2] == 0x00) && (response[3] == 0x06))
            {
                // positive response, and response fits the request
                log.Text = messageCounter + ")  W: 00 06";
                messageCounter++;
            }
        }
        private void areaEntrySpacingCmReadoutBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(false, 0x0006, 0);
            char[] response = getResponse();
            if ((response[1] == 'R') && (response[2] == 0x00) && (response[3] == 0x06))
            {
                // positive response, and response fits the request
                areaEntrySpacingCmValue.Value = response[4] << 8 | response[5];
                log.Text = messageCounter + ")  R: 00 06";
                messageCounter++;
            }
        }

        private void averagingSampleCountSendBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(true, 0x0007, averagingSampleCountValue.Value);
            char[] response = getResponse();
            if ((response[1] == 'W') && (response[2] == 0x00) && (response[3] == 0x07))
            {
                // positive response, and response fits the request
                log.Text = messageCounter + ")  W: 00 07";
                messageCounter++;
            }
        }
        private void averagingSampleCountReadoutBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(false, 0x0007, 0);
            char[] response = getResponse();
            if ((response[1] == 'R') && (response[2] == 0x00) && (response[3] == 0x07))
            {
                // positive response, and response fits the request
                averagingSampleCountValue.Value = response[4] << 8 | response[5];
                log.Text = messageCounter + ")  R: 00 07";
                messageCounter++;
            }

        }
        private void sensorTypeSendBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(true, 0x0008, sensorTypeValue.SelectedIndex);
            char[] response = getResponse();
            if ((response[1] == 'W') && (response[2] == 0x00) && (response[3] == 0x08))
            {
                // positive response, and response fits the request
                log.Text = messageCounter + ")  W: 00 08";
                messageCounter++;
            }
        }

        private void sensorTypeReadoutBtn_Click(object sender, EventArgs e)
        {
            makeAndSendCommand(false, 0x0008, 0);
            char[] response = getResponse();
            if ((response[1] == 'R') && (response[2] == 0x00) && (response[3] == 0x08))
            {
                // positive response, and response fits the request
                sensorTypeValue.SelectedIndex = response[4] << 8 | response[5];
                log.Text = messageCounter + ")  R: 00 08";
                messageCounter++;
            }
        }

        private void areaEntrySendBtn_Click(object sender, EventArgs e)
        {
            UInt16 address = 0x000A;
            address += (UInt16)(areaEntrySelectValue.Value * 2);
            makeAndSendCommand(true, address, areaEntryValue.Value);
            char[] response = getResponse();
            if ((response[1] == 'W') && (response[2] == (address & 0xff00) >> 8) && (response[3] == (address & 0x00ff)))
            {
                // positive response, and response fits the request
                log.Text = messageCounter + ")  W: " + response[2] + " " + response[3];
                messageCounter++;
            }
        }

        private void areaEntryValueReadoutBtn_Click(object sender, EventArgs e)
        {
            UInt16 address = 0x000A;
            address += (UInt16)(areaEntrySelectValue.Value * 2);

            makeAndSendCommand(false, address, 0);
            char[] response = getResponse();
            if ((response[1] == 'R') && (response[2] == (address & 0xFF00)>>8) && (response[3] == (address&0x00FF)))
            {
                // positive response, and response fits the request
                areaEntryValue.Value = response[4] << 8 | response[5];
                log.Text = messageCounter + ")  R: " + ((address&0xFF00) >> 8) + " " + (address&0x00ff);
                messageCounter++;
            }
        }

        private void sessionEndBtn_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen == false)
            {
                serialPort1.PortName = "COM" + comPortToBeUsedValue.Value.ToString();
                serialPort1.Open();
            }

            char[] command = { ':', 'q', (char)0x00, (char)0x00, (char)0x00, (char)0x00 };
            serialPort1.Write(command,0,6);
        }
    }
}
