#include "./BSP/KEY/key.h"

/**
* @brief ������ʼ������
* @param ��
* @retval ��
*/
void key_init(void)
{
GPIO_InitTypeDef gpio_init_struct; /* GPIO ���ò����洢���� */
/* ʱ��ʹ�� */
K_UP_GPIO_CLK_ENABLE();
K_LEFT_GPIO_CLK_ENABLE();
K_DOWN_GPIO_CLK_ENABLE();
K_RIGHT_GPIO_CLK_ENABLE();
	
gpio_init_struct.Pin = K_UP_GPIO_PIN; /* KEY UP ���� */
gpio_init_struct.Mode = GPIO_MODE_INPUT; /* ���� */
gpio_init_struct.Pull = GPIO_PULLDOWN; /* ���� */
gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* ���� */
HAL_GPIO_Init(K_UP_GPIO_PORT, &gpio_init_struct); /* KEY UP ����ģʽ���� */
	
	gpio_init_struct.Pin = K_LEFT_GPIO_PIN; /* KEY LEFT���� */
gpio_init_struct.Mode = GPIO_MODE_INPUT; /* ���� */
gpio_init_struct.Pull = GPIO_PULLUP; /* ���� */
gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* ���� */	
HAL_GPIO_Init(K_LEFT_GPIO_PORT, &gpio_init_struct); 
	
gpio_init_struct.Pin = K_DOWN_GPIO_PIN; /* KEY��DOWN ���� */
gpio_init_struct.Mode = GPIO_MODE_INPUT; /* ���� */
gpio_init_struct.Pull = GPIO_PULLUP; /* ���� */
gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* ���� */
HAL_GPIO_Init(K_DOWN_GPIO_PORT, &gpio_init_struct); 

gpio_init_struct.Pin = K_RIGHT_GPIO_PIN; /* KEY RIGHT ���� */
gpio_init_struct.Mode = GPIO_MODE_INPUT; /* ���� */
gpio_init_struct.Pull = GPIO_PULLUP; /* ���� */
gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* ���� */
HAL_GPIO_Init(K_RIGHT_GPIO_PORT, &gpio_init_struct); 
}


/**
* @brief ����ɨ�躯��
* @note �ú�������Ӧ���ȼ�(ͬʱ���¶������): K_UP >K_DOWN > K_RIGHT!!
* @param mode:0 / 1, ���庬������:
* @arg 0, ��֧��������(���������²���ʱ, ֻ�е�һ�ε��û᷵�ؼ�ֵ,
* �����ɿ��Ժ�, �ٴΰ��²Ż᷵��������ֵ)
* @arg 1, ֧��������(���������²���ʱ, ÿ�ε��øú������᷵�ؼ�ֵ)
* @retval ��ֵ,��������:
* K_UP_PRES 1  
* K_LEFT_PRES 2  
* K_DOWN_PRES 3 
* K_RIGHT_PRES 4  
*/
uint8_t key_scan(uint8_t mode)
{
static uint8_t key_up = 1; /* �������ɿ���־ */
uint8_t keyval = 0;
	
if (mode) key_up = 1; /* ֧������ */
	
if (key_up && (K_UP == 1 || K_LEFT == 0 || K_DOWN == 0|| K_RIGHT == 0))
{ /* �����ɿ���־Ϊ 1, ��������һ������������ */
delay_ms(10); /* ȥ���� */
key_up = 0;
if (K_UP == 1) keyval = K_UP_PRES;
if (K_LEFT == 0) keyval = K_LEFT_PRES;
if ( K_DOWN == 0) keyval =K_DOWN_PRES;
if (K_RIGHT == 0) keyval = K_RIGHT_PRES;
}
else if (K_UP == 0 && K_LEFT == 1 && K_DOWN == 1&& K_RIGHT == 1)
{ /* û���κΰ�������, ��ǰ����ɿ� */
key_up = 1;
}
return keyval; /* ���ؼ�ֵ */
}
