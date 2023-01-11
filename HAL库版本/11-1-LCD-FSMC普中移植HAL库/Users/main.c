#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"

int main(void)
{
	u8 i=0;
	u16 color=0;
   
    

    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* 设置时钟,72M */
    delay_init(72);                             /* 初始化延时函数 */
    usart_init(115200);
    led_init();                                 /* 初始化LED */
    TFTLCD_Init();			//LCD初始化
	
	FRONT_COLOR=BLACK;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,12,"Hello World!");
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Hello World!");
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Hello World!");
	LCD_ShowFontHZ(10, 80,"普中科技");
	LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,24,"www.prechin.cn");
	
	LCD_Fill(10,150,60,180,BLUE);
	color=LCD_ReadPoint(20,160);
	LCD_Fill(100,150,150,180,color);
	printf("color=%x\r\n",color);
	
	//LCD_ShowPicture(20,220,200,112,(u8 *)gImage_picture);

	while(1)
	{
		i++;
		if(i%20==0)
		{
			 LED0_TOGGLE();
		}
		
		delay_ms(10);
			
	}
}

