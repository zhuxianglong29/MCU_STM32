/**
 ****************************************************************************************************
 * @file        wwdg.h
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

#ifndef __WDG_H
#define __WDG_H

#include "./SYSTEM/sys/sys.h"


void iwdg_init(uint8_t prer, uint16_t rlr);
void iwdg_feed(void);

void wwdg_init(uint8_t tr, uint8_t wr, uint32_t fprer);

#endif




























