#include "./BSP/KEY/key.h"

/**
* @brief 按键初始化函数
* @param 无
* @retval 无
*/
void key_init(void)
{
GPIO_InitTypeDef gpio_init_struct; /* GPIO 配置参数存储变量 */
/* 时钟使能 */
K_UP_GPIO_CLK_ENABLE();
K_LEFT_GPIO_CLK_ENABLE();
K_DOWN_GPIO_CLK_ENABLE();
K_RIGHT_GPIO_CLK_ENABLE();
	
gpio_init_struct.Pin = K_UP_GPIO_PIN; /* KEY UP 引脚 */
gpio_init_struct.Mode = GPIO_MODE_INPUT; /* 输入 */
gpio_init_struct.Pull = GPIO_PULLDOWN; /* 下拉 */
gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
HAL_GPIO_Init(K_UP_GPIO_PORT, &gpio_init_struct); /* KEY UP 引脚模式设置 */
	
	gpio_init_struct.Pin = K_LEFT_GPIO_PIN; /* KEY LEFT引脚 */
gpio_init_struct.Mode = GPIO_MODE_INPUT; /* 输入 */
gpio_init_struct.Pull = GPIO_PULLUP; /* 上拉 */
gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */	
HAL_GPIO_Init(K_LEFT_GPIO_PORT, &gpio_init_struct); 
	
gpio_init_struct.Pin = K_DOWN_GPIO_PIN; /* KEY　DOWN 引脚 */
gpio_init_struct.Mode = GPIO_MODE_INPUT; /* 输入 */
gpio_init_struct.Pull = GPIO_PULLUP; /* 上拉 */
gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
HAL_GPIO_Init(K_DOWN_GPIO_PORT, &gpio_init_struct); 

gpio_init_struct.Pin = K_RIGHT_GPIO_PIN; /* KEY RIGHT 引脚 */
gpio_init_struct.Mode = GPIO_MODE_INPUT; /* 输入 */
gpio_init_struct.Pull = GPIO_PULLUP; /* 上拉 */
gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
HAL_GPIO_Init(K_RIGHT_GPIO_PORT, &gpio_init_struct); 
}


/**
* @brief 按键扫描函数
* @note 该函数有响应优先级(同时按下多个按键): K_UP >K_DOWN > K_RIGHT!!
* @param mode:0 / 1, 具体含义如下:
* @arg 0, 不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
* 必须松开以后, 再次按下才会返回其他键值)
* @arg 1, 支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
* @retval 键值,定义如下:
* K_UP_PRES 1  
* K_LEFT_PRES 2  
* K_DOWN_PRES 3 
* K_RIGHT_PRES 4  
*/
uint8_t key_scan(uint8_t mode)
{
static uint8_t key_up = 1; /* 按键按松开标志 */
uint8_t keyval = 0;
	
if (mode) key_up = 1; /* 支持连按 */
	
if (key_up && (K_UP == 1 || K_LEFT == 0 || K_DOWN == 0|| K_RIGHT == 0))
{ /* 按键松开标志为 1, 且有任意一个按键按下了 */
delay_ms(10); /* 去抖动 */
key_up = 0;
if (K_UP == 1) keyval = K_UP_PRES;
if (K_LEFT == 0) keyval = K_LEFT_PRES;
if ( K_DOWN == 0) keyval =K_DOWN_PRES;
if (K_RIGHT == 0) keyval = K_RIGHT_PRES;
}
else if (K_UP == 0 && K_LEFT == 1 && K_DOWN == 1&& K_RIGHT == 1)
{ /* 没有任何按键按下, 标记按键松开 */
key_up = 1;
}
return keyval; /* 返回键值 */
}
