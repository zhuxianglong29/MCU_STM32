/**
 ******************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2020-08-20
 * @brief    新建工程实验-HAL库版本 实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 STM32F103 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/BTIM/btim.h"

void led_init(void);                       /* LED初始化函数声明 */

int main(void)
{
	HAL_Init(); /* 初始化 HAL 库 */
	sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
	delay_init(72); /* 延时初始化 */
	usart_init(115200); /* 串口初始化为 115200 */
	led_init(); /* 初始化 LED */
	btim_timx_int_init(5000 - 1, 7200 - 1); /* 10Khz 的计数频率，计数 5K 次为 500ms */
	while (1)
		{
		LED0_TOGGLE();
		delay_ms(200);
		}
}
