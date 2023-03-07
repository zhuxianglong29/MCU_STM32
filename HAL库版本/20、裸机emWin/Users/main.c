/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       �޲���ϵͳ---emWin��ֲʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./MALLOC/malloc.h"
#include "./BSP/BTIM/btim.h"
#include "./BSP/TOUCH/touch.h"
#include "GUI.h"
#include "GUIDemo.h"
#include "WM.h"


int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    //usmart_dev.init(72);                /* ��ʼ��USMART */
    lcd_init(); /* ��ʼ�� LCD */
		tp_dev.init(); /* ��������ʼ�� */
		btim_timx_int_init(999,71); /* ��ʱ 1ms �����ṩ emWin ���� */
		__HAL_RCC_CRC_CLK_ENABLE(); /* ʹ�� CRC ʱ�� */
		GUI_Init(); /* emWin ��ʼ�� */
		GUIDEMO_Main();
    while(1);
}
