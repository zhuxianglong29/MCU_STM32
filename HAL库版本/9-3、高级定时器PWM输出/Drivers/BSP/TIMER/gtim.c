/**
 ****************************************************************************************************
 * @file        gtim.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.3
 * @date        2020-04-20
 * @brief       ͨ�ö�ʱ�� ��������
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
 * V1.0 20211216
 * ��һ�η���
 * V1.1 20211216
 * ����gtim_timx_pwm_chy_init����
 * V1.2 20211216
 * 1,����gtim_timx_cap_chy_init����
 * V1.3 20211216
 * 1,֧���ⲿ�����������
 * 2,����gtim_timx_cnt_chy_init,gtim_timx_cnt_chy_get_count��gtim_timx_cnt_chy_restart��������  
 *
 ****************************************************************************************************
 */

#include "./BSP/TIMER/gtim.h"
#include "./BSP/LED/led.h"


TIM_HandleTypeDef g_timx_handle; /* ��ʱ��x��� */

/**
 * @brief       ͨ�ö�ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtim_timx_int_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();                                 /* ʹ��TIMxʱ�� */

    g_timx_handle.Instance = GTIM_TIMX_INT;                     /* ͨ�ö�ʱ��x */
    g_timx_handle.Init.Prescaler = psc;                         /* Ԥ��Ƶϵ�� */
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* ��������ģʽ */
    g_timx_handle.Init.Period = arr;                            /* �Զ�װ��ֵ */
    HAL_TIM_Base_Init(&g_timx_handle);

    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);             /* �����ж����ȼ�����ռ���ȼ�1�������ȼ�3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);                     /* ����ITMx�ж� */

    HAL_TIM_Base_Start_IT(&g_timx_handle);                      /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
}

/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_INT_IRQHandler(void)
{
    /* ���´���û��ʹ�ö�ʱ��HAL�⹲�ô���������������ֱ��ͨ���ж��жϱ�־λ�ķ�ʽ */
    if(__HAL_TIM_GET_FLAG(&g_timx_handle, TIM_FLAG_UPDATE) != RESET)
    {
        LED1_TOGGLE();
        __HAL_TIM_CLEAR_IT(&g_timx_handle, TIM_IT_UPDATE);  /* �����ʱ������жϱ�־λ */
    }
}


/*********************************������ͨ�ö�ʱ��PWM���ʵ�����*************************************/

TIM_HandleTypeDef g_timx_pwm_chy_handle;     /* ��ʱ��x��� */

/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y PWM��� ��ʼ��������ʹ��PWMģʽ1��
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwm_chy  = {0};                          /* ��ʱ��PWM������� */

    g_timx_pwm_chy_handle.Instance = GTIM_TIMX_PWM;                     /* ��ʱ��x */
    g_timx_pwm_chy_handle.Init.Prescaler = psc;                         /* ��ʱ����Ƶ */
    g_timx_pwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* ��������ģʽ */
    g_timx_pwm_chy_handle.Init.Period = arr;                            /* �Զ���װ��ֵ */
    HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);                           /* ��ʼ��PWM */

    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                           /* ģʽѡ��PWM1 */
    timx_oc_pwm_chy.Pulse = arr / 2;                                    /* ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ� */
                                                                        /* Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50% */
    timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_LOW;                    /* ����Ƚϼ���Ϊ�� */
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle, &timx_oc_pwm_chy, GTIM_TIMX_PWM_CHY); /* ����TIMxͨ��y */
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle, GTIM_TIMX_PWM_CHY);       /* ������ӦPWMͨ�� */
}

/**
 * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
                �˺����ᱻHAL_TIM_PWM_Init()����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_PWM)
    {
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE();               /* ����ͨ��y��CPIOʱ�� */
        GTIM_TIMX_PWM_CHY_CLK_ENABLE();

        gpio_init_struct.Pin = GTIM_TIMX_PWM_CHY_GPIO_PIN; /* ͨ��y��CPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;           /* ����������� */
        gpio_init_struct.Pull = GPIO_PULLUP;               /* ���� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;     /* ���� */
        HAL_GPIO_Init(GTIM_TIMX_PWM_CHY_GPIO_PORT, &gpio_init_struct);
        GTIM_TIMX_PWM_CHY_GPIO_REMAP();                    /* IO��REMAP����, �Ƿ��Ҫ�鿴ͷ�ļ����õ�˵�� */
    }
}


/*********************************ͨ�ö�ʱ�����벶��ʵ�����*************************************/

TIM_HandleTypeDef g_timx_cap_chy_handle;      /* ��ʱ��x��� */

/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y ���벶�� ��ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtim_timx_cap_chy_init(uint16_t arr, uint16_t psc)
{
    TIM_IC_InitTypeDef timx_ic_cap_chy = {0};

    g_timx_cap_chy_handle.Instance = GTIM_TIMX_CAP;                     /* ��ʱ��5 */
    g_timx_cap_chy_handle.Init.Prescaler = psc;                         /* ��ʱ����Ƶ */
    g_timx_cap_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* ��������ģʽ */
    g_timx_cap_chy_handle.Init.Period = arr;                            /* �Զ���װ��ֵ */
    HAL_TIM_IC_Init(&g_timx_cap_chy_handle);

    timx_ic_cap_chy.ICPolarity = TIM_ICPOLARITY_RISING;                 /* �����ز��� */
    timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;             /* ӳ�䵽TI1�� */
    timx_ic_cap_chy.ICPrescaler = TIM_ICPSC_DIV1;                       /* ���������Ƶ������Ƶ */
    timx_ic_cap_chy.ICFilter = 0;                                       /* ���������˲��������˲� */
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle, &timx_ic_cap_chy, GTIM_TIMX_CAP_CHY);  /* ����TIM5ͨ��1 */

    __HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle, TIM_IT_UPDATE);         /* ʹ�ܸ����ж� */
    HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);     /* ��ʼ����TIM5��ͨ��1 */
}

/**
 * @brief       ͨ�ö�ʱ�����벶���ʼ���ӿ�
                HAL����õĽӿڣ��������ò�ͬ�����벶��
 * @param       htim:��ʱ�����
 * @note        �˺����ᱻHAL_TIM_IC_Init()����
 * @retval      ��
 */
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_CAP)                    /*����ͨ������*/
    {
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIMX_CAP_CHY_CLK_ENABLE();                     /* ʹ��TIMxʱ�� */
        GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE();                /* ��������IO��ʱ�� */

        gpio_init_struct.Pin = GTIM_TIMX_CAP_CHY_GPIO_PIN;  /* ���벶���GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* ����������� */
        gpio_init_struct.Pull = GPIO_PULLDOWN;              /* ���� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* ���� */
        HAL_GPIO_Init(GTIM_TIMX_CAP_CHY_GPIO_PORT, &gpio_init_struct);

        HAL_NVIC_SetPriority(GTIM_TIMX_CAP_IRQn, 1, 3);     /* ��ռ1�������ȼ�3 */
        HAL_NVIC_EnableIRQ(GTIM_TIMX_CAP_IRQn);             /* ����ITMx�ж� */
    }
}

/* ���벶��״̬(g_timxchy_cap_sta)
 * [7]  :0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
 * [6]  :0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
 * [5:0]:����ߵ�ƽ������Ĵ���,������63��,���������ֵ = 63*65536 + 65535 = 4194303
 *       ע��:Ϊ��ͨ��,����Ĭ��ARR��CCRy����16λ�Ĵ���,����32λ�Ķ�ʱ��(��:TIM5),Ҳֻ��16λʹ��
 *       ��1us�ļ���Ƶ��,����ʱ��Ϊ:4194303 us, Լ4.19��
 *
 *      (˵��һ�£�����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
 */
uint8_t g_timxchy_cap_sta = 0;    /* ���벶��״̬ */
uint16_t g_timxchy_cap_val = 0;   /* ���벶��ֵ */


/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_CAP_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);  /* ��ʱ��HAL�⹲�ô����� */
}

/**
 * @brief       ��ʱ�����벶���жϴ���ص�����
 * @param       htim:��ʱ�����ָ��
 * @note        �ú�����HAL_TIM_IRQHandler�лᱻ����
 * @retval      ��
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_CAP)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)                /* ��δ�ɹ����� */
        {
            if (g_timxchy_cap_sta & 0X40)                   /* ����һ���½��� */
            {
                g_timxchy_cap_sta |= 0X80;                  /* ��ǳɹ�����һ�θߵ�ƽ���� */
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);  /* ��ȡ��ǰ�Ĳ���ֵ */
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);                      /* һ��Ҫ�����ԭ�������� */
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_RISING); /* ����TIM5ͨ��1�����ز��� */
            }
            else /* ��δ��ʼ,��һ�β��������� */
            {
                g_timxchy_cap_sta = 0;                              /* ��� */
                g_timxchy_cap_val = 0;
                g_timxchy_cap_sta |= 0X40;                          /* ��ǲ����������� */
                __HAL_TIM_DISABLE(&g_timx_cap_chy_handle);          /* �رն�ʱ��5 */
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle, 0);   /* ��ʱ��5���������� */
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);   /* һ��Ҫ�����ԭ�������ã��� */
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_FALLING); /* ��ʱ��5ͨ��1����Ϊ�½��ز��� */
                __HAL_TIM_ENABLE(&g_timx_cap_chy_handle);           /* ʹ�ܶ�ʱ��5 */
            }
        }
    }
}

/**
 * @brief       ��ʱ�������жϻص�����
 * @param        htim:��ʱ�����ָ��
 * @note        �˺����ᱻ��ʱ���жϺ�����ͬ���õ�
 * @retval      ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_CAP)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)            /* ��δ�ɹ����� */
        {
            if (g_timxchy_cap_sta & 0X40)               /* �Ѿ����񵽸ߵ�ƽ�� */
            {
                if ((g_timxchy_cap_sta & 0X3F) == 0X3F) /* �ߵ�ƽ̫���� */
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);                     /* һ��Ҫ�����ԭ�������� */
                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_RISING);/* ����TIM5ͨ��1�����ز��� */
                    g_timxchy_cap_sta |= 0X80;          /* ��ǳɹ�������һ�� */
                    g_timxchy_cap_val = 0XFFFF;
                }
                else      /* �ۼƶ�ʱ��������� */
                {
                    g_timxchy_cap_sta++;
                }
            }
        }
    }
}


/*********************************ͨ�ö�ʱ���������ʵ�����*************************************/

TIM_HandleTypeDef g_timx_cnt_chy_handle;        /* ��ʱ��x��� */

/* ��¼��ʱ�����������������, ���������������� */
uint32_t g_timxchy_cnt_ofcnt = 0 ;              /* ����������� */

/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y ������� ��ʼ������
 * @note
 *              ������ѡ��ͨ�ö�ʱ����ʱ��ѡ��: �ⲿʱ��Դģʽ1(SMS[2:0] = 111)
 *              ����CNT�ļ���ʱ��Դ������ TIMX_CH1/CH2, ����ʵ���ⲿ�������(�������CH1/CH2)
 *
 *              ʱ�ӷ�Ƶ�� = psc, һ������Ϊ0, ��ʾÿһ��ʱ�Ӷ������һ��, ����߾���.
 *              ͨ����ȡCNT���������, �����򵥼���, ���Եõ���ǰ�ļ���ֵ, �Ӷ�ʵ���������
 *
 * @param       arr: �Զ���װֵ 
 * @retval      ��
 */
void gtim_timx_cnt_chy_init(uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct;
    TIM_SlaveConfigTypeDef tim_slave_config = {0};
    GTIM_TIMX_CNT_CHY_CLK_ENABLE();                                          /* ʹ��TIMxʱ�� */
    GTIM_TIMX_CNT_CHY_GPIO_CLK_ENABLE();                                     /* ����GPIOAʱ�� */
    
    g_timx_cnt_chy_handle.Instance = GTIM_TIMX_CNT;                          /* ��ʱ��x */
    g_timx_cnt_chy_handle.Init.Prescaler = psc;                              /* ��ʱ����Ƶ */
    g_timx_cnt_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;             /* ��������ģʽ */
    g_timx_cnt_chy_handle.Init.Period = 65535;                               /* �Զ���װ��ֵ */
    HAL_TIM_IC_Init(&g_timx_cnt_chy_handle);

    gpio_init_struct.Pin = GTIM_TIMX_CNT_CHY_GPIO_PIN;                       /* ���벶���GPIO�� */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                                   /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
    HAL_GPIO_Init(GTIM_TIMX_CNT_CHY_GPIO_PORT, &gpio_init_struct);

    /* ��ģʽ���ⲿ����ģʽ1 */
    tim_slave_config.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;                    /* ��ģʽ���ⲿ����ģʽ1 */
    tim_slave_config.InputTrigger = TIM_TS_TI1FP1;                           /* ���봥����ѡ�� TI1FP1(TIMX_CH1) ��Ϊ����Դ */
    tim_slave_config.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;           /* �������ԣ������� */
    tim_slave_config.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;           /* ����Ԥ��Ƶ���� */
    tim_slave_config.TriggerFilter = 0x0;                                    /* �˲��������в���Ҫ�κ��˲� */
    HAL_TIM_SlaveConfigSynchro(&g_timx_cnt_chy_handle, &tim_slave_config);

    HAL_NVIC_SetPriority(GTIM_TIMX_CNT_IRQn, 1, 3);                          /* �����ж����ȼ�����ռ���ȼ�1�������ȼ�3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_CNT_IRQn);

    __HAL_TIM_ENABLE_IT(&g_timx_cnt_chy_handle, TIM_IT_UPDATE);              /* ʹ�ܸ����ж� */
    HAL_TIM_IC_Start(&g_timx_cnt_chy_handle, GTIM_TIMX_CNT_CHY);             /* ��ʼ����TIMx��ͨ��y */
}

/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y ��ȡ��ǰ����ֵ 
 * @param       ��
 * @retval      ��ǰ����ֵ
 */
uint32_t gtim_timx_cnt_chy_get_count(void)
{
    uint32_t count = 0;
    count = g_timxchy_cnt_ofcnt * 65536;                     /* �������������Ӧ�ļ���ֵ */
    count += __HAL_TIM_GET_COUNTER(&g_timx_cnt_chy_handle);  /* ���ϵ�ǰCNT��ֵ */
    return count;
}

/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y ����������
 * @param       ��
 * @retval      ��ǰ����ֵ
 */
void gtim_timx_cnt_chy_restart(void)
{
    __HAL_TIM_DISABLE(&g_timx_cnt_chy_handle);        /* �رն�ʱ��TIMX */
    g_timxchy_cnt_ofcnt = 0;                          /* �ۼ������� */
    __HAL_TIM_SET_COUNTER(&g_timx_cnt_chy_handle, 0); /* ���������� */
    __HAL_TIM_ENABLE(&g_timx_cnt_chy_handle);         /* ʹ�ܶ�ʱ��TIMX */
}

/**
 * @brief       ͨ�ö�ʱ��TIMX ������� �����жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_CNT_IRQHandler(void)
{
    /* ���´���û��ʹ�ö�ʱ��HAL�⹲�ô���������������ֱ��ͨ���ж��жϱ�־λ�ķ�ʽ */
    if(__HAL_TIM_GET_FLAG(&g_timx_cnt_chy_handle, TIM_FLAG_UPDATE) != RESET)
    {
        g_timxchy_cnt_ofcnt++;          /* �ۼ�������� */
    }

      __HAL_TIM_CLEAR_IT(&g_timx_cnt_chy_handle, TIM_IT_UPDATE);
}





