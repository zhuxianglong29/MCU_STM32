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

#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./MALLOC/malloc.h"
#include "./BSP/BTIM/btim.h"
#include "./BSP/TOUCH/touch.h"
#include "GUI.h"

#include "WM.h"
//#include "emwin_demo.h"
#include "freertos_demo.h"


int main(void)
{
			HAL_Init(); /* ��ʼ�� HAL �� */
			sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
			delay_init(72); /* ��ʱ��ʼ�� */
			usart_init(115200); /* ���ڳ�ʼ��Ϊ 115200 */
			//usmart_dev.init(72); /* ��ʼ�� USMART */
			led_init(); /* ��ʼ�� LED */
			lcd_init(); /* ��ʼ�� LCD */
			key_init(); /* ��ʼ������ */
			//sram_init(); /* SRAM ��ʼ�� */
			my_mem_init(SRAMIN); /* ��ʼ���ڲ� SRAM �ڴ�� */
			//my_mem_init(SRAMEX); /* ��ʼ���ⲿ SRAM �ڴ�� */
			tp_dev.init(); /* ��������ʼ�� */
			LED0(0);//��LED0
			freertos_demo(); /* �������񣬲�ִ�� emwin ���� */

}
