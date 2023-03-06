#include "stm32f10x.h"

 
/************************************************
 ALIENTEK ��ӢSTM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
	
	USART_Initstruct.USART_BaudRate=115200; //������
	USART_Initstruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������������
	USART_Initstruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;	//��ʹ�ܣ��շ�ģʽ
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
