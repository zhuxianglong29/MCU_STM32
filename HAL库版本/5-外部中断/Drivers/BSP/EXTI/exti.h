#ifndef __EXTI_H_
#define __EXTI_H_
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"


/* 引脚 和 中断编号 & 中断服务函数 定义 注：KEY0=K_LEFT  KEY1=K_RIGHT WKUP=K_UP*/
#define KEY0_INT_GPIO_PORT              GPIOE
#define KEY0_INT_GPIO_PIN               GPIO_PIN_2
#define KEY0_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define KEY0_INT_IRQn                   EXTI2_IRQn
#define KEY0_INT_IRQHandler             EXTI2_IRQHandler

#define KEY1_INT_GPIO_PORT              GPIOE
#define KEY1_INT_GPIO_PIN               GPIO_PIN_4
#define KEY1_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define KEY1_INT_IRQn                   EXTI4_IRQn
#define KEY1_INT_IRQHandler             EXTI4_IRQHandler

#define WKUP_INT_GPIO_PORT              GPIOA
#define WKUP_INT_GPIO_PIN               GPIO_PIN_0
#define WKUP_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */
#define WKUP_INT_IRQn                   EXTI0_IRQn
#define WKUP_INT_IRQHandler             EXTI0_IRQHandler



void extix_init(void);



#endif 

