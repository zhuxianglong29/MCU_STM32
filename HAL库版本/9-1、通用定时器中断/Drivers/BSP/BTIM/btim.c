#include "./BSP/BTIM/btim.h"



TIM_HandleTypeDef g_timx_handle;  /* 定时器句柄 */

/**
* @brief 定时器更新中断回调函数
* @param htim:定时器句柄指针
* @retval 无
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
if (htim->Instance == BTIM_TIMX_INT)
	{
	LED1_TOGGLE();
	}
}



/**
* @brief 通用定时器 TIMX 定时中断初始化函数
* @note
* 基本定时器的时钟来自 APB1,当 PPRE1 ≥ 2 分频的时候
* 基本定时器的时钟为 APB1 时钟的 2 倍, 而 APB1 为 36M, 所以定时器时钟 = 72Mhz
* 定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
* Ft=定时器工作频率,单位:Mhz
*
* @param arr: 自动重装值。
* @param psc: 时钟预分频数
* @retval 无
*/
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
	BTIM_TIMX_INT_CLK_ENABLE();
	g_timx_handle.Instance = BTIM_TIMX_INT; /* 定时器 x */
	g_timx_handle.Init.Prescaler = psc; /* 预分频 */
	g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP; /* 递增计数器 */
	g_timx_handle.Init.Period = arr; /* 自动装载值 */
	HAL_TIM_Base_Init(&g_timx_handle);
		
	/* 设置中断优先级，抢占优先级 1，子优先级 3 */
	HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 1, 3);
	HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn); /* 开启 ITMx 中断 */
	HAL_TIM_Base_Start_IT(&g_timx_handle); /* 使能定时器 x 和定时器 x 更新中断 */
}




/**
* @brief 定时器中断服务函数
* @param 无
* @retval 无
*/
void BTIM_TIMX_INT_IRQHandler(void)
{
HAL_TIM_IRQHandler(&g_timx_handle);
}





/**
 * @brief       定时器中断服务函数（相当回调函数
 * @param       无
 * @retval      无
 */
//void GTIM_TIMX_INT_IRQHandler(void)
//{
//    /* 以下代码没有使用定时器HAL库共用处理函数来处理，而是直接通过判断中断标志位的方式 */
//    if(__HAL_TIM_GET_FLAG(&g_timx_handle, TIM_FLAG_UPDATE) != RESET)
//    {
//        LED1_TOGGLE();
//        __HAL_TIM_CLEAR_IT(&g_timx_handle, TIM_IT_UPDATE);  /* 清除定时器溢出中断标志位 */
//    }
//}



