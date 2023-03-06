/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       ������ʾ ʵ��
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
#include "./FATFS/exfuns/exfuns.h"
#include "./TEXT/text.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDIO/sdio_sdcard.h"
#include "./BSP/NORFLASH/norflash.h"


int main(void)
{
    uint32_t fontcnt;
    uint8_t i, j;
    uint8_t fontx[2]; /* GBK�� */
    uint8_t key, t;

    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(72);                /* ��ʼ��USMART */
    led_init();                         /* ��ʼ��LED */
    lcd_init();                         /* ��ʼ��LCD */
    key_init();                         /* ��ʼ������ */
    my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */

    exfuns_init();                      /* Ϊfatfs��ر��������ڴ� */
    f_mount(fs[0], "0:", 1);            /* ����SD�� */
    f_mount(fs[1], "1:", 1);            /* ����FLASH */

    while (fonts_init())                /* ����ֿ� */
    {
    UPD:
        lcd_clear(WHITE);               /* ���� */
        lcd_show_string(30, 30, 200, 16, 16, "STM32", RED);

        while (sd_init())               /* ���SD�� */
        {
            lcd_show_string(30, 50, 200, 16, 16, "SD Card Failed!", RED);
            delay_ms(200);
            lcd_fill(30, 50, 200 + 30, 50 + 16, WHITE);
            delay_ms(200);
        }

        lcd_show_string(30, 50, 200, 16, 16, "SD Card OK", RED);
        lcd_show_string(30, 70, 200, 16, 16, "Font Updating...", RED);
        key = fonts_update_font(20, 90, 16, (uint8_t *)"0:", RED); /* �����ֿ� */

        while (key) /* ����ʧ�� */
        {
            lcd_show_string(30, 90, 200, 16, 16, "Font Update Failed!", RED);
            delay_ms(200);
            lcd_fill(20, 90, 200 + 20, 90 + 16, WHITE);
            delay_ms(200);
        }

        lcd_show_string(30, 90, 200, 16, 16, "Font Update Success!   ", RED);
        delay_ms(1500);
        lcd_clear(WHITE); /* ���� */
    }

    text_show_string(30, 30, 200, 16, "����ԭ��STM32������", 16, 0, RED);
    text_show_string(30, 50, 200, 16, "GBK�ֿ���Գ���", 16, 0, RED);
    text_show_string(30, 70, 200, 16, "����ԭ��@ALIENTEK", 16, 0, RED);
    text_show_string(30, 90, 200, 16, "��KEY0,�����ֿ�", 16, 0, RED);
    
    
    text_show_string(30, 110, 200, 16, "������ֽ�:", 16, 0, BLUE);
    text_show_string(30, 130, 200, 16, "������ֽ�:", 16, 0, BLUE);
    text_show_string(30, 150, 200, 16, "���ּ�����:", 16, 0, BLUE);
    
    text_show_string(30, 180, 200, 24, "��Ӧ����Ϊ:", 24, 0, BLUE);
    text_show_string(30, 204, 200, 16, "��Ӧ����(16*16)Ϊ:", 16, 0, BLUE);
    text_show_string(30, 220, 200, 16, "��Ӧ����(12*12)Ϊ:", 12, 0, BLUE);

    while (1)
    {
        fontcnt = 0;

        for (i = 0x81; i < 0xff; i++) /* GBK������ֽڷ�ΧΪ0X81~0XFE */
        {
            fontx[0] = i;
            lcd_show_num(118, 130, i, 3, 16, BLUE); /* ��ʾ������ֽ� */

            for (j = 0x40; j < 0xfe; j++) /* GBK������ֽڷ�ΧΪ 0X40~0X7E, 0X80~0XFE) */
            {
                if (j == 0x7f)
                    continue;

                fontcnt++;
                lcd_show_num(118, 130, j, 3, 16, BLUE);       /* ��ʾ������ֽ� */
                lcd_show_num(118, 150, fontcnt, 5, 16, BLUE); /* ���ּ�����ʾ */
                fontx[1] = j;
                text_show_font(30 + 132, 180, fontx, 24, 0, BLUE);
                text_show_font(30 + 144, 204, fontx, 16, 0, BLUE);
                text_show_font(30 + 108, 220, fontx, 12, 0, BLUE);
                t = 200;

                while (t--) /* ��ʱ,ͬʱɨ�谴�� */
                {
                    delay_ms(1);
                    key = key_scan(0);

                    if (key == K_LEFT_PRES)
                    {
                        goto UPD; /* ��ת��UPDλ��(ǿ�Ƹ����ֿ�) */
                    }
                }

                LED0_TOGGLE();
            }
        }
    }
}









