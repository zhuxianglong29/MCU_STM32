/**
 ****************************************************************************************************
 * @file        emwin_demo.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-01-04
 * @brief       BMPͼƬ��ʾ ʵ��
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
 ****************************************************************************************************
 */

#include "emwin_demo.h"
#include "EmWinHZFont.h"
#include "GUI.h"
#include "./MALLOC/malloc.h"
#include "./FATFS/source/ff.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LCD/lcd.h"
#if SYS_SUPPORT_OS
#include "FreeRTOS.h"
#include "task.h"

#endif


static FIL BMPFile;
static char bmpBuffer[BMPPERLINESIZE];
/*******************************************************************
*
*       Static functions
*
********************************************************************
 */
/*********************************************************************
*
*       BmpGetData
*
* Function description
*   This routine is called by GUI_BMP_DrawEx(). The routine is responsible
*   for setting the data pointer to a valid data location with at least
*   one valid byte.
*
* Parameters:
*   p           - Pointer to application defined data.
*   NumBytesReq - Number of bytes requested.
*   ppData      - Pointer to data pointer. This pointer should be set to
*                 a valid location.
*   StartOfFile - If this flag is 1, the data pointer should be set to the
*                 beginning of the data stream.
*
* Return value:
*   Number of data bytes available.
 */
static int emiwn_bmp_get_data(void *p, const U8 **ppData, unsigned NumBytesReq, U32 Off)
{
    static int readaddress = 0;
    FIL *phFile;
    UINT NumBytesRead;

    phFile = (FIL *)p;
  
#if SYS_SUPPORT_OS
  
#endif
        
    if (NumBytesReq > sizeof(bmpBuffer))
    {
        NumBytesReq = sizeof(bmpBuffer);
    }


    if (Off == 1) readaddress = 0; /* �ƶ�ָ�뵽Ӧ�ö�ȡ��λ�� */
    else readaddress = Off;

#if SYS_SUPPORT_OS
      taskENTER_CRITICAL();           /* �����ٽ��� */
#endif
    f_lseek(phFile, readaddress);


    f_read(phFile, bmpBuffer, NumBytesReq, &NumBytesRead); /* ��ȡ���ݵ��������� */
#if SYS_SUPPORT_OS
		taskEXIT_CRITICAL();        //�˳������ٽ���
#endif
    *ppData = (U8 *)bmpBuffer;
    return NumBytesRead;            /* ���ض�ȡ�����ֽ��� */
}

/**
 * @brief       ��ָ��λ����ʾ���ص�RAM�е�JPEGͼƬ
                BMPFileName:ͼƬ��SD�����������洢�豸�е�·��(���ļ�ϵͳ֧�֣�)
 * @param       mode:��ʾģʽ
      @arg      0 ��ָ��λ����ʾ���в���x,yȷ����ʾλ��
      @arg      1 ��LCD�м���ʾͼƬ����ѡ���ģʽ��ʱ�����x,y��Ч��
 * @param       X:ͼƬ���Ͻ���LCD�е�x��λ��(������modeΪ1ʱ���˲�����Ч)
 * @param       y:ͼƬ���Ͻ���LCD�е�y��λ��(������modeΪ1ʱ���˲�����Ч)
 * @param       member:  ���ű����ķ�����
 * @param       denom:���ű����ķ�ĸ��
 * @retval      0 ��ʾ����,���� ʧ��
  */
int emwin_dispbmp(uint8_t *BMPFileName, uint8_t mode, uint32_t x, uint32_t y, int member, int denom)
{
    uint16_t bread;
    char *bmpbuffer;
    char result;
    volatile int XSize, YSize;
    volatile float Xflag, Yflag;
    GUI_COLOR forecolor, bkcolor;
  
#if SYS_SUPPORT_OS
    
#endif

    forecolor = GUI_GetColor();  /* ��ȡ��ǰǰ��ɫ */
    bkcolor = GUI_GetBkColor();  /* ��ȡ��ǰ����ɫ */
    result = f_open(&BMPFile, (const TCHAR *)BMPFileName, FA_READ); /* ���ļ� */

    /* �ļ��򿪴�������ļ�����BMPMEMORYSIZE */
    if ((result != FR_OK) || (BMPFile.obj.objsize > BMPMEMORYSIZE)) return 1;

    bmpbuffer = mymalloc(SRAMIN, BMPFile.obj.objsize); /* �����ڴ� */

    if (bmpbuffer == NULL) 
    {
        printf("�����ڴ�ʧ��\r\n");
        return 2;
    }

#if SYS_SUPPORT_OS
    
#endif

    result = f_read(&BMPFile, bmpbuffer, BMPFile.obj.objsize, (UINT *)&bread); /* ��ȡ���� */

    if (result != FR_OK) 
    {
        printf("��ȡʧ��\r\n");
        return 3;
    }

#if SYS_SUPPORT_OS
    taskEXIT_CRITICAL();        //�˳������ٽ���
#endif

    switch (mode)
    {
        case 0: /* ��ָ��λ����ʾͼƬ */
            if ((member == 1) && (denom == 1)) /* �������ţ�ֱ�ӻ��� */
            {
                GUI_BMP_Draw(bmpbuffer, x, y); /* ��ָ��λ����ʾBMPͼƬ */
            }
            else  /* ����ͼƬ��Ҫ���� */
            {
                GUI_BMP_DrawScaled(bmpbuffer, x, y, member, denom);
            }

            break;

        case 1: /* ��LCD�м���ʾͼƬ */
            XSize = GUI_BMP_GetXSize(bmpbuffer); /* ��ȡͼƬ��X���С */
            YSize = GUI_BMP_GetYSize(bmpbuffer); /* ��ȡͼƬ��Y���С */

            if ((member == 1) && (denom == 1)) /* �������ţ�ֱ�ӻ��� */
            {
                /* ��LCD�м���ʾͼƬ */
                GUI_BMP_Draw(bmpbuffer, (lcddev.width - XSize) / 2 - 1, (lcddev.height - YSize) / 2 - 1);
            }
            else  /* ����ͼƬ��Ҫ���� */
            {
                Xflag = (float)XSize * ((float)member / (float)denom);
                Yflag = (float)YSize * ((float)member / (float)denom);
                XSize = (lcddev.width - (int)Xflag) / 2 - 1;
                YSize = (lcddev.height - (int)Yflag) / 2 - 1;
                GUI_BMP_DrawScaled(bmpbuffer, XSize, YSize, member, denom);
            }

            break;
    }

    f_close(&BMPFile);          /* �ر�BMPFile�ļ� */
    myfree(SRAMIN, bmpbuffer);  /* �ͷ��ڴ� */
    GUI_SetColor(forecolor);    /* �ָ�ǰ��ɫ */
    GUI_SetBkColor(bkcolor);    /* �ָ�����ɫ */
    return 0;
}

/**
 * @brief       ��ָ��λ����ʾ������ص�RAM�е�BMPͼƬ(���ļ�ϵͳ֧�֣�����СRAM���Ƽ�ʹ�ô˷�����)
                BMPFileName:ͼƬ��SD�����������洢�豸�е�·��
 * @param       mode:��ʾģʽ
      @arg      0 ��ָ��λ����ʾ���в���x,yȷ����ʾλ��
      @arg      1 ��LCD�м���ʾͼƬ����ѡ���ģʽ��ʱ�����x,y��Ч��
 * @param       X:ͼƬ���Ͻ���LCD�е�x��λ��(������modeΪ1ʱ���˲�����Ч)
 * @param       y:ͼƬ���Ͻ���LCD�е�y��λ��(������modeΪ1ʱ���˲�����Ч)
 * @param       member:  ���ű����ķ�����
 * @param       denom:���ű����ķ�ĸ��
 * @retval      0 ��ʾ����,���� ʧ��
  */
int emwin_dispbmpex(uint8_t *BMPFileName, uint8_t mode, uint32_t x, uint32_t y, int member, int denom)
{
    char result;
    volatile int XSize, YSize;
    volatile float Xflag, Yflag;
    GUI_COLOR forecolor, bkcolor;
    forecolor = GUI_GetColor();  /* ��ȡ��ǰǰ��ɫ */
    bkcolor = GUI_GetBkColor();  /* ��ȡ��ǰ����ɫ */

    result = f_open(&BMPFile, (const TCHAR *)BMPFileName, FA_READ);	/* ���ļ� */

    /* �ļ��򿪴��� */
    if (result != FR_OK)    return 1;

    switch (mode)
    {
        case 0: /* ��ָ��λ����ʾͼƬ */
            if ((member == 1) && (denom == 1)) /* �������ţ�ֱ�ӻ��� */
            {
                GUI_BMP_DrawEx(emiwn_bmp_get_data, &BMPFile, x, y); /* ��ָ��λ����ʾBMPͼƬ */
            }
            else  /* ����ͼƬ��Ҫ���� */
            {
                GUI_BMP_DrawScaledEx(emiwn_bmp_get_data, &BMPFile, x, y, member, denom);
            }

            break;

        case 1:  /* ��LCD�м���ʾͼƬ */
            XSize = GUI_BMP_GetXSizeEx(emiwn_bmp_get_data, &BMPFile);   /* ��ȡͼƬ��X���С */
            YSize = GUI_BMP_GetYSizeEx(emiwn_bmp_get_data, &BMPFile);   /* ��ȡͼƬ��Y���С */

            if ((member == 1) && (denom == 1)) /* �������ţ�ֱ�ӻ��� */
            {
                /* ��LCD�м���ʾͼƬ */
                GUI_BMP_DrawEx(emiwn_bmp_get_data, &BMPFile, (lcddev.width - XSize) / 2 - 1, (lcddev.height - YSize) / 2 - 1);
            }
            else  /* ����ͼƬ��Ҫ���� */
            {
                Xflag = (float)XSize * ((float)member / (float)denom);
                Yflag = (float)YSize * ((float)member / (float)denom);
                XSize = (lcddev.width - (int)Xflag) / 2 - 1;
                YSize = (lcddev.height - (int)Yflag) / 2 - 1;
                GUI_BMP_DrawScaledEx(emiwn_bmp_get_data, &BMPFile, XSize, YSize, member, denom);
            }

            break;
    }

    f_close(&BMPFile);        /* �ر�BMPFile�ļ� */
    GUI_SetColor(forecolor);  /* �ָ�ǰ��ɫ */
    GUI_SetBkColor(bkcolor);  /* �ָ�����ɫ */
    return 0;
}

/**
 * @brief       �˺�����GUI_BMP_Serialize()���ã��������ļ�д���ֽ�
 * @param       ��
 * @retval      ��
  */
static void _WriteByte2File(U8 Data, void *p)
{
    UINT nWritten;
    f_write((FIL *)p, &Data, 1, &nWritten);
}

/**
 * @brief       ����һ��BMPͼƬ�����浽SD����,ʵ����Ļ��ͼ���ܣ�
 * @param       x0:����BMP�ļ���X��ʼλ��
 * @param       y0:����BMP�ļ���Y��ʼλ��
 * @param       Xsize:X�Ĵ�С
 * @param       Ysize:Y�Ĵ�С
 * @retval      ��
 */
void emwin_create_bmppicture(uint8_t *filename, int x0, int y0, int Xsize, int Ysize)
{
    static FIL hFile;
   
    GUI_COLOR forecolor, bkcolor;
    forecolor = GUI_GetColor();   /* ��ȡ��ǰǰ��ɫ */
    bkcolor = GUI_GetBkColor();   /* ��ȡ��ǰ����ɫ */
    /* ����һ���ļ���·��Ϊfilename,����ļ�ԭ���ʹ��ڵĻ��ᱻ�½����ļ����ǵ��� */
    f_open(&hFile, (const TCHAR *)filename, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
    GUI_BMP_SerializeEx(_WriteByte2File, x0, y0, Xsize, Ysize, &hFile);
    f_close(&hFile);           /* �ر��ļ� */
    GUI_SetColor(forecolor);   /* �ָ�ǰ��ɫ */
    GUI_SetBkColor(bkcolor);   /* �ָ�����ɫ */
}

/**
 * @brief       emwin_main(emwin���)
 * @param       ��
 * @return      ��
 */
void emwin_main(void) 
{
    GUI_SetBkColor(GUI_BLUE);
    GUI_SetColor(GUI_RED);
    GUI_SetFont(&GUI_FontHZ16);
    GUI_Clear();

    while (1)
    {
        GUI_DispStringHCenterAt("������ص�BMPͼƬ", 100, 5);
        emwin_dispbmpex((uint8_t *)"0:/PICTURE/BMP/ԭ�Ӹ繫�ںŶ�ά��.bmp", 0, 10, 78, 1, 1);
        GUI_Delay(1000);
        GUI_Clear();


        GUI_DispStringHCenterAt("��С1/2��������ص�BMPͼƬ", 100, 5);
        emwin_dispbmpex((uint8_t *)"0:/PICTURE/BMP/ԭ�Ӹ繫�ںŶ�ά��.bmp", 1, 0, 0, 1, 2);
        GUI_Delay(1000);
        GUI_Clear();

        GUI_DispStringHCenterAt("����4/3��BMPͼƬ", 100, 5);
        emwin_dispbmpex((uint8_t *)"0:/PICTURE/BMP/ԭ�Ӹ繫�ںŶ�ά��.bmp", 1, 0, 0, 4, 3);
        GUI_Delay(1000);
        GUI_Clear();
    }
}
