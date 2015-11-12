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
*�ļ���     : device_rtc.c
*����       : ����ʱ���豸�����32.768KHz���������ʱ�ӣ�һ�����ھ��Ȳ��߳���
*ԭ��       : ����ϵͳ���Ĳ�����ʱ�ӷ�Ƶ��õ�ʱ���֡��룬�˾��Ȳ��ߣ�����һ�㳡��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/07/21       ��ʼ�汾
********************************************************************************
*/

#include "system.h"


/*******************************************************************************
* ����	    : Rtcϵͳʱ��100/S����10mSһ�ε���
*******************************************************************************/
void RtcSystick100Routine(void) 
{
    static byte Counter = 0;
    
    if (++Counter == 100)
    {
        Counter = 0;

        if (AppDataPointer->Rtc.Second < 59)
            AppDataPointer->Rtc.Second++;
        else
        {
            AppDataPointer->Rtc.Second = 0;
            if(AppDataPointer->Rtc.Minute < 59)
                AppDataPointer->Rtc.Minute++;
            else
            {
                AppDataPointer->Rtc.Minute = 0;
                if(AppDataPointer->Rtc.Hour < 23)
                    AppDataPointer->Rtc.Hour++;
                else
                {
                    AppDataPointer->Rtc.Hour = 0;
                    AppDataPointer->Rtc.Day++;
                } 
            }
        }
    }	
}

