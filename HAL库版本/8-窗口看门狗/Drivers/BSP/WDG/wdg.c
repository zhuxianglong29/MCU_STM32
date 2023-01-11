/**
 ****************************************************************************************************
 * @file        wwdg.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-22
 * @brief       ���ڿ��Ź� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211124
 * ��һ�η���
 * V1.1 20211124
 * ��Ӵ��ڿ��Ź���ش���
 *
 ****************************************************************************************************
 */

#include "./BSP/WDG/wdg.h"
#include "./BSP/LED/led.h"


IWDG_HandleTypeDef g_iwdg_handle;   /* �������Ź���� */

/**
 * @brief       ��ʼ���������Ź� 
 * @param       prer: IWDG_PRESCALER_4~IWDG_PRESCALER_256,��Ӧ4~256��Ƶ
 *   @arg       ��Ƶ���� = 4 * 2^prer. �����ֵֻ����256!
 * @param       rlr: �Զ���װ��ֵ,0~0XFFF. 
 * @note        ʱ�����(���):Tout=((4 * 2^prer) * rlr) / 40 (ms). 
 * @retval      ��
 */
void iwdg_init(uint8_t prer, uint16_t rlr)
{
    g_iwdg_handle.Instance = IWDG;
    g_iwdg_handle.Init.Prescaler = prer; /* ����IWDG��Ƶϵ�� */
    g_iwdg_handle.Init.Reload = rlr;     /* ��װ��ֵ */
    HAL_IWDG_Init(&g_iwdg_handle);       /* ��ʼ��IWDG������ */
}

/**
 * @brief       ι�������Ź�
 * @param       ��
 * @retval      ��
 */
void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&g_iwdg_handle);  /* ��װ�ؼ����� */
}


/************************�����Ǵ��ڿ��Ź�����********************************/


WWDG_HandleTypeDef g_wwdg_handle;  /* WWDG��� */

/**
 * @brief       ��ʼ�����ڿ��Ź�
 * @param       tr: T[6:0],������ֵ
 * @param       tw: W[6:0],����ֵ
 * @note        fprer:��Ƶϵ����WDGTB��,��Χ:WWDG_PRESCALER_1~WWDG_PRESCALER_8,��ʾ2^WDGTB��Ƶ
 *              Fwwdg=PCLK1/(4096*2^fprer). һ��PCLK1=36Mhz
                ���-��С��ʱʱ��ο� RM0008���ߡ�STM32F10xxx�ο��ֲᡷP321
 * @retval      ��
 */
void wwdg_init(uint8_t tr, uint8_t wr, uint32_t fprer)
{
    g_wwdg_handle.Instance = WWDG;
    g_wwdg_handle.Init.Prescaler = fprer;         /* ���÷�Ƶϵ�� */
    g_wwdg_handle.Init.Window = wr;               /* ���ô���ֵ */
    g_wwdg_handle.Init.Counter = tr;              /* ���ü�����ֵ */
    g_wwdg_handle.Init.EWIMode = WWDG_EWI_ENABLE; /* ʹ�ܴ��ڿ��Ź���ǰ�����ж� */
    HAL_WWDG_Init(&g_wwdg_handle);                /* ��ʼ��WWDG */
}

/**
 * @brief       WWDG MSP�ص�
 * @param       WWDG���
 * @note        �˺����ᱻHAL_WWDG_Init()����
 * @retval      ��
 */
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();            /* ʹ�ܴ��ڿ��Ź�ʱ�� */

    HAL_NVIC_SetPriority(WWDG_IRQn, 2, 3);  /* ��ռ���ȼ�2�������ȼ�Ϊ3 */
    HAL_NVIC_EnableIRQ(WWDG_IRQn);          /* ʹ�ܴ��ڿ��Ź��ж� */
}

/**
 * @brief       ���ڿ��Ź��жϷ������
 * @param       ��
 * @retval      ��
 */
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_wwdg_handle);  /* ����WWDG�����жϴ����� */
}

/**
 * @brief       ���ڿ��Ź�ι�������жϷ���ص�����
 * @param       wwdg���
 * @note        �˺����ᱻHAL_WWDG_IRQHandler()����
 * @retval      ��
 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    HAL_WWDG_Refresh(&g_wwdg_handle); /* ���´��ڿ��Ź�ֵ */
    LED1_TOGGLE();                    /* LED1��˸ */
}

