#ifndef __BEEP_H_
#define __BEEP_H_
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

/* ���� ���� */
#define BEEP_GPIO_PORT GPIOB
#define BEEP_GPIO_PIN GPIO_PIN_5
/* PB ��ʱ��ʹ�� */
#define BEEP_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)


/* BEEP �˿ڶ���,ͨ�����Ϸ�תʵ����Դ���������� */
#define BEEP(x) do{ x ? \
HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET) : \
HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_RESET);\
}while(0) /* ��ת */


void beep_init(void); 
void beep_buz(uint32_t nus);

#endif 
