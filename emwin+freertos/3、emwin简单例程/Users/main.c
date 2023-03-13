/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       无操作系统---emWin移植实验
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
#include "./BSP/BTIM/btim.h"
#include "./BSP/TOUCH/touch.h"
#include "GUI.h"

#include "WM.h"
//#include "emwin_demo.h"
#include "freertos_demo.h"


int main(void)
{
			HAL_Init(); /* 初始化 HAL 库 */
			sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
			delay_init(72); /* 延时初始化 */
			usart_init(115200); /* 串口初始化为 115200 */
			//usmart_dev.init(72); /* 初始化 USMART */
			led_init(); /* 初始化 LED */
			lcd_init(); /* 初始化 LCD */
			key_init(); /* 初始化按键 */
			//sram_init(); /* SRAM 初始化 */
			my_mem_init(SRAMIN); /* 初始化内部 SRAM 内存池 */
			//my_mem_init(SRAMEX); /* 初始化外部 SRAM 内存池 */
			tp_dev.init(); /* 触摸屏初始化 */
			LED0(0);//打开LED0
			freertos_demo(); /* 创建任务，并执行 emwin 例程 */

}
