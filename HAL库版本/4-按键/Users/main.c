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
uint8_t key;
void led_init(void);                       /* LED��ʼ���������� */

int main(void)
{
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* ����ʱ��,72M */
    delay_init(72);                             /* ��ʼ����ʱ���� */
    led_init();                                 /* ��ʼ��LED */
		beep_init();
		key_init();
		usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    
    while(1)
    {
       key = key_scan(0); /* �õ���ֵ */
			if(key)
			{
				switch(key)
				{
					case 1:
						printf("K_UP");
						break;
					
					case 2:
						printf("K_LEFT");
						break;
					
					case 3:
						printf("K_DOWN");
						break;
					
					case 4:
						printf("K_RIGHT");
						break;
				}
			}
			else
			{
				delay_ms(10);
			}
				
    }
}

