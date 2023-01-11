#include "./BSP/EXTI/exti.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LED/led.h"


/**
 * @brief       KEY0 外部中断服务程序
 * @param       无
 * @retval      无
 */
void KEY0_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY0所在中断线 的中断标志位 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

/**
 * @brief       KEY1 外部中断服务程序
 * @param       无
 * @retval      无
 */
void KEY1_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY1_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY1所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}


/**
 * @brief       WK_UP 外部中断服务程序
 * @param       无
 * @retval      无
 */
void WKUP_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);        /* 调用中断处理公用函数 清除KEY_UP所在中断线 的中断标志位，中断下半部在HAL_GPIO_EXTI_Callback执行 */
    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);        /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

/**
 * @brief       中断服务程序中需要做的事情
                在HAL库中所有的外部中断服务函数都会调用此函数
 * @param       GPIO_Pin:中断引脚号
 * @retval      无
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);      /* 消抖 */
    switch(GPIO_Pin)
    {
        case KEY0_INT_GPIO_PIN:
            if (K_LEFT == 0)
            {
                LED0_TOGGLE();  /* LED0 状态取反 */ 
                LED1_TOGGLE();  /* LED1 状态取反 */ 
            }
            break;
        case KEY1_INT_GPIO_PIN:
            if (K_RIGHT == 0)
            {
                LED0_TOGGLE();  /* LED0 状态取反 */ 
                LED1_TOGGLE();  /* LED1 状态取反 */  
            }
            break;
        case WKUP_INT_GPIO_PIN:
            if (K_UP == 1)
            {
                LED0_TOGGLE();  /* LED0 状态取反 */ 
            }
            break;
    }
}

/**
 * @brief       外部中断初始化程序
 * @param       无
 * @retval      无
 */
void extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    K_LEFT_GPIO_CLK_ENABLE();                                  /* KEY0时钟使能 */
    K_RIGHT_GPIO_CLK_ENABLE();                                  /* KEY1时钟使能 */
    K_UP_GPIO_CLK_ENABLE();                                  /* WKUP时钟使能 */

    gpio_init_struct.Pin = KEY0_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* 下升沿触发 */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_INT_GPIO_PORT, &gpio_init_struct);    /* KEY0配置为下降沿触发中断 */

    gpio_init_struct.Pin = KEY1_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* 下升沿触发 */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &gpio_init_struct);    /* KEY1配置为下降沿触发中断 */
    
    gpio_init_struct.Pin = WKUP_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;             /* 上升沿触发 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(WKUP_INT_GPIO_PORT, &gpio_init_struct);        /* WKUP配置为下降沿触发中断 */

    HAL_NVIC_SetPriority(KEY0_INT_IRQn, 0, 2);               /* 抢占0，子优先级2 */
    HAL_NVIC_EnableIRQ(KEY0_INT_IRQn);                       /* 使能中断线4 */

    HAL_NVIC_SetPriority(KEY1_INT_IRQn, 1, 2);               /* 抢占1，子优先级2 */
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);                       /* 使能中断线3 */

    HAL_NVIC_SetPriority(WKUP_INT_IRQn, 2, 2);               /* 抢占2，子优先级2 */
    HAL_NVIC_EnableIRQ(WKUP_INT_IRQn);                       /* 使能中断线0 */
}


