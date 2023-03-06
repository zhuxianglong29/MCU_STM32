#include "stm32f10x.h"

 
/************************************************
 ALIENTEK 精英STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

void USART1_Init(void)
{
		GPIO_InitTypeDef GPIO_Initstruct;
		USART_InitTypeDef USART_Initstruct;
		NVIC_InitTypeDef NVIC_Initstruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode= GPIO_Mode_AF_PP;
	GPIO_Initstruct.GPIO_Speed= GPIO_Speed_10MHz;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	GPIO_Initstruct.GPIO_Mode= GPIO_Mode_IN_FLOATING;
	GPIO_Initstruct.GPIO_Speed= GPIO_Speed_10MHz;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	USART_Initstruct.USART_BaudRate=115200; //波特率
	USART_Initstruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_Initstruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;	//都使能，收发模式
	USART_Initstruct.USART_Parity=USART_Parity_No;
	USART_Initstruct.USART_StopBits=USART_StopBits_1;
	USART_Initstruct.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART1,&USART_Initstruct);
	
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_Initstruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstruct);
	
	
	
}

void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		res=USART_ReceiveData(USART1);
		USART_SendData(USART1,res);
		
	}

}

 int main(void)
 {	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 USART1_Init();
	 while(1);
	 
	
 }
