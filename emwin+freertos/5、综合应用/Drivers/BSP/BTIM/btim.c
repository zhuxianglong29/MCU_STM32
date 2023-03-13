#include "./BSP/BTIM/btim.h"
#include "GUI.h"



TIM_HandleTypeDef timx_handler; /*定时器参数句柄*/
uint8_t count=0;
//extern __IO int32_t OS_TimeMS;os的节拍定义在delay中这里不用

/**
 * @brief       基本定时器TIMX中断服务函数
 * @param       无
 * @retval      无
 */


/**
 * @brief       基本定时器TIMX定时中断初始化函数
 * @note
 *              基本定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              基本定时器的时钟为APB1时钟的2倍, 而APB1为36M, 所以定时器时钟 = 72Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
    timx_handler.Instance = BTIM_TIMX_INT;                      /*通用定时器X*/
    timx_handler.Init.Prescaler = psc;                          /* 设置预分频器  */
    timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;         /* 向上计数器 */
    timx_handler.Init.Period = arr;                             /*自动装载值*/
    timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;   /*时钟分频因子*/
    HAL_TIM_Base_Init(&timx_handler);

    HAL_TIM_Base_Start_IT(&timx_handler);                       /*使能通用定时器x和及其更新中断：TIM_IT_UPDATE*/
}

/**
 * @brief       定时器底册驱动，开启时钟，设置中断优先级
                此函数会被HAL_TIM_Base_Init()函数调用
 * @param       无
 * @retval      无
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
        BTIM_TIMX_INT_CLK_ENABLE();                     /*使能TIM时钟*/
        HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 1, 3); /* 抢占1，子优先级3，组2 */
        HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn);         /*开启ITM3中断*/
    }
}

