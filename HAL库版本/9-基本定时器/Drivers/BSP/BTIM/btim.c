#include "./BSP/BTIM/btim.h"



TIM_HandleTypeDef g_timx_handle;  /* ��ʱ����� */


/**
* @brief ������ʱ�� TIMX ��ʱ�жϳ�ʼ������
* @note
* ������ʱ����ʱ������ APB1,�� PPRE1 �� 2 ��Ƶ��ʱ��
* ������ʱ����ʱ��Ϊ APB1 ʱ�ӵ� 2 ��, �� APB1 Ϊ 36M, ���Զ�ʱ��ʱ�� = 72Mhz
* ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
* Ft=��ʱ������Ƶ��,��λ:Mhz
*
* @param arr: �Զ���װֵ��
* @param psc: ʱ��Ԥ��Ƶ��
* @retval ��
*/
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
	g_timx_handle.Instance = BTIM_TIMX_INT; /* ��ʱ�� x */
	g_timx_handle.Init.Prescaler = psc; /* Ԥ��Ƶ */
	g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP; /* ���������� */
	g_timx_handle.Init.Period = arr; /* �Զ�װ��ֵ */
	HAL_TIM_Base_Init(&g_timx_handle);
		
	HAL_TIM_Base_Start_IT(&g_timx_handle); /* ʹ�ܶ�ʱ�� x �Ͷ�ʱ�� x �����ж� */
}


/**
* @brief ��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
�˺����ᱻ HAL_TIM_Base_Init()��������
* @param ��
* @retval ��
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
if (htim->Instance == BTIM_TIMX_INT)
	{
	BTIM_TIMX_INT_CLK_ENABLE(); /* ʹ�� TIMx ʱ�� */
	/* �����ж����ȼ�����ռ���ȼ� 1�������ȼ� 3 */
	HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 1, 3);
	HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn); /* ���� ITMx �ж� */
	}
}


/**
* @brief ��ʱ���жϷ�����
* @param ��
* @retval ��
*/
void BTIM_TIMX_INT_IRQHandler(void)
{
HAL_TIM_IRQHandler(&g_timx_handle);
}


/**
* @brief ��ʱ�������жϻص�����
* @param htim:��ʱ�����ָ��
* @retval ��
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
if (htim->Instance == BTIM_TIMX_INT)
	{
	LED1_TOGGLE();
	}
}
