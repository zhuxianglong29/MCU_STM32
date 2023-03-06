#ifndef __BTIM_H_
#define __BTIM_H_
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"

/* 基本定时器 定义 */
/* TIMX 中断定义
* 默认是针对 TIM6/TIM7.
* 注意: 通过修改这 4 个宏定义,可以支持 TIM1~TIM8 任意一个定时器.
*/
#define BTIM_TIMX_INT TIM6
#define BTIM_TIMX_INT_IRQn TIM6_DAC_IRQn
#define BTIM_TIMX_INT_IRQHandler TIM6_DAC_IRQHandler
/* TIM6 时钟使能 */
#define BTIM_TIMX_INT_CLK_ENABLE() do{ __HAL_RCC_TIM6_CLK_ENABLE(); }while(0)

void btim_timx_int_init(uint16_t arr, uint16_t psc);

#endif 
