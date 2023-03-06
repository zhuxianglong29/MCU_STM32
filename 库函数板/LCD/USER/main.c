

#include "sys.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "tftlcd.h"
#include "picture.h"


/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	u8 i=0;
	u16 color=0;
	
	delay_init();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	LED_init();
	uart_init(9600);
	TFTLCD_Init();			//LCD��ʼ��
	
	FRONT_COLOR=BLACK;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,12,"Hello World!");
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Hello World!");
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Hello World!");
	LCD_ShowFontHZ(10, 80,"���пƼ�");
	LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,24,"www.prechin.cn");
	
	LCD_Fill(10,150,60,180,BLUE);
	color=LCD_ReadPoint(20,160);
	LCD_Fill(100,150,150,180,color);
	printf("color=%x\r\n",color);
	
	LCD_ShowPicture(20,220,200,112,(u8 *)gImage_picture);
	while(1);
	


	
}
