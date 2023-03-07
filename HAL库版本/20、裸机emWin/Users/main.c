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
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./MALLOC/malloc.h"
#include "./BSP/BTIM/btim.h"
#include "./BSP/TOUCH/touch.h"
#include "GUI.h"
#include "GUIDemo.h"
#include "WM.h"


int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
    //usmart_dev.init(72);                /* 初始化USMART */
    lcd_init(); /* 初始化 LCD */
		tp_dev.init(); /* 触摸屏初始化 */
		btim_timx_int_init(999,71); /* 定时 1ms 用来提供 emWin 心跳 */
		__HAL_RCC_CRC_CLK_ENABLE(); /* 使能 CRC 时钟 */
		GUI_Init(); /* emWin 初始化 */
		GUIDEMO_Main();
    while(1);
}
