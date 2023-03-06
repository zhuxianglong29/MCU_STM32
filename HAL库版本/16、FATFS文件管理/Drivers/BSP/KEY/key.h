#ifndef __KEY_H_
#define __KEY_H_
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

/* PA0 定义 */
#define K_UP_GPIO_PORT GPIOA
#define K_UP_GPIO_PIN GPIO_PIN_0
#define K_UP_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

/* PE2 口时钟使能 */
#define K_LEFT_GPIO_PORT GPIOE
#define K_LEFT_GPIO_PIN GPIO_PIN_2
#define K_LEFT_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

/* PE3 口时钟使能 */
#define K_DOWN_GPIO_PORT GPIOE
#define K_DOWN_GPIO_PIN GPIO_PIN_3
#define K_DOWN_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

/* PE4 口时钟使能 */
#define K_RIGHT_GPIO_PORT GPIOE
#define K_RIGHT_GPIO_PIN GPIO_PIN_4
#define K_RIGHT_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)


#define K_UP HAL_GPIO_ReadPin( K_UP_GPIO_PORT, K_UP_GPIO_PIN) /* 读取 K_UP 引脚 */
#define K_LEFT HAL_GPIO_ReadPin(K_LEFT_GPIO_PORT, K_LEFT_GPIO_PIN) 
#define K_DOWN HAL_GPIO_ReadPin(K_DOWN_GPIO_PORT, K_DOWN_GPIO_PIN) 
#define K_RIGHT HAL_GPIO_ReadPin(K_RIGHT_GPIO_PORT, K_RIGHT_GPIO_PIN) 

#define K_UP_PRES 1 /* KEY_UP 按下 */
#define K_LEFT_PRES 2 //key0
#define K_DOWN_PRES 3 
#define K_RIGHT_PRES 4 //key1

void key_init(void);
uint8_t key_scan(uint8_t mode);

#endif 
