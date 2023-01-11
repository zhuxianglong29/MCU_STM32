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
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"




int main(void)
{
		HAL_Init(); /* 初始化 HAL 库 */
		sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
		delay_init(72); /* 延时初始化 */
		usart_init(115200); /* 串口初始化为 115200 */
		led_init(); /* 初始化 LED */
		
		extix_init(); /* 初始化外部中断输入 */
		//LED0(0); /* 先点亮红灯 */
		while (1)
		{
			printf("OK\r\n");
			delay_ms(1000);
		}
}

