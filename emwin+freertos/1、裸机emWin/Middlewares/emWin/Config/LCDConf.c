/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2020  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V6.16 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Software GmbH
Licensed to:              ARM Ltd, 110 Fulbourn Road, CB1 9NJ Cambridge, UK
Licensed SEGGER software: emWin
License number:           GUI-00181
License model:            LES-SLA-20007, Agreement, effective since October 1st 2011 
Licensed product:         MDK-ARM Professional
Licensed platform:        ARM7/9, Cortex-M/R4
Licensed number of seats: -
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

#include "GUIDRV_Template.h"
#include "GUIDRV_FlexColor.h"
#include "./BSP/LCD/lcd.h"

//��ֹ����ӵ�
void GUI_X_InitOS(void)    {  }
void GUI_X_Unlock(void)    { }
void GUI_X_Lock(void)      {   }
U32  GUI_X_GetTaskId(void) {}
	
/* �봥�����йض��壬����ʵ�������д */
#define TOUCH_AD_TOP 160 /* ���´������Ķ�����д�� Y ��ģ������ֵ�� */
#define TOUCH_AD_BOTTOM 3990 /* ���´������ĵײ���д�� Y ��ģ������ֵ�� */
#define TOUCH_AD_LEFT 160 /* ���´���������࣬д�� X ��ģ������ֵ�� */
#define TOUCH_AD_RIGHT 3990 /* ���´��������Ҳ࣬д�� X ��ģ������ֵ�� */

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/
//
// Physical display size
//   The display size should be adapted in order to match the size of
//   the target display.
//
#define XSIZE_PHYS 480
#define YSIZE_PHYS 272

//
// Color conversion
//   The color conversion functions should be selected according to
//   the color mode of the target display. Detaileds can be found in
//   the chapter "Colors" in the emWin user manual.
//
#define COLOR_CONVERSION GUICC_8888

//
// Display driver
//   GUIDRV_WIN32 is for use only within the emWin Simulation
//   environment. In order to use the target display controller, the
//   according emWin display driver should be configured as it is
//   described in the chapter "Display Drivers" in the emWin user
//   manual. Beyond that sample configuration files can be found in
//   The folder "Sample\LCDConf\%DISPLAY_DRIVER%\".
//
#define DISPLAY_DRIVER GUIDRV_WIN32

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description
*   Called during the initialization process in order to set up the
*   display driver configuration.
*/
void LCD_X_Config(void) {
  /* ������ʾ�������� */
GUI_DEVICE_CreateAndLink(&GUIDRV_Template_API, GUICC_M565, 0, 0);
  LCD_SetSizeEx(0, lcddev.width, lcddev.height);
	LCD_SetVSizeEx(0, lcddev.width, lcddev.height);
	
	if (lcddev.dir == 0) /* ���� */
		{
		GUI_TOUCH_SetOrientation(GUI_MIRROR_X);
		GUI_TOUCH_Calibrate(GUI_COORD_X, 0, lcddev.width, 155, 3903);
		GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, lcddev.height, 188, 3935);
		}
		else /* ���� */
		{
		GUI_TOUCH_SetOrientation(GUI_SWAP_XY);
		GUI_TOUCH_Calibrate(GUI_COORD_X, 0, lcddev.width, 155, 3903);
		GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, lcddev.height, 188, 3935);
		}
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description
*   Display driver callback function. This function is called by the
*   Display driver for certain purposes. Using GUIDRV_Win32 it is not
*   required to react to any command.
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  GUI_USE_PARA(LayerIndex);
  GUI_USE_PARA(Cmd);
  GUI_USE_PARA(pData);
  return 0;
}

/*************************** End of file ****************************/
