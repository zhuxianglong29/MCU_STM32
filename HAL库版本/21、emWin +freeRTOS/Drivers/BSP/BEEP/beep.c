#include "./BSP/BEEP/beep.h"
uint32_t ms_num;

/**
* @brief ��ʼ�� BEEP ��� IO ��, ��ʹ��ʱ��
* @param ��
* @retval ��
*/
void beep_init(void)
{
		GPIO_InitTypeDef beep_gpio_struct;
		beep_gpio_struct.Mode=GPIO_MODE_OUTPUT_PP;
		beep_gpio_struct.Pin=BEEP_GPIO_PIN;
		beep_gpio_struct.Pull=GPIO_NOPULL;
		beep_gpio_struct.Speed=GPIO_SPEED_FREQ_HIGH;
		BEEP_GPIO_CLK_ENABLE();
		HAL_GPIO_Init(BEEP_GPIO_PORT,&beep_gpio_struct);
	
}


/**
* @brief BEEP���庯��
* @param ����ʱ��Ϊ����ʱ��
* @retval ��
*/
void beep_buz(uint32_t ms)
{
	ms_num=ms*1000;
	while(ms>0)
	{
		BEEP(0);
		delay_us(100);
		BEEP(1);
		delay_us(100);
		ms_num-=200;
		if(ms_num<=0)
			break;
	}
	
}

