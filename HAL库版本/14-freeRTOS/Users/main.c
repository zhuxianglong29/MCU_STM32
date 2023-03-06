/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       �ڴ���� ʵ��
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
#include "freertos_demo.h"




int main(void)
{
    uint8_t paddr[20];  /* ���P Addr:+p��ַ��ASCIIֵ */
    uint16_t memused = 0;
    uint8_t key;
    uint8_t i = 0;
    uint8_t *p = 0;
    uint8_t *tp = 0;

    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
 
    led_init();                         /* ��ʼ��LED */
    lcd_init();                         /* ��ʼ��LCD */
    key_init();                         /* ��ʼ������ */
   // my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */

   // lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
   // lcd_show_string(30,  70, 200, 16, 16, "MALLOC TEST", RED);
  //  lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
   // lcd_show_string(30, 110, 200, 16, 16, "KEY0:Malloc KEY1:Free", RED);
   // lcd_show_string(30, 130, 200, 16, 16, "KEY_UP:Write ", RED);
  //  lcd_show_string(30, 160, 200, 16, 16, "SRAMIN ", BLUE);
   // lcd_show_string(30, 176, 200, 16, 16, "SRAMIN   USED:", BLUE);
		
		freertos_demo();
}





























