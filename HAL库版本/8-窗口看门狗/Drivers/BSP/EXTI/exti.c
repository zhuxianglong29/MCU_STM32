#include "./BSP/EXTI/exti.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LED/led.h"


/**
 * @brief       KEY0 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void KEY0_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_INT_GPIO_PIN);         /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       KEY1 �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void KEY1_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY1_INT_GPIO_PIN);         /* �����жϴ����ú��� ���KEY1�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}


/**
 * @brief       WK_UP �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
 */
void WKUP_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);        /* �����жϴ����ú��� ���KEY_UP�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

/**
 * @brief       �жϷ����������Ҫ��������
                ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);      /* ���� */
    switch(GPIO_Pin)
    {
        case KEY0_INT_GPIO_PIN:
            if (K_LEFT == 0)
            {
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */ 
            }
            break;
        case KEY1_INT_GPIO_PIN:
            if (K_RIGHT == 0)
            {
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */  
            }
            break;
        case WKUP_INT_GPIO_PIN:
            if (K_UP == 1)
            {
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
            }
            break;
    }
}

/**
 * @brief       �ⲿ�жϳ�ʼ������
 * @param       ��
 * @retval      ��
 */
void extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    K_LEFT_GPIO_CLK_ENABLE();                                  /* KEY0ʱ��ʹ�� */
    K_RIGHT_GPIO_CLK_ENABLE();                                  /* KEY1ʱ��ʹ�� */
    K_UP_GPIO_CLK_ENABLE();                                  /* WKUPʱ��ʹ�� */

    gpio_init_struct.Pin = KEY0_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* �����ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_INT_GPIO_PORT, &gpio_init_struct);    /* KEY0����Ϊ�½��ش����ж� */

    gpio_init_struct.Pin = KEY1_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* �����ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &gpio_init_struct);    /* KEY1����Ϊ�½��ش����ж� */
    
    gpio_init_struct.Pin = WKUP_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;             /* �����ش��� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(WKUP_INT_GPIO_PORT, &gpio_init_struct);        /* WKUP����Ϊ�½��ش����ж� */

    HAL_NVIC_SetPriority(KEY0_INT_IRQn, 0, 2);               /* ��ռ0�������ȼ�2 */
    HAL_NVIC_EnableIRQ(KEY0_INT_IRQn);                       /* ʹ���ж���4 */

    HAL_NVIC_SetPriority(KEY1_INT_IRQn, 1, 2);               /* ��ռ1�������ȼ�2 */
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);                       /* ʹ���ж���3 */

    HAL_NVIC_SetPriority(WKUP_INT_IRQn, 2, 2);               /* ��ռ2�������ȼ�2 */
    HAL_NVIC_EnableIRQ(WKUP_INT_IRQn);                       /* ʹ���ж���0 */
}


