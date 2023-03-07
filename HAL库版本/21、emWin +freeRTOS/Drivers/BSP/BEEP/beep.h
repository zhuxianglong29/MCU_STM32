#ifndef __BEEP_H_
#define __BEEP_H_
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

/* 引脚 定义 */
#define BEEP_GPIO_PORT GPIOB
#define BEEP_GPIO_PIN GPIO_PIN_5
/* PB 口时钟使能 */
#define BEEP_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)


/* BEEP 端口定义,通过不断翻转实现无源蜂鸣器鸣响 */
#define BEEP(x) do{ x ? \
HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET) : \
HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_RESET);\
}while(0) /* 翻转 */


void beep_init(void); 
void beep_buz(uint32_t nus);

#endif 
