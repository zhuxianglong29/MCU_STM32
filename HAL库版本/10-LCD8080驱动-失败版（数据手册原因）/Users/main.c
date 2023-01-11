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
#include "./BSP/LCD/lcd.h"

void led_init(void);                       /* LED��ʼ���������� */

int main(void)
{
     uint16_t point_value = 0;
    uint8_t x = 0;
    
    HAL_Init();                         /* HAL���ʼ�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                         /* ��ʼ��LED */
    lcd_init();
    
    lcd_draw_point(0, 0, RED);
    lcd_draw_point(0, 1, RED);
    lcd_draw_point(100, 100, RED);
    
    /* 0xF800 */
    point_value = lcd_read_point(100, 100);
    printf("point_value:%#x \r\n",point_value);

    lcd_show_char(0, 0, 'A', 16, 1, RED);
    lcd_show_char(100, 100, 'B', 24, 1, RED);

    
    while (1)
    {
        switch (x)
        {
        case 0:
            lcd_clear(WHITE);
            break;

        case 1:
            lcd_clear(BLACK);
            break;

        case 2:
            lcd_clear(BLUE);
            break;

        case 3:
            lcd_clear(RED);
            break;

        case 4:
            lcd_clear(MAGENTA);
            break;

        case 5:
            lcd_clear(GREEN);
            break;

        case 6:
            lcd_clear(CYAN);
            break;

        case 7:
            lcd_clear(YELLOW);
            break;

        case 8:
            lcd_clear(BRRED);
            break;

        case 9:
            lcd_clear(GRAY);
            break;

        case 10:
            lcd_clear(LGRAY);
            break;

        case 11:
            lcd_clear(BROWN);
            break;
        }

        x++;

        if (x == 12)
            x = 0;

        LED0_TOGGLE(); /* �����˸ */
        delay_ms(1000);
    }
}

