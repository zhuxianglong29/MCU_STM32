/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       内存管理 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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
    uint8_t paddr[20];  /* 存放P Addr:+p地址的ASCII值 */
    uint16_t memused = 0;
    uint8_t key;
    uint8_t i = 0;
    uint8_t *p = 0;
    uint8_t *tp = 0;

    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
 
    led_init();                         /* 初始化LED */
    lcd_init();                         /* 初始化LCD */
    key_init();                         /* 初始化按键 */
   // my_mem_init(SRAMIN);                /* 初始化内部SRAM内存池 */

   // lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
   // lcd_show_string(30,  70, 200, 16, 16, "MALLOC TEST", RED);
  //  lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
   // lcd_show_string(30, 110, 200, 16, 16, "KEY0:Malloc KEY1:Free", RED);
   // lcd_show_string(30, 130, 200, 16, 16, "KEY_UP:Write ", RED);
  //  lcd_show_string(30, 160, 200, 16, 16, "SRAMIN ", BLUE);
   // lcd_show_string(30, 176, 200, 16, 16, "SRAMIN   USED:", BLUE);
		
		freertos_demo();
}





























