/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2020-08-20
 * @brief    �½�����ʵ��-HAL��汾 ʵ��
 * @license  Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ******************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� STM32F103 ������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"




int main(void)
{
		HAL_Init(); /* ��ʼ�� HAL �� */
		sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
		delay_init(72); /* ��ʱ��ʼ�� */
		usart_init(115200); /* ���ڳ�ʼ��Ϊ 115200 */
		led_init(); /* ��ʼ�� LED */
		
		extix_init(); /* ��ʼ���ⲿ�ж����� */
		//LED0(0); /* �ȵ������ */
		while (1)
		{
			printf("OK\r\n");
			delay_ms(1000);
		}
}

