using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.Runtime.InteropServices;

/*------------兼容ZLG的数据类型---------------------------------*/

//1.ZLGCAN系列接口卡信息的数据类型。
public struct VCI_BOARD_INFO
{
    public UInt16 hw_Version;
    public UInt16 fw_Version;
    public UInt16 dr_Version;
    public UInt16 in_Version;
    public UInt16 irq_Num;
    public byte can_Num;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)] public byte[] str_Serial_Num;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
    public byte[] str_hw_Type;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
    public byte[] Reserved;
}

/////////////////////////////////////////////////////
//2.定义CAN信息帧的数据类型。
unsafe public struct VCI_CAN_OBJ  //使用不安全代码
{
    public uint ID;
    public uint TimeStamp;        //时间标识
    public byte TimeFlag;         //是否使用时间标识
    public byte SendType;         //发送标志。保留，未用
    public byte RemoteFlag;       //是否是远程帧
    public byte ExternFlag;       //是否是扩展帧
    public byte DataLen;          //数据长度
    public fixed byte Data[8];    //数据
    public fixed byte Reserved[3];//保留位

}

//3.定义初始化CAN的数据类型
public struct VCI_INIT_CONFIG
{
    public UInt32 AccCode;
    public UInt32 AccMask;
    public UInt32 Reserved;
    public byte Filter;   //0或1接收所有帧。2标准帧滤波，3是扩展帧滤波。
    public byte Timing0;  //波特率参数，具体配置，请查看二次开发库函数说明书。
    public byte Timing1;
    public byte Mode;     //模式，0表示正常模式，1表示只听模式,2自测模式
}

/*------------其他数据结构描述---------------------------------*/
//4.USB-CAN总线适配器板卡信息的数据类型1，该类型为VCI_FindUsbDevice函数的返回参数。
public struct VCI_BOARD_INFO1
{
    public UInt16 hw_Version;
    public UInt16 fw_Version;
    public UInt16 dr_Version;
    public UInt16 in_Version;
    public UInt16 irq_Num;
    public byte can_Num;
    public byte Reserved;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)] public byte[] str_Serial_Num;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
    public byte[] str_hw_Type;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
    public byte[] str_Usb_Serial;
}

/*------------数据结构描述完成---------------------------------*/

public struct CHGDESIPANDPORT
{
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
    public byte[] szpwd;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
    public byte[] szdesip;
    public Int32 desport;

    public void Init()
    {
        szpwd = new byte[10];
        szdesip = new byte[20];
    }
}

namespace ledControl_client
{
    public partial class FormMain : Form
    {
        byte ledMode = 0;

        UInt32 devType = 4;     // USBCAN2
        UInt32 devId = 0;
        UInt32 canChn = 0;

        UInt32 isDevOpen = 0;

        uint brightnessLevel = 0;

        /*------------兼容ZLG的函数描述---------------------------------*/
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_OpenDevice(UInt32 DeviceType, UInt32 DeviceInd, UInt32 Reserved);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_CloseDevice(UInt32 DeviceType, UInt32 DeviceInd);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_InitCAN(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd, ref VCI_INIT_CONFIG pInitConfig);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_ReadBoardInfo(UInt32 DeviceType, UInt32 DeviceInd, ref VCI_BOARD_INFO pInfo);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_GetReceiveNum(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_ClearBuffer(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_StartCAN(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_ResetCAN(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_Transmit(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd, ref VCI_CAN_OBJ pSend, UInt32 Len);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_Receive(UInt32 DeviceType, UInt32 DeviceInd, UInt32 CANInd, ref VCI_CAN_OBJ pReceive, UInt32 Len, Int32 WaitTime);

        /*------------其他函数描述---------------------------------*/

        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_ConnectDevice(UInt32 DevType, UInt32 DevIndex);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_UsbDeviceReset(UInt32 DevType, UInt32 DevIndex, UInt32 Reserved);
        [DllImport("controlcan.dll")]
        static extern UInt32 VCI_FindUsbDevice(ref VCI_BOARD_INFO1 pInfo);

        public FormMain()
        {
            InitializeComponent();
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            comboBoxLedModeSelection.SelectedIndex = 0;
            richTextBox1.Text = "No CAN connection ...\n";
        }

        private void FormMain_Close()
        {
            if(isDevOpen == 1)
            {
                VCI_CloseDevice(devType, devId);
            }
            else
            {

            }
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            uint sendReturnSts = 0;

            VCI_CAN_OBJ sendMsgObj = new VCI_CAN_OBJ();
            sendMsgObj.ID = 0x505;
            sendMsgObj.RemoteFlag = 0;
            sendMsgObj.ExternFlag = 0;
            sendMsgObj.SendType = 0;
            sendMsgObj.DataLen = 8;

            ledMode = (byte)comboBoxLedModeSelection.SelectedIndex;
            unsafe
            {
                sendMsgObj.Data[0] = (byte)ledMode;
                sendMsgObj.Data[1] = 0;
                sendMsgObj.Data[2] = 0;
                sendMsgObj.Data[3] = 0;
                sendMsgObj.Data[4] = 0;
                sendMsgObj.Data[5] = 0;
                sendMsgObj.Data[6] = 0;
                sendMsgObj.Data[7] = 0;
            }

            sendReturnSts = VCI_Transmit(devType, devId, canChn, ref sendMsgObj, 1);
            if (sendReturnSts != 0)
            {
                richTextBox1.AppendText("Current led mode:" + ledMode.ToString() + "\n");
            }
        }

        private void ConnectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            uint openDevSts = 0;
            if(isDevOpen == 0)
            {
                richTextBox1.AppendText("Start build CAN connection with CAN card ...\n");
                openDevSts = VCI_OpenDevice(devType, devId, 0);
                if (openDevSts != 1)
                {
                    richTextBox1.AppendText("Failed to connect the device\n");
                    richTextBox1.AppendText("Open return code:" + openDevSts.ToString() + '\n');
                    return;
                }
                else
                {
                    
                }
                

                VCI_INIT_CONFIG canConfig = new VCI_INIT_CONFIG();
                canConfig.Mode = 0;
                canConfig.Timing0 = 0x00;
                canConfig.Timing1 = 0x1C;

                openDevSts = VCI_InitCAN(devType, devId, canChn, ref canConfig);
                if(openDevSts != 1)
                {
                    richTextBox1.AppendText("Failed to initialize the CAN channel\n");
                    return;
                }
                else
                {
                    richTextBox1.AppendText("Connect Succeed\n");
                }

                openDevSts = VCI_StartCAN(devType, devId, canChn);
                if (openDevSts != 1)
                {
                    richTextBox1.AppendText("Failed to start the CAN channel\n");
                    return;
                }
                else
                {
                    richTextBox1.AppendText("start Succeed\n");
                    isDevOpen = 1;
                }
            }
            else
            {

            }
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            uint sendReturnSts = 0;
            VCI_CAN_OBJ sendMsgObj = new VCI_CAN_OBJ();

            if((brightnessLevel == 0) || (isDevOpen == 0))
            {
                // highest brightness level so do nothing
            }
            else if((brightnessLevel == 1) || (brightnessLevel == 2))
            {
                brightnessLevel = brightnessLevel - 1;
                sendMsgObj.ID = 0x505;
                sendMsgObj.RemoteFlag = 0;
                sendMsgObj.ExternFlag = 0;
                sendMsgObj.SendType = 0;
                sendMsgObj.DataLen = 8;

                unsafe
                {
                    sendMsgObj.Data[0] = 1;
                    sendMsgObj.Data[1] = 0;
                    sendMsgObj.Data[2] = 0;
                    sendMsgObj.Data[3] = 0;
                    sendMsgObj.Data[4] = 0;
                    sendMsgObj.Data[5] = 0;
                    sendMsgObj.Data[6] = 0;
                    sendMsgObj.Data[7] = 0;
                }
                sendReturnSts = VCI_Transmit(devType, devId, canChn, ref sendMsgObj, 1);
                Thread.Sleep(200);

                sendMsgObj.ID = 0x505;
                sendMsgObj.RemoteFlag = 0;
                sendMsgObj.ExternFlag = 0;
                sendMsgObj.SendType = 0;
                sendMsgObj.DataLen = 8;

                unsafe
                {
                    sendMsgObj.Data[0] = 0;
                    sendMsgObj.Data[1] = 0;
                    sendMsgObj.Data[2] = 0;
                    sendMsgObj.Data[3] = 0;
                    sendMsgObj.Data[4] = 0;
                    sendMsgObj.Data[5] = 0;
                    sendMsgObj.Data[6] = 0;
                    sendMsgObj.Data[7] = 0;
                }
                sendReturnSts = VCI_Transmit(devType, devId, canChn, ref sendMsgObj, 1);
                Thread.Sleep(200);

                sendMsgObj.ID = 0x505;
                sendMsgObj.RemoteFlag = 0;
                sendMsgObj.ExternFlag = 0;
                sendMsgObj.SendType = 0;
                sendMsgObj.DataLen = 8;

                unsafe
                {
                    sendMsgObj.Data[0] = 1;
                    sendMsgObj.Data[1] = 0;
                    sendMsgObj.Data[2] = 0;
                    sendMsgObj.Data[3] = 0;
                    sendMsgObj.Data[4] = 0;
                    sendMsgObj.Data[5] = 0;
                    sendMsgObj.Data[6] = 0;
                    sendMsgObj.Data[7] = 0;
                }
                sendReturnSts = VCI_Transmit(devType, devId, canChn, ref sendMsgObj, 1);
                Thread.Sleep(200);
            }
            //else if((brightnessLevel == 2))
            //{
            //    brightnessLevel = brightnessLevel - 1;
            //    sendMsgObj.ID = 0x505;
            //    sendMsgObj.RemoteFlag = 0;
            //    sendMsgObj.ExternFlag = 0;
            //    sendMsgObj.SendType = 0;
            //    sendMsgObj.DataLen = 8;

            //    unsafe
            //    {
            //        sendMsgObj.Data[0] = 1;
            //        sendMsgObj.Data[1] = 0;
            //        sendMsgObj.Data[2] = 0;
            //        sendMsgObj.Data[3] = 0;
            //        sendMsgObj.Data[4] = 0;
            //        sendMsgObj.Data[5] = 0;
            //        sendMsgObj.Data[6] = 0;
            //        sendMsgObj.Data[7] = 0;
            //    }
            //    sendReturnSts = VCI_Transmit(devType, devId, canChn, ref sendMsgObj, 1);
            //    Thread.Sleep(300);
            //}
            else
            {
                // some thing wrong
            }

            // back to the led mode which selected
            sendReturnSts = 0;
            sendMsgObj.ID = 0x505;
            sendMsgObj.RemoteFlag = 0;
            sendMsgObj.ExternFlag = 0;
            sendMsgObj.SendType = 0;
            sendMsgObj.DataLen = 8;
            ledMode = (byte)comboBoxLedModeSelection.SelectedIndex;
            unsafe
            {
                sendMsgObj.Data[0] = (byte)ledMode;
                sendMsgObj.Data[1] = 0;
                sendMsgObj.Data[2] = 0;
                sendMsgObj.Data[3] = 0;
                sendMsgObj.Data[4] = 0;
                sendMsgObj.Data[5] = 0;
                sendMsgObj.Data[6] = 0;
                sendMsgObj.Data[7] = 0;
            }
            sendReturnSts = VCI_Transmit(devType, devId, canChn, ref sendMsgObj, 1);
        }

        private void Button2_Click_1(object sender, EventArgs e)
        {
            uint sendReturnSts = 0;
            VCI_CAN_OBJ sendMsgObj = new VCI_CAN_OBJ();

            if ((brightnessLevel == 2) || (isDevOpen == 0))
            {
                // lowest brightness level so do nothing
            }
            else if ((brightnessLevel == 0) || (brightnessLevel == 1))
            {
                brightnessLevel = brightnessLevel + 1;
                sendMsgObj.ID = 0x505;
                sendMsgObj.RemoteFlag = 0;
                sendMsgObj.ExternFlag = 0;
                sendMsgObj.SendType = 0;
                sendMsgObj.DataLen = 8;

                unsafe
                {
                    sendMsgObj.Data[0] = 1;
                    sendMsgObj.Data[1] = 0;
                    sendMsgObj.Data[2] = 0;
                    sendMsgObj.Data[3] = 0;
                    sendMsgObj.Data[4] = 0;
                    sendMsgObj.Data[5] = 0;
                    sendMsgObj.Data[6] = 0;
                    sendMsgObj.Data[7] = 0;
                }
                sendReturnSts = VCI_Transmit(devType, devId, canChn, ref sendMsgObj, 1);
                Thread.Sleep(200);
            }
            else
            {
                // something wrong
            }

            // back to the led mode which selected
            sendReturnSts = 0;
            sendMsgObj.ID = 0x505;
            sendMsgObj.RemoteFlag = 0;
            sendMsgObj.ExternFlag = 0;
            sendMsgObj.SendType = 0;
            sendMsgObj.DataLen = 8;
            ledMode = (byte)comboBoxLedModeSelection.SelectedIndex;
            unsafe
            {
                sendMsgObj.Data[0] = (byte)ledMode;
                sendMsgObj.Data[1] = 0;
                sendMsgObj.Data[2] = 0;
                sendMsgObj.Data[3] = 0;
                sendMsgObj.Data[4] = 0;
                sendMsgObj.Data[5] = 0;
                sendMsgObj.Data[6] = 0;
                sendMsgObj.Data[7] = 0;
            }
            sendReturnSts = VCI_Transmit(devType, devId, canChn, ref sendMsgObj, 1);
        }
    }
}
