/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-21
 * @brief       �߼���ʱ�����ָ������PWM ʵ��
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

#include "./BSP/TIMER/atim.h"


int main(void)
{
    uint8_t key = 0;
    uint8_t t = 0;
    GPIO_InitTypeDef gpio_init_struct;

    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                         /* ��ʼ��LED */
   

    /* �� LED1 ��������Ϊ����ģʽ, �����PC6��ͻ */
    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                /* ����Ϊ���� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED1���� */

    atim_timx_npwm_chy_init(5000 - 1, 7200 - 1);            /* 10Khz�ļ���Ƶ��,2hz��PWMƵ��. */

    ATIM_TIMX_NPWM_CHY_CCRX = 2500; /* ����PWMռ�ձ�,50%,�������Կ���ÿһ��PWM����,LED1(BLUE)
                                     * ��һ��ʱ��������,һ��ʱ�������,LED1����һ��,��ʾһ��PWM��
                                     */
    atim_timx_npwm_chy_set(5);      /* ���5��PWM��(����LED1(BLUE)��˸5��) */

    while (1)
    {
       
            atim_timx_npwm_chy_set(5); /* ���5��PWM��(����TIM8_CH1, ��PC6���5������) */
             
						delay_ms(2000);
     
            LED0_TOGGLE();
		}
   
}


