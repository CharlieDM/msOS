/*
********************************************************************************
*                                嵌入式微系统
*                                   msOS
*
*                            硬件平台:msPLC DEMO
*                          主芯片:STM32F103R8T6/RBT6
*                           深圳市雨滴科技有限公司
*
*                                作者:王绍伟
*                                网名:凤舞天
*                                标识:Wangsw
*
*                                QQ:26033613
*                               QQ群:291235815
*                        淘宝店:http://52edk.taobao.com
*                      论坛:http://gongkong.eefocus.com/bbs/
*                博客:http://forum.eet-cn.com/BLOG_wangsw317_1268.HTM
********************************************************************************
*文件名     : device_di.c
*作用       : PLC开关量输入接口，PLC标识为X端
*原理       : 无
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2015/07/17       初始版本
********************************************************************************
*/

#include "drive.h"
#include "system.h"


static void PortRegister(void)
{
    AppDataPointer->DI.pX0 = (uint *)BitBand(GPIOA_IDR_ADDR, 4); 
    AppDataPointer->DI.pX1 = (uint *)BitBand(GPIOA_IDR_ADDR, 5);
    AppDataPointer->DI.pX2 = (uint *)BitBand(GPIOA_IDR_ADDR, 6);
    AppDataPointer->DI.pX3 = (uint *)BitBand(GPIOA_IDR_ADDR, 7);
}

void InitDI(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    

    PortRegister();
}

