#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(void)
{
	delay_init();
	LED_init();
	
	while(1)
	{
		PCout(0)=1;
		PCout(4)=1;
		delay_ms(500);
		
		PCout(0)=0;
		PCout(4)=0;
		delay_ms(500);
	}
}

