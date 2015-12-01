/*
********************************************************************************
*                                Ƕ��ʽ΢ϵͳ
*                                   msOS
*
*                            Ӳ��ƽ̨:msPLC DEMO
*                          ��оƬ:STM32F103R8T6/RBT6
*                           ��������οƼ����޹�˾
*
*                                ����:����ΰ
*                                ����:������
*                                ��ʶ:Wangsw
*
*                                QQ:26033613
*                               QQȺ:291235815
*                        �Ա���:http://52edk.taobao.com
*                      ��̳:http://gongkong.eefocus.com/bbs/
*                ����:http://forum.eet-cn.com/BLOG_wangsw317_1268.HTM
********************************************************************************
*�ļ���     : modbus_host.c
*����       : ��չModbusģ��
*ԭ��       : ͨ����׼ModbusЭ����չ��ģ��
*           : ͨ��Modbus����PLC����������ַ
*           : ͨ���ĸ����飬��������
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2014/11/8       ��ʼ�汾
********************************************************************************
*/

#include "system.h"
#if 0
#define DeviceID                    1
#define TimeoutSum                  2

#define TxdBufferSum                256
#define RxdBufferSum                256
#define DataPointer                 ((DataStruct *)0)
#define DataBase                    (uint)AppDataPointer
extern const byte CrcHighBlock[256];
extern const byte CrcLowBlock[256];

//************************************************************************************
//��HMI�������ݣ�����������Ӧ�ĵ�ַ
const bool * Block0x[] =                // DataOutPort
{
    &DataPointer->DO.Y0, &DataPointer->DO.Y1, &DataPointer->DO.Y2, &DataPointer->DO.Y3, &DataPointer->DO.Y4, &DataPointer->DO.Y5
};

const bool * Block1x[] =                // DataInPort
{
    &DataPointer->DI.X0, &DataPointer->DI.X1, &DataPointer->DI.X2, &DataPointer->DI.X3
};
const ushort * Block3x[] =              // AdcInPort
{
    &DataPointer->Adc.A0, &DataPointer->Adc.A1, &DataPointer->Adc.A2, &DataPointer->Adc.A3
};

const ushort * Block4x[] =              // Register
{
    (ushort *)(&DataPointer->Frequency), (ushort *)(&(DataPointer->Frequency)) + 1,
    (ushort *)(&(DataPointer->Voltage)), (ushort *)(&(DataPointer->Current))
};
//************************************************************************************

static byte TxdBuffer[TxdBufferSum];    // ����֡���ͻ�����
static byte RxdBuffer[RxdBufferSum];    // ����֡���ݻ�����

static bool RxdState;                   // ����״̬
static ushort RxdCounter;               // ���ռ���
static ushort RxdTimeout;               // ���ճ�ʱ��֡





/*************************************************************************************
* MODBUS������Ӧ����
* ���룺���ݿ�ʼ��ַ�����ȣ���1���ǣ�0����֡�Ŀ�ʼ��
* ���û����ã�Ҫȷ��USART�ķ�������ж���ʹ�ܵģ�
*************************************************************************************/
static void Response(byte *bufferPointer, int sum)
{
    ushort crc;
    byte * pointer;

    crc = Crc16(bufferPointer, sum);

    pointer = bufferPointer + sum;
    
    *pointer++ = Byte1(crc);
    *pointer = Byte0(crc);
    sum = sum + 2;
    System.Device.Usart3.Write(bufferPointer, sum);
}

/*************************************************************************************
* ��������˿ڶ�ȡ
*************************************************************************************/
static void Read0x(ushort address)
{
    int i;
    byte byteSum, packetSum;
    ushort bitSum;
    byte * pointer;

    TxdBuffer[0] = RxdBuffer[0];      //֡��ַ
    TxdBuffer[1] = RxdBuffer[1];      //������
    
    Byte1(bitSum) = RxdBuffer[4];  
    Byte0(bitSum) = RxdBuffer[5];  //����˿���

    
    if (bitSum & 0x07)                  //���˿����Ƿ���8�ı���
        byteSum = (bitSum >> 3) + 1;    //ȷ���ֽ���
    else
        byteSum = bitSum >> 3;
    
    TxdBuffer[2] = byteSum;            //�ֽ���

    pointer = &TxdBuffer[3];           //����շ�������
    for (i = 0; i < byteSum; i++)       
        *pointer = false;

    for (i = 0; i < bitSum; i++)        //д��˿���Ϣ
    {
        if (*(bool *)(DataBase + (uint)Block0x[address + i]) == true) //��������ָ������
            pointer[i >> 3] |= 1 << (i & 7);
    }

    packetSum = TxdBuffer[2] + 3;

    Response(TxdBuffer, packetSum);
}

/*************************************************************************************
* ��������˿ڶ�ȡ
*************************************************************************************/
static void Read1x(ushort address)
{
    int i, packetSum;
    ushort bitSum, byteSum;
    byte * pointer;

    TxdBuffer[0] = RxdBuffer[0];      //֡��ַ
    TxdBuffer[1] = RxdBuffer[1];      //������
    
    Byte1(bitSum) = RxdBuffer[4];
    Byte0(bitSum) = RxdBuffer[5];

    
    if (bitSum & 0x07)
        byteSum = (bitSum >> 3) + 1;
    else
        byteSum = bitSum >> 3;
    
    TxdBuffer[2] = byteSum;            //�ֽ���

    pointer = &TxdBuffer[3];           //������������
    for (i = 0; i < byteSum; i++)       
        *pointer = false;

    for (i = 0; i < bitSum; i++)        //д��bit��Ϣ,msOS�д洢bit��Ϣ����Byte�������洢
    {
        if (*(bool *)(DataBase + (uint)Block1x[address + i]) == true)
            pointer[i >> 3] |= 1 << (i & 7);
    }

    packetSum = TxdBuffer[2] + 3;

    Response(TxdBuffer, packetSum);
}

/*************************************************************************************
* ��Ȧ����д����
*************************************************************************************/
static void WriteSingle0x(ushort address)
{
    ushort bitFlag;

    Byte1(bitFlag) = RxdBuffer[4];
    Byte0(bitFlag) = RxdBuffer[5];
        
    if (bitFlag == 0xFF00)                                  //true:0xFF00
        *(bool *)(DataBase + (uint)Block0x[address]) = true;
    else                                                    //false:0x0000
        *(bool *)(DataBase + (uint)Block0x[address]) = false;
    
    System.Device.Usart3.Write(RxdBuffer, RxdCounter);    //Ӧ��֡��������֡��ͬ
}

/*************************************************************************************
* ��Ȧ���д����������Ӧ
*************************************************************************************/
static void Write0x(ushort address)
{
    int i;
    ushort bitSum;
    byte * pointer;
    
    Byte1(bitSum) = RxdBuffer[4];
    Byte0(bitSum) = RxdBuffer[5];

    pointer = &RxdBuffer[6];
    for (i = 0; i < bitSum; i++)
        *(bool *)(DataBase + (uint)Block0x[address + i]) = GetBit(pointer[i >> 3], i & 0x07);

    memcpy(TxdBuffer, RxdBuffer, 6);

    Response(TxdBuffer, 6);
}

/*************************************************************************************
* Adc���봦��
*************************************************************************************/
static void Read3x(ushort address)
{
    int i, packetSum;
    ushort registerSum, data;
    byte * pointer;
    
    TxdBuffer[0] = RxdBuffer[0];      //֡��ַ
    TxdBuffer[1] = RxdBuffer[1];      //������
    
    Byte1(registerSum) = RxdBuffer[4];
    Byte0(registerSum) = RxdBuffer[5];
    
    TxdBuffer[2] = registerSum << 1;   //�ֽ��� registerSum <= 0x7D��register��ushort����

    pointer = &TxdBuffer[3];
    for (i = 0; i < registerSum; i++)
    {
        data = *(ushort *)(DataBase + (uint)Block3x[address++]);
        *pointer++ = Byte1(data);
        *pointer++ = Byte0(data);
    }

    packetSum = TxdBuffer[2] + 3;
    
    Response(TxdBuffer, packetSum);
}

/*************************************************************************************
* �Ĵ�����������Ӧ
*************************************************************************************/
static void Read4x(ushort address)
{
    int i, packetSum;
    ushort registerSum, data;
    byte * pointer;
    
    TxdBuffer[0] = RxdBuffer[0];      //֡��ַ
    TxdBuffer[1] = RxdBuffer[1];      //������
    
    Byte1(registerSum) = RxdBuffer[4];
    Byte0(registerSum) = RxdBuffer[5];
    
    TxdBuffer[2] = registerSum << 1;   //�ֽ��� registerSum <= 0x7D��register��ushort����

    pointer = &TxdBuffer[3];
    for (i = 0; i < registerSum; i++)
    {
        data = *(ushort *)(DataBase + (uint)Block4x[address++]);
        *pointer++ = Byte1(data);
        *pointer++ = Byte0(data);
    }

    packetSum = TxdBuffer[2] + 3;
    
    Response(TxdBuffer, packetSum);
}
/*************************************************************************************
* �Ĵ�������д����������Ӧ
*************************************************************************************/
static void WriteSingle4x(ushort address)
{
    ushort data;

    Byte1(data) = RxdBuffer[4];
    Byte0(data) = RxdBuffer[5];

    *(ushort *)(DataBase + (uint)Block4x[address]) = data;
    
    System.Device.Usart3.Write(RxdBuffer, RxdCounter);
}

/*************************************************************************************
*
* ��Ĵ���д����������Ӧ
*
*************************************************************************************/
static void Write4x(ushort address)
{
    int i;
    ushort registerSum, data;
    byte * pointer;
    
    Byte1(registerSum) = RxdBuffer[4];
    Byte0(registerSum) = RxdBuffer[5];

    pointer = &RxdBuffer[7];                   //ǰ�滹��һ���ֽ�������6λ��
    for (i = 0; i < registerSum; i++)
    {
        Byte1(data) = *pointer++;
        Byte0(data) = *pointer++;

        *(ushort *)(DataBase + (uint)Block4x[address++]) = data;
    }
    
    memcpy(TxdBuffer, RxdBuffer, 6);

    Response(TxdBuffer, 6);
}



/************************************************************************************
* ���ݽ��ո�λ
*************************************************************************************/
static void RxdReset()
{
    RxdCounter = 0;
    RxdTimeout = 0;
    RxdState = no;
}

/*************************************************************************************
* MODBUS����֡����:�������
* ���룺ָʾ�Ѿ����յ�һ֡���ݹ��Ӻ���ָ�룬��Ӧָʾ���Ӻ���ָ��
* ������ѭ������
*************************************************************************************/
static void ParseRxdFrame(void)
{
    ushort address, crcCalculate , crcReceive;

    if (RxdBuffer[0] != DeviceID)
    {
        RxdReset(); return;
    }
        
    if (RxdCounter < 4)
    {
        RxdReset(); return;
    }
        
    crcCalculate = Crc16(RxdBuffer, RxdCounter - 2);
    Byte1(crcReceive) = RxdBuffer[RxdCounter - 2];
    Byte0(crcReceive) = RxdBuffer[RxdCounter - 1];
    
    if (crcCalculate != crcReceive)     //У��
    {
        RxdReset(); return;
    }
    
    Byte1(address) = RxdBuffer[2]; //��ȡ��λ��ַ
    Byte0(address) = RxdBuffer[3]; //��ȡ��λ��ַ
    
    switch(RxdBuffer[1])                       //ʶ��֧�ֵĹ�����
    {
        case ReadDataOutPort0X:
            Read0x(address);
            break;
            
        case ReadDataInPort1X:
            Read1x(address);
            break;
            
        case ReadAdcInPort3X:
            Read3x(address);
            break;
            
        case ReadRegister4X:
            Read4x(address);
            break;
        
        case WriteSingleDataOutPort0X:
            WriteSingle0x(address);
            break;
            
        case WriteSingleRegister4X:
            WriteSingle4x(address);
            break;

        case WriteDataOutPort0X:
            Write0x(address);
            break;
            
        case WriteRegister4X:
            Write4x(address);
            break;

        case ReadWriteRegister4X:
            break;
        case MaskRegister:
            break;
        case ReadDeviceID:
            break;  
        default:
            break;
    }

    RxdReset();
}

/*************************************************************************************
* ���ջ���
*************************************************************************************/
static void DataReceive(byte data)
{
    if(RxdCounter >= RxdBufferSum)
        RxdCounter = 0;
		
    RxdBuffer[RxdCounter++] = data;

    RxdTimeout = 0;//1 
    RxdState = yes;
}

/*************************************************************************************
* MODBUS���ջ�������ʱ����
* ÿ0.1MS������һ��
* ����ȷ��MODBUS������һ֡����
*************************************************************************************/
static void RxdTimeOutRoutine(void)
{
    if (RxdState == yes)
    {
        RxdTimeout++;
        if (RxdTimeout > TimeoutSum)
        {
            RxdState = no;
            ParseRxdFrame();
        }
    }
}


/************************************************************************************
* MODBUS��ʼ��
*************************************************************************************/
void InitHostModbus(void)
{
    RxdReset();
    
    System.Device.Systick.Register(Systick10000, RxdTimeOutRoutine);    

    System.Device.Usart3.Register((uint)TxdBuffer, (uint)DataReceive);
}
 
#endif


