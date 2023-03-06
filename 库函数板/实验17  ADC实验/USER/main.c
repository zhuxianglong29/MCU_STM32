#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "tftlcd.h"
#include "usart.h"	 
#include "adc.h"
 
/************************************************
 ALIENTEK��ӢSTM32������ʵ��17
 ADC ʵ��   
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

   
 int main(void)
 {	 
	 u8 i=0;
	u16 color=0;
  u16 adcx;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	TFTLCD_Init();		 	
 	Adc_Init();		  		//ADC��ʼ��

		FRONT_COLOR=BLACK;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"Elite STM32");	
	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"ADC TEST");	
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,16,"ATOM@ALIENTEK");
	
       
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		LCD_ShowxNum(10,80,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowxNum(10,120,adcx,1,16,0);//��ʾ��ѹֵ
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(26,120,temp,3,16,0X80);
		LED0=!LED0;
		delay_ms(250);	
	}
 }

