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
*                        ��̳:http://bbs.huayusoft.com
*                        �Ա���:http://52edk.taobao.com
*                ����:http://forum.eet-cn.com/BLOG_wangsw317_1268.HTM
********************************************************************************
*�ļ���     : menu.c
*����       : �������
*ԭ��       : ���ӳ����а����������Form��ÿһ��������Լ���BackText�������֡�
*           : Chart��Label��ǩ��TextBox�ı�����ؼ�������Add��������֮��
*           : ��Ҫ��ʼ��ֵ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/07/21       ��ʼ�汾
********************************************************************************
*/

#include "system.h"
#include "app.h"




// �Լ�
static Chart CheckChart;


static TextBox FrequencyTextBox;
static TextBox PowerPercentTextBox;
static Label PowerLabel;
static Label VoltageLabel;
static Label CurrentLabel;
static Label TemperatureLabel;
static Label OnOffLabel;

static TextBox MaxPowerTextBox;
static TextBox MaxTemperatureTextBox;
static TextBox MaxFrequencyTextBox;
static TextBox MaxFrequencyOffsetTextBox;
static TextBox MaxPressTextBox;
static Label StateLabel;

static TextBox SerialNumberTextBox;
static TextBox YearTextBox;
static TextBox MonthTextBox;
static TextBox DayTextBox;
static Label IdentifyNumber0Label;
static Label IdentifyNumber1Label;
static Label IdentifyNumber2Label;

static TextBox RtcYearTextBox;
static TextBox RtcMonthTextBox;
static TextBox RtcWeekTextBox;
static TextBox RtcDayTextBox;
static TextBox RtcHourTextBox;
static TextBox RtcMinuteTextBox;
static TextBox RtcSecondTextBox;

static Label X0Label;
static Label X1Label;
static Label X2Label;
static Label X3Label;

static TextBox Y0TextBox;
static TextBox Y1TextBox;
static TextBox Y2TextBox;
static TextBox Y3TextBox;
static TextBox Y4TextBox;
static TextBox Y5TextBox;

static Label Adc0Label;
static Label Adc1Label;
static Label Adc2Label;
static Label Adc3Label;

static Label X0Label1;
static Label X1Label1;
static Label X2Label1;
static Label X3Label1;

static TextBox Y0TextBox1;
static TextBox Y1TextBox1;
static TextBox Y2TextBox1;
static TextBox Y3TextBox1;
static TextBox Y4TextBox1;
static TextBox Y5TextBox1;

static Label Adc0Label1;
static Label Adc1Label1;
static Label Adc2Label1;
static Label Adc3Label1;
static TextBox Reg1TextBox1;
static TextBox Reg0TextBox1;
static TextBox RegTextBox1;

const string OnOffString[] =
{
    "��", "��"
};

const string StateString[] = 
{
    "����ɨƵ",
    "��������",
    "��Ƶ����",
    "���๤��",
    "�쳣����"
};

const string WeekString[] = 
{
    "��", "һ", "��", "��", "��", "��", "��"
};


/*******************************************************************************
* ������	: InitializeMmi
* ����	    : ��ʼ��MMI,���ظ���ؼ�������������
* �������  : ��
* ���ز���  : ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/11       ��ʼ�汾
*******************************************************************************/
void InitMenu(void)
{
    byte i;

// Logo Form
    System.Gui.Form.Init(&App.Menu.LogoForm);
    App.Menu.LogoForm.BackTextPointer = "    ��οƼ�    "
                                        "      msOS      "
                                        "     V1.3.0     "
                                        "   2015.12.28   ";
// Check Form
    System.Gui.Form.Init(&App.Menu.CheckForm);
    CheckChart.Character = '*';
    for(i = 0; i < 16; i++)
        CheckChart.Column[i] = 0;

    App.Menu.CheckForm.ChartPointer = &CheckChart;

// Work Form
    System.Gui.Form.Init(&App.Menu.WorkForm);
    App.Menu.WorkForm.BackTextPointer = "Ƶ��          Hz"
                                        "����   %       W"
                                        "��ѹ    ����    "
                                        "�¶�   C        ";

    System.Gui.Form.AddTextBox(&App.Menu.WorkForm, &FrequencyTextBox);
    FrequencyTextBox.DataPointer = (void *)(&App.Data.Frequency);
    FrequencyTextBox.Type = GuiDataTypeIntDec;
    FrequencyTextBox.DataMax = 980000;
    FrequencyTextBox.DataMin = 600000;
    FrequencyTextBox.DataStep = 1000;
    FrequencyTextBox.DataBigStep = 10000;
    FrequencyTextBox.X = 13;
    FrequencyTextBox.Y = 0;
    
    System.Gui.Form.AddTextBox(&App.Menu.WorkForm, &PowerPercentTextBox);
    PowerPercentTextBox.DataPointer = (void *)(&App.Data.PowerPercent);
    PowerPercentTextBox.Type = GuiDataTypeIntDec;
    PowerPercentTextBox.DataMax = 100;
    PowerPercentTextBox.DataMin = 0;
    PowerPercentTextBox.DataStep = 1;
    PowerPercentTextBox.DataBigStep = 10;
    PowerPercentTextBox.X = 6;
    PowerPercentTextBox.Y = 1;
    
    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &PowerLabel);
    PowerLabel.DataPointer = (void *)(&App.Data.Power);
    PowerLabel.Type = GuiDataTypeIntDec;
    PowerLabel.X = 14;
    PowerLabel.Y = 1;
    
    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &VoltageLabel);
    VoltageLabel.DataPointer = (void *)(&App.Data.Voltage);
    VoltageLabel.Type = GuiDataTypeIntDec;
    VoltageLabel.X = 7;
    VoltageLabel.Y = 2;
    
    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &CurrentLabel);
    CurrentLabel.DataPointer = (void *)(&App.Data.Current);
    CurrentLabel.Type = GuiDataTypeIntDec;
    CurrentLabel.X = 15;
    CurrentLabel.Y = 2;
    
    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &TemperatureLabel);
    TemperatureLabel.DataPointer = (void *)(&App.Data.Temperature);
    TemperatureLabel.Type = GuiDataTypeIntDec;
    TemperatureLabel.X = 6;
    TemperatureLabel.Y = 3;

    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &OnOffLabel);
    OnOffLabel.DataPointer = (void *)(&App.Data.OnOff);
    OnOffLabel.Type = GuiDataTypeSnString;
    OnOffLabel.Align = GuiDataAlignRight;
    OnOffLabel.StringBlockPointer = OnOffString;
    OnOffLabel.X = 15;
    OnOffLabel.Y = 3;
    
// Setup Form
    System.Gui.Form.Init(&App.Menu.SetupForm);
    App.Menu.SetupForm.BackTextPointer = "����    �¶�   C"
                                         "Ƶ��   KƵƫ   K"
                                         "ˮѹ            "
                                         "                ";
    System.Gui.Form.AddTextBox(&App.Menu.SetupForm, &MaxPowerTextBox);
    MaxPowerTextBox.DataPointer = (void *)(&App.Data.MaxPower);
    MaxPowerTextBox.Type = GuiDataTypeIntDec;
    MaxPowerTextBox.DataMax = 7500;
    MaxPowerTextBox.DataMin = 4000;
    MaxPowerTextBox.DataStep = 500;
    MaxPowerTextBox.DataBigStep = 500;
    MaxPowerTextBox.X = 7;
    MaxPowerTextBox.Y = 0;
    
    System.Gui.Form.AddTextBox(&App.Menu.SetupForm, &MaxTemperatureTextBox);
    MaxTemperatureTextBox.DataPointer = (void *)(&App.Data.MaxTemperature);
    MaxTemperatureTextBox.Type = GuiDataTypeIntDec;
    MaxTemperatureTextBox.DataMax = 60;
    MaxTemperatureTextBox.DataMin = 40;
    MaxTemperatureTextBox.DataStep = 1;
    MaxTemperatureTextBox.DataBigStep = 1;
    MaxTemperatureTextBox.X = 14;
    MaxTemperatureTextBox.Y = 0;
    
    System.Gui.Form.AddTextBox(&App.Menu.SetupForm, &MaxFrequencyTextBox);
    MaxFrequencyTextBox.DataPointer = (void *)(&App.Data.MaxFrequency);
    MaxFrequencyTextBox.Type = GuiDataTypeIntDec;
    MaxFrequencyTextBox.DataMax = 980000;
    MaxFrequencyTextBox.DataMin = 500000;
    MaxFrequencyTextBox.DataStep = 100000;
    MaxFrequencyTextBox.DataBigStep = 100000;
    MaxFrequencyTextBox.Coefficient = 0.001;
    MaxFrequencyTextBox.X = 6;
    MaxFrequencyTextBox.Y = 1;
    
    System.Gui.Form.AddTextBox(&App.Menu.SetupForm, &MaxFrequencyOffsetTextBox);
    MaxFrequencyOffsetTextBox.DataPointer = (void *)(&App.Data.MaxFrequencyOffset);
    MaxFrequencyOffsetTextBox.Type = GuiDataTypeIntDec;
    MaxFrequencyOffsetTextBox.DataMax = 100000;
    MaxFrequencyOffsetTextBox.DataMin = 50000;
    MaxFrequencyOffsetTextBox.DataStep = 10000;
    MaxFrequencyOffsetTextBox.DataBigStep = 10000;
    MaxFrequencyOffsetTextBox.Coefficient = 0.001;
    MaxFrequencyOffsetTextBox.X = 14;
    MaxFrequencyOffsetTextBox.Y = 1;

    System.Gui.Form.AddTextBox(&App.Menu.SetupForm, &MaxPressTextBox);
    MaxPressTextBox.DataPointer = (void *)(&App.Data.MaxPress);
    MaxPressTextBox.Type = GuiDataTypeFloatDec;
    MaxPressTextBox.Digits = 1;
    Float(MaxPressTextBox.DataMax) = 5.0;
    Float(MaxPressTextBox.DataMin) = 1.0;
    Float(MaxPressTextBox.DataStep) = 0.1;
    Float(MaxPressTextBox.DataBigStep) = 0.5;
    MaxPressTextBox.X = 7;
    MaxPressTextBox.Y = 2; 

    System.Gui.Form.AddLabel(&App.Menu.SetupForm, &StateLabel);
    StateLabel.DataPointer = (void *)(&App.Data.State);
    StateLabel.Type = GuiDataTypeSnString;
    StateLabel.Align = GuiDataAlignLeft;
    StateLabel.StringBlockPointer = StateString;
    StateLabel.X = 8;
    StateLabel.Y = 2; 

// Service Form
    System.Gui.Form.Init(&App.Menu.ServiceForm);
    App.Menu.ServiceForm.BackTextPointer = "�������        "
                                           "��������  :  :  "
                                           "                "
                                           "                ";
    System.Gui.Form.AddTextBox(&App.Menu.ServiceForm, &SerialNumberTextBox);
    SerialNumberTextBox.DataPointer = (void *)(&App.Data.SerialNumber);
    SerialNumberTextBox.Type = GuiDataTypeUintDec;
    SerialNumberTextBox.DataMax = 10000;
    SerialNumberTextBox.DataMin = 1;
    SerialNumberTextBox.DataStep = 1;
    SerialNumberTextBox.DataBigStep = 100;
    SerialNumberTextBox.X = 15;
    SerialNumberTextBox.Y = 0;

    System.Gui.Form.AddTextBox(&App.Menu.ServiceForm, &YearTextBox);
    YearTextBox.DataPointer = (void *)(&App.Data.Year);
    YearTextBox.Type = GuiDataTypeIntDec;
    YearTextBox.DataMax = 99;
    YearTextBox.DataMin = 14;
    YearTextBox.DataStep = 1;
    YearTextBox.DataBigStep = 10;
    YearTextBox.X = 9;
    YearTextBox.Y = 1;

    System.Gui.Form.AddTextBox(&App.Menu.ServiceForm, &MonthTextBox);
    MonthTextBox.DataPointer = (void *)(&App.Data.Month);
    MonthTextBox.Type = GuiDataTypeIntDec;
    MonthTextBox.DataMax = 12;
    MonthTextBox.DataMin = 1;
    MonthTextBox.DataStep = 1;
    MonthTextBox.DataBigStep = 10;
    MonthTextBox.X = 12;
    MonthTextBox.Y = 1;

    System.Gui.Form.AddTextBox(&App.Menu.ServiceForm, &DayTextBox);
    DayTextBox.DataPointer = (void *)(&App.Data.Day);
    DayTextBox.Type = GuiDataTypeIntDec;
    DayTextBox.DataMax = 31;
    DayTextBox.DataMin = 1;
    DayTextBox.DataStep = 1;
    DayTextBox.DataBigStep = 10;
    DayTextBox.X = 15;
    DayTextBox.Y = 1;
   
    System.Gui.Form.AddLabel(&App.Menu.ServiceForm, &IdentifyNumber0Label);
    IdentifyNumber0Label.DataPointer = (void *)(&App.Data.IdentifyNumber0);
    IdentifyNumber0Label.Type = GuiDataTypeUintHex;
    IdentifyNumber0Label.X = 7;
    IdentifyNumber0Label.Y = 2;
    IdentifyNumber0Label.Digits= 8;
    
    System.Gui.Form.AddLabel(&App.Menu.ServiceForm, &IdentifyNumber1Label);
    IdentifyNumber1Label.DataPointer = (void *)(&App.Data.IdentifyNumber1);
    IdentifyNumber1Label.Type = GuiDataTypeUintHex;
    IdentifyNumber1Label.X = 15;
    IdentifyNumber1Label.Y = 2;
    IdentifyNumber1Label.Digits = 8;
    
    System.Gui.Form.AddLabel(&App.Menu.ServiceForm, &IdentifyNumber2Label);
    IdentifyNumber2Label.DataPointer = (void *)(&App.Data.IdentifyNumber2);
    IdentifyNumber2Label.Type = GuiDataTypeUintHex;
    IdentifyNumber2Label.X = 7;
    IdentifyNumber2Label.Y = 3;
    IdentifyNumber2Label.Digits = 8;

// Time Form
    System.Gui.Form.Init(&App.Menu.TimeForm);
    App.Menu.TimeForm.BackTextPointer = "    ʱ    ��    "
                                        "                "
                                        "      ��  ��  ��"
                                        "����      :  :  ";
    System.Gui.Form.AddTextBox(&App.Menu.TimeForm, &RtcYearTextBox);
    RtcYearTextBox.DataPointer = (void *)(&App.Data.Rtc.Year);
    RtcYearTextBox.Type = GuiDataTypeUshortDec;
    RtcYearTextBox.DataMax = 2100;
    RtcYearTextBox.DataMin = 2000;
    RtcYearTextBox.DataStep = 1;
    RtcYearTextBox.DataBigStep = 10;
    RtcYearTextBox.X = 5;
    RtcYearTextBox.Y = 2; 

    System.Gui.Form.AddTextBox(&App.Menu.TimeForm, &RtcMonthTextBox);
    RtcMonthTextBox.DataPointer = (void *)(&App.Data.Rtc.Month);
    RtcMonthTextBox.Type = GuiDataTypeByteDec;
    RtcMonthTextBox.DataMax = 12;
    RtcMonthTextBox.DataMin = 1;
    RtcMonthTextBox.DataStep = 1;
    RtcMonthTextBox.DataBigStep = 2;
    RtcMonthTextBox.X = 9;
    RtcMonthTextBox.Y = 2; 

    System.Gui.Form.AddTextBox(&App.Menu.TimeForm, &RtcDayTextBox);
    RtcDayTextBox.DataPointer = (void *)(&App.Data.Rtc.Day);
    RtcDayTextBox.Type = GuiDataTypeByteDec;
    RtcDayTextBox.DataMax = 31;
    RtcDayTextBox.DataMin = 0;
    RtcDayTextBox.DataStep = 1;
    RtcDayTextBox.DataBigStep = 1;
    RtcDayTextBox.X = 13;
    RtcDayTextBox.Y = 2;

    System.Gui.Form.AddTextBox(&App.Menu.TimeForm, &RtcWeekTextBox);
    RtcWeekTextBox.DataPointer = (void *)(&App.Data.Rtc.Week);
    RtcWeekTextBox.Type = GuiDataTypeSnString;
    RtcWeekTextBox.Align = GuiDataAlignLeft;
    RtcWeekTextBox.StringBlockPointer = WeekString;
    RtcWeekTextBox.DataMax = 6;
    RtcWeekTextBox.DataMin = 0;
    RtcWeekTextBox.DataStep = 1;
    RtcWeekTextBox.DataBigStep = 1;
    RtcWeekTextBox.X = 4;
    RtcWeekTextBox.Y = 3; 

    System.Gui.Form.AddTextBox(&App.Menu.TimeForm, &RtcHourTextBox);
    RtcHourTextBox.DataPointer = (void *)(&App.Data.Rtc.Hour);
    RtcHourTextBox.Type = GuiDataTypeByteDec;
    RtcHourTextBox.DataMax = 59;
    RtcHourTextBox.DataMin = 0;
    RtcHourTextBox.DataStep = 1;
    RtcHourTextBox.DataBigStep = 1;
    RtcHourTextBox.X = 9;
    RtcHourTextBox.Y = 3; 

    System.Gui.Form.AddTextBox(&App.Menu.TimeForm, &RtcMinuteTextBox);
    RtcMinuteTextBox.DataPointer = (void *)(&App.Data.Rtc.Minute);
    RtcMinuteTextBox.Type = GuiDataTypeByteDec;
    RtcMinuteTextBox.DataMax = 59;
    RtcMinuteTextBox.DataMin = 0;
    RtcMinuteTextBox.DataStep = 1;
    RtcMinuteTextBox.DataBigStep = 1;
    RtcMinuteTextBox.X = 12;
    RtcMinuteTextBox.Y = 3; 

    System.Gui.Form.AddTextBox(&App.Menu.TimeForm, &RtcSecondTextBox);
    RtcSecondTextBox.DataPointer = (void *)(&App.Data.Rtc.Second);
    RtcSecondTextBox.Type = GuiDataTypeByteDec;
    RtcSecondTextBox.DataMax = 59;
    RtcSecondTextBox.DataMin = 0;
    RtcSecondTextBox.DataStep = 1;
    RtcSecondTextBox.DataBigStep = 1;
    RtcSecondTextBox.X = 15;
    RtcSecondTextBox.Y = 3;

// Port Form
    System.Gui.Form.Init(&App.Menu.PortForm);
    App.Menu.PortForm.BackTextPointer = "X   :   Y       "
                                          "A0:     A1:     "
                                          "A2:     A3:     "
                                          "                ";
    System.Gui.Form.AddLabel(&App.Menu.PortForm, &X0Label);
    X0Label.DataPointer = (void *)(App.Data.DI.pX0);
    X0Label.Type = GuiDataTypeByteDec;
    X0Label.X = 2;
    X0Label.Y = 0; 
    
    System.Gui.Form.AddLabel(&App.Menu.PortForm, &X1Label);
    X1Label.DataPointer = (void *)(App.Data.DI.pX1);
    X1Label.Type = GuiDataTypeByteDec;
    X1Label.X = 3;
    X1Label.Y = 0; 

    System.Gui.Form.AddLabel(&App.Menu.PortForm, &X2Label);
    X2Label.DataPointer = (void *)(App.Data.DI.pX2);
    X2Label.Type = GuiDataTypeByteDec;
    X2Label.X = 4;
    X2Label.Y = 0; 
    
    System.Gui.Form.AddLabel(&App.Menu.PortForm, &X3Label);
    X3Label.DataPointer = (void *)(App.Data.DI.pX3);
    X3Label.Type = GuiDataTypeByteDec;
    X3Label.X = 5;
    X3Label.Y = 0; 
    /***********************************************/
    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y0TextBox);
    Y0TextBox.DataPointer = (void *)(&App.Data.DO.Y0);
    Y0TextBox.Type = GuiDataTypeByteDec;
    Y0TextBox.X = 10;
    Y0TextBox.Y = 0;
    Y0TextBox.DataMax = 1;
    Y0TextBox.DataMin = 0;
    Y0TextBox.DataStep = 1;
    Y0TextBox.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y1TextBox);
    Y1TextBox.DataPointer = (void *)(&App.Data.DO.Y1);
    Y1TextBox.Type = GuiDataTypeByteDec;
    Y1TextBox.X = 11;
    Y1TextBox.Y = 0;
    Y1TextBox.DataMax = 1;
    Y1TextBox.DataMin = 0;
    Y1TextBox.DataStep = 1;
    Y1TextBox.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y2TextBox);
    Y2TextBox.DataPointer = (void *)(&App.Data.DO.Y2);
    Y2TextBox.Type = GuiDataTypeByteDec;
    Y2TextBox.X = 12;
    Y2TextBox.Y = 0;
    Y2TextBox.DataMax = 1;
    Y2TextBox.DataMin = 0;
    Y2TextBox.DataStep = 1;
    Y2TextBox.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y3TextBox);
    Y3TextBox.DataPointer = (void *)(&App.Data.DO.Y3);
    Y3TextBox.Type = GuiDataTypeByteDec;
    Y3TextBox.X = 13;
    Y3TextBox.Y = 0;
    Y3TextBox.DataMax = 1;
    Y3TextBox.DataMin = 0;
    Y3TextBox.DataStep = 1;
    Y0TextBox.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y4TextBox);
    Y4TextBox.DataPointer = (void *)(&App.Data.DO.Y4);
    Y4TextBox.Type = GuiDataTypeByteDec;
    Y4TextBox.X = 14;
    Y4TextBox.Y = 0;
    Y4TextBox.DataMax = 1;
    Y4TextBox.DataMin = 0;
    Y4TextBox.DataStep = 1;
    Y4TextBox.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y5TextBox);
    Y5TextBox.DataPointer = (void *)(&App.Data.DO.Y5);
    Y5TextBox.Type = GuiDataTypeByteDec;
    Y5TextBox.X = 15;
    Y5TextBox.Y = 0;
    Y5TextBox.DataMax = 1;
    Y5TextBox.DataMin = 0;
    Y5TextBox.DataStep = 1;
    Y5TextBox.DataBigStep = 1;
    /***********************************************/
    System.Gui.Form.AddLabel(&App.Menu.PortForm, &Adc0Label);
    Adc0Label.DataPointer = (void *)(App.Data.Adc.pA0);
    Adc0Label.Type = GuiDataTypeUshortDec;
    Adc0Label.X = 6;
    Adc0Label.Y = 1;   

    System.Gui.Form.AddLabel(&App.Menu.PortForm, &Adc1Label);
    Adc1Label.DataPointer = (void *)(App.Data.Adc.pA1);
    Adc1Label.Type = GuiDataTypeUshortDec;
    Adc1Label.X = 15;
    Adc1Label.Y = 1;   

    System.Gui.Form.AddLabel(&App.Menu.PortForm, &Adc2Label);
    Adc2Label.DataPointer = (void *)(App.Data.Adc.pA2);
    Adc2Label.Type = GuiDataTypeUshortDec;
    Adc2Label.X = 6;
    Adc2Label.Y = 2;   

    System.Gui.Form.AddLabel(&App.Menu.PortForm, &Adc3Label);
    Adc3Label.DataPointer = (void *)(App.Data.Adc.pA3);
    Adc3Label.Type = GuiDataTypeUshortDec;
    Adc3Label.X = 15;
    Adc3Label.Y = 2;  


// SubPlc Form
    System.Gui.Form.Init(&App.Menu.SubPlcForm);
    App.Menu.SubPlcForm.BackTextPointer = "X   :   Y       "
                                          "A0:     A1:     "
                                          "A2:     A3:     "
                                          "                ";
    System.Gui.Form.AddLabel(&App.Menu.SubPlcForm, &X0Label1);
    X0Label1.DataPointer = (void *)(&App.Data.SubPlc.DI.X0);
    X0Label1.Type = GuiDataTypeByteDec;
    X0Label1.X = 2;
    X0Label1.Y = 0; 
    
    System.Gui.Form.AddLabel(&App.Menu.SubPlcForm, &X1Label1);
    X1Label1.DataPointer = (void *)(&App.Data.SubPlc.DI.X1);
    X1Label1.Type = GuiDataTypeByteDec;
    X1Label1.X = 3;
    X1Label1.Y = 0; 

    System.Gui.Form.AddLabel(&App.Menu.SubPlcForm, &X2Label1);
    X2Label1.DataPointer = (void *)(&App.Data.SubPlc.DI.X2);
    X2Label1.Type = GuiDataTypeByteDec;
    X2Label1.X = 4;
    X2Label1.Y = 0; 
    
    System.Gui.Form.AddLabel(&App.Menu.SubPlcForm, &X3Label1);
    X3Label1.DataPointer = (void *)(&App.Data.SubPlc.DI.X3);
    X3Label1.Type = GuiDataTypeByteDec;
    X3Label1.X = 5;
    X3Label1.Y = 0; 
    /***********************************************/
    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &Y0TextBox1);
    Y0TextBox1.DataPointer = (void *)(&App.Data.SubPlc.DO.Y0);
    Y0TextBox1.Type = GuiDataTypeByteDec;
    Y0TextBox1.X = 10;
    Y0TextBox1.Y = 0;
    Y0TextBox1.DataMax = 1;
    Y0TextBox1.DataMin = 0;
    Y0TextBox1.DataStep = 1;
    Y0TextBox1.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &Y1TextBox1);
    Y1TextBox1.DataPointer = (void *)(&App.Data.SubPlc.DO.Y1);
    Y1TextBox1.Type = GuiDataTypeByteDec;
    Y1TextBox1.X = 11;
    Y1TextBox1.Y = 0;
    Y1TextBox1.DataMax = 1;
    Y1TextBox1.DataMin = 0;
    Y1TextBox1.DataStep = 1;
    Y1TextBox1.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &Y2TextBox1);
    Y2TextBox1.DataPointer = (void *)(&App.Data.SubPlc.DO.Y2);
    Y2TextBox1.Type = GuiDataTypeByteDec;
    Y2TextBox1.X = 12;
    Y2TextBox1.Y = 0;
    Y2TextBox1.DataMax = 1;
    Y2TextBox1.DataMin = 0;
    Y2TextBox1.DataStep = 1;
    Y2TextBox1.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &Y3TextBox1);
    Y3TextBox1.DataPointer = (void *)(&App.Data.SubPlc.DO.Y3);
    Y3TextBox1.Type = GuiDataTypeByteDec;
    Y3TextBox1.X = 13;
    Y3TextBox1.Y = 0;
    Y3TextBox1.DataMax = 1;
    Y3TextBox1.DataMin = 0;
    Y3TextBox1.DataStep = 1;
    Y0TextBox1.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &Y4TextBox1);
    Y4TextBox1.DataPointer = (void *)(&App.Data.SubPlc.DO.Y4);
    Y4TextBox1.Type = GuiDataTypeByteDec;
    Y4TextBox1.X = 14;
    Y4TextBox1.Y = 0;
    Y4TextBox1.DataMax = 1;
    Y4TextBox1.DataMin = 0;
    Y4TextBox1.DataStep = 1;
    Y4TextBox1.DataBigStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &Y5TextBox1);
    Y5TextBox1.DataPointer = (void *)(&App.Data.SubPlc.DO.Y5);
    Y5TextBox1.Type = GuiDataTypeByteDec;
    Y5TextBox1.X = 15;
    Y5TextBox1.Y = 0;
    Y5TextBox1.DataMax = 1;
    Y5TextBox1.DataMin = 0;
    Y5TextBox1.DataStep = 1;
    Y5TextBox1.DataBigStep = 1;
    /***********************************************/
    System.Gui.Form.AddLabel(&App.Menu.SubPlcForm, &Adc0Label1);
    Adc0Label1.DataPointer = (void *)(&App.Data.SubPlc.Adc.A0);
    Adc0Label1.Type = GuiDataTypeUshortDec;
    Adc0Label1.X = 6;
    Adc0Label1.Y = 1;   

    System.Gui.Form.AddLabel(&App.Menu.SubPlcForm, &Adc1Label1);
    Adc1Label1.DataPointer = (void *)(&App.Data.SubPlc.Adc.A1);
    Adc1Label1.Type = GuiDataTypeUshortDec;
    Adc1Label1.X = 15;
    Adc1Label1.Y = 1;   

    System.Gui.Form.AddLabel(&App.Menu.SubPlcForm, &Adc2Label1);
    Adc2Label1.DataPointer = (void *)(&App.Data.SubPlc.Adc.A2);
    Adc2Label1.Type = GuiDataTypeUshortDec;
    Adc2Label1.X = 6;
    Adc2Label1.Y = 2;   

    System.Gui.Form.AddLabel(&App.Menu.SubPlcForm, &Adc3Label1);
    Adc3Label1.DataPointer = (void *)(&App.Data.SubPlc.Adc.A3);
    Adc3Label1.Type = GuiDataTypeUshortDec;
    Adc3Label1.X = 15;
    Adc3Label1.Y = 2; 
    /***********************************************/
    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &Reg1TextBox1);
    Reg1TextBox1.DataPointer = (void *)((ushort*)&App.Data.SubPlc.Reg + 1);
    Reg1TextBox1.Type = GuiDataTypeUshortHex;
    Reg1TextBox1.X = 3;
    Reg1TextBox1.Y = 3;
    Reg1TextBox1.DataMax = 0xFFFF;
    Reg1TextBox1.DataMin = 0;
    Reg1TextBox1.DataStep = 1;
    Reg1TextBox1.DataBigStep = 0x10;
    Reg1TextBox1.Digits = 4;

    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &Reg0TextBox1);
    Reg0TextBox1.DataPointer = (void *)((ushort*)&App.Data.SubPlc.Reg);
    Reg0TextBox1.Type = GuiDataTypeUshortHex;
    Reg0TextBox1.X = 7;
    Reg0TextBox1.Y = 3;
    Reg0TextBox1.DataMax = 0xFFFF;
    Reg0TextBox1.DataMin = 0;
    Reg0TextBox1.DataStep = 1;
    Reg0TextBox1.DataBigStep = 0x10;
    Reg0TextBox1.Digits = 4;
    
    System.Gui.Form.AddTextBox(&App.Menu.SubPlcForm, &RegTextBox1);
    RegTextBox1.DataPointer = (void *)(&App.Data.SubPlc.Reg);
    RegTextBox1.Type = GuiDataTypeIntDec;
    RegTextBox1.X = 15;
    RegTextBox1.Y = 3;
    RegTextBox1.DataMax = 999999;
    RegTextBox1.DataMin = 0;
    RegTextBox1.DataStep = 1;
    RegTextBox1.DataBigStep = 10;
}

/*******************************************************************************
* ������	: MenuTask
* ����	    : MenuTask���񣬱���Ϊ������ȼ����񣬽�������Form�ڵĸ����ؼ�������ʾ
* �������  : ��
* ���ز���  : ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/12/16       �޸İ汾
*******************************************************************************/
void MenuTask (void)
{
    static uint MenuSystick; 
    
    InitMenu();
    MenuSystick = App.Data.Systick1000 + 100;
    while(true)             
    {
        if (App.Data.Systick1000 >= MenuSystick)
        {
            MenuSystick = App.Data.Systick1000 + 100;
            System.Gui.Parse(App.Menu.FocusFormPointer);
        }
    }
}

