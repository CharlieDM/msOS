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
*�ļ���     : app.c
*����       : Ӧ�ó������
*ԭ��       : Ӧ�ò���ڣ�Ҳ��ϵͳ��ڣ���Ҫ��ʼ����������������
*           : ����LogicTask��MenuTask,����LogicTask�ڵ���Ϣ          
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/07/21       ��ʼ�汾
********************************************************************************
*/


#include "system.h"
#include "app.h"

AppStruct App;

/*******************************************************************************
* ����	    : ��ʼ�����ݿ�
*******************************************************************************/
static void InitData(void)
{
    AppDataPointer = &(App.Data);
    
    App.Data.Frequency = 900000;
    App.Data.PowerPercent = 20;
    App.Data.Power = 6000;
    App.Data.Voltage = 99;
    App.Data.Current = 101;
    App.Data.Temperature = 25;
    App.Data.OnOff = "��";
    
    
    App.Data.MaxPower = 6000;
    App.Data.MaxTemperature = 50;
    App.Data.MaxFrequency = 980000;
    App.Data.MaxFrequencyOffset = 100000;
    App.Data.MaxPress = 2.0;
    App.Data.State = 1;
    App.Data.Rtc.Day = 0;
    App.Data.Rtc.Hour = 0;
    App.Data.Rtc.Minute = 0;
    App.Data.Rtc.Second = 0;

    App.Data.SerialNumber = 0;
    App.Data.Year = 14;
    App.Data.Month = 9;
    App.Data.Day = 11;

    App.Data.IdentifyNumber0 = GetUintFrom(IdentifyNumberAddress);
    App.Data.IdentifyNumber1 = GetUintFrom(IdentifyNumberAddress + 4);
    App.Data.IdentifyNumber2 = GetUintFrom(IdentifyNumberAddress + 8);

    App.Menu.FocusFormPointer = (Form *)0;
}

/*******************************************************************************
* ����	    : C�������Main����
*******************************************************************************/
int main(void) 
{      
    InitData();
    System.Init();                          // ��ʼ��ϵͳ��

    System.OS.CreateLogicTask(LogicTask);   // ����ҵ���߼�����
    System.OS.CreateMenuTask(MenuTask);     // �����˵���������
    
    System.OS.Start();
    EnableIrq();                            // ���ж�
}
