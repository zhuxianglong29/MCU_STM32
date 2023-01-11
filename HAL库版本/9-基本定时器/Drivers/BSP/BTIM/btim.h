#ifndef __BTIM_H_
#define __BTIM_H_
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"

/* ������ʱ�� ���� */
/* TIMX �ж϶���
* Ĭ������� TIM6/TIM7.
* ע��: ͨ���޸��� 4 ���궨��,����֧�� TIM1~TIM8 ����һ����ʱ��.
*/
#define BTIM_TIMX_INT TIM6
#define BTIM_TIMX_INT_IRQn TIM6_DAC_IRQn
#define BTIM_TIMX_INT_IRQHandler TIM6_DAC_IRQHandler
/* TIM6 ʱ��ʹ�� */
#define BTIM_TIMX_INT_CLK_ENABLE() do{ __HAL_RCC_TIM6_CLK_ENABLE(); }while(0)

void btim_timx_int_init(uint16_t arr, uint16_t psc);

#endif 
