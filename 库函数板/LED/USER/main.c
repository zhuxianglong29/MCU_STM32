#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(void)
{
	delay_init();
	LED_init();
	while(1)
	{
	
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
	
		delay_ms(500);
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		
		
		delay_ms(500);
	}


}
