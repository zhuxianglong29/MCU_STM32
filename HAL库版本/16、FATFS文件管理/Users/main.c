/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       FATFS ʵ��
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
#include "./MALLOC/malloc.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDIO/sdio_sdcard.h"
#include "./BSP/NORFLASH/norflash.h"
#include "./FATFS/exfuns/exfuns.h"


int main(void)
{
    uint32_t total, free;
    uint8_t t = 0;
    uint8_t res = 0;

    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(72);                /* ��ʼ��USMART */
    led_init();                         /* ��ʼ��LED */
    lcd_init();                         /* ��ʼ��LCD */
    key_init();                         /* ��ʼ������ */
    my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */

    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30,  70, 200, 16, 16, "FATFS TEST", RED);
    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "Use USMART for test", RED);

    while (sd_init()) /* ��ⲻ��SD�� */
    {
        lcd_show_string(30, 130, 200, 16, 16, "SD Card Error!", RED);
        delay_ms(500);
        lcd_show_string(30, 130, 200, 16, 16, "Please Check! ", RED);
        delay_ms(500);
        LED0_TOGGLE(); /* LED0��˸ */
    }

    exfuns_init();                 /* Ϊfatfs��ر��������ڴ� */
    f_mount(fs[0], "0:", 1);       /* ����SD�� */
    res = f_mount(fs[1], "1:", 1); /* ����FLASH. */

    if (res == 0X0D) /* FLASH����,FAT�ļ�ϵͳ����,���¸�ʽ��FLASH */
    {
        lcd_show_string(30, 130, 200, 16, 16, "Flash Disk Formatting...", RED); /* ��ʽ��FLASH */
        res = f_mkfs("1:", 0, 0, FF_MAX_SS);                                    /* ��ʽ��FLASH,1:,�̷�;0,ʹ��Ĭ�ϸ�ʽ������ */

        if (res == 0)
        {
            f_setlabel((const TCHAR *)"1:ALIENTEK");                                /* ����Flash���̵�����Ϊ��ALIENTEK */
            lcd_show_string(30, 130, 200, 16, 16, "Flash Disk Format Finish", RED); /* ��ʽ����� */
        }
        else
            lcd_show_string(30, 130, 200, 16, 16, "Flash Disk Format Error ", RED); /* ��ʽ��ʧ�� */

        delay_ms(1000);
    }

    lcd_fill(30, 130, 240, 150 + 16, WHITE); /* �����ʾ */

    while (exfuns_get_free((uint8_t*)"0", &total, &free)) /* �õ�SD������������ʣ������ */
    {
        lcd_show_string(30, 130, 200, 16, 16, "SD Card Fatfs Error!", RED);
        delay_ms(200);
        lcd_fill(30, 130, 240, 150 + 16, WHITE); /* �����ʾ */
        delay_ms(200);
        LED0_TOGGLE(); /* LED0��˸ */
    }

    lcd_show_string(30, 130, 200, 16, 16, "FATFS OK!", BLUE);
    lcd_show_string(30, 150, 200, 16, 16, "SD Total Size:     MB", BLUE);
    lcd_show_string(30, 170, 200, 16, 16, "SD  Free Size:     MB", BLUE);
    lcd_show_num(30 + 8 * 14, 150, total >> 10, 5, 16, BLUE); /* ��ʾSD�������� MB */
    lcd_show_num(30 + 8 * 14, 170, free >> 10, 5, 16, BLUE);  /* ��ʾSD��ʣ������ MB */

    while (1)
    {
        t++;
        delay_ms(200);
        LED0_TOGGLE(); /* LED0��˸ */
    }
}









