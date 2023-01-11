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

void led_init(void);                       /* LED��ʼ���������� */

int main(void)
{
    HAL_Init();                              /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);      /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    led_init();                              /* LED��ʼ�� */
    
    while(1)
    { 
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);    /* PB5��1 */ 
        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);  /* PE5��0 */ 
        delay_ms(500);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);  /* PB5��0 */
        HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);    /* PE5��1 */
        delay_ms(500); 
    }
}

/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    __HAL_RCC_GPIOB_CLK_ENABLE();                          /* IO��PBʱ��ʹ�� */
    __HAL_RCC_GPIOE_CLK_ENABLE();                          /* IO��PEʱ��ʹ�� */

    gpio_initstruct.Pin = GPIO_PIN_5;                      /* LED0���� */
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_initstruct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);                /* ��ʼ��LED0���� */

    gpio_initstruct.Pin = GPIO_PIN_5;                      /* LED1���� */
    HAL_GPIO_Init(GPIOE, &gpio_initstruct);                /* ��ʼ��LED1���� */
}
