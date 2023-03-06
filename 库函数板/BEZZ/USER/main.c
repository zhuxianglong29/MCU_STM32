#include "stm32f10x.h"
#include "buzz.h"
#include "delay.h"

int main(void)
{
	delay_init();
	buzz_init();
	
	while(1)
	{	
		BEEP=1;
		delay_ms(300);
	
		BEEP=0;
		delay_ms(300);
	}
}

