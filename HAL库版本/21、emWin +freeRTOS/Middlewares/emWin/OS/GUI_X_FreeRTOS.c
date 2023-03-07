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
File        : GUI_X_FreeRTOS.c
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "GUI.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static SemaphoreHandle_t osMutex;
static SemaphoreHandle_t osSemaphore;

static SemaphoreHandle_t KeySemaphore;
static int				 KeyPressed;
static char			     KeyIsInited;
/*

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*      Timing:
*                 GUI_GetTime()
*                 GUI_Delay(int)

  Some timing dependent routines require a GetTime
  and delay funtion. Default time unit (tick), normally is
  1 ms.
*/

int GUI_X_GetTime(void) { 
	return ((int)xTaskGetTickCount());
}

void GUI_X_Delay(int period) { 
	
	vTaskDelay(period);
}

/*********************************************************************
*
*       GUI_X_ExecIdle()
*
*/
void GUI_X_ExecIdle(void)
{
	GUI_X_Delay(1);
}

/*********************************************************************
*
*      Multitasking:
*
*                 GUI_X_InitOS()
*                 GUI_X_GetTaskId()
*                 GUI_X_Lock()
*                 GUI_X_Unlock()
*
* Note:
*   The following routines are required only if emWin is used in a
*   true multi task environment, which means you have more than one
*   thread using the emWin API.
*   In this case the
*                       #define GUI_OS 1
*  needs to be in GUIConf.h
*/
void GUI_X_InitOS(void)
{
	osMutex=xSemaphoreCreateMutex();		//创建互斥信号量
	vSemaphoreCreateBinary(osSemaphore);	//创建二值信号量
}

//等待信号量
void GUI_X_Lock(void)
{
	xSemaphoreTake(osMutex,portMAX_DELAY);	//请求信号量
}
//发送信号量
void GUI_X_Unlock(void)
{
	xSemaphoreGive(osMutex);				//释放信号量
}

//返回任务ID
U32 GUI_X_GetTaskId(void)
{
	return ((uint32_t)xTaskGetCurrentTaskHandle()); 	//获取任务ID
}

/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/
#define OS_SendString(s) GUI_USE_PARA(s)
void GUI_X_Log     (const char *s) { GUI_USE_PARA(s); }
void GUI_X_Warn    (const char *s) { GUI_USE_PARA(s); }
void GUI_X_ErrorOut(const char *s) { GUI_USE_PARA(s); }

/*********************************************************************
*
*      GUI_X_Init()
*
* Note:
*   This routine is called from GUI_Init() in any case whether there
*   is an RTOS or not. You can use it for additional initializations
*   needed.
*/
static void CheckInit(void)
{
	if(KeyIsInited == pdFALSE){
		KeyIsInited = pdTRUE;
		GUI_X_Init();
	}
}


void GUI_X_Init(void)
{
	vSemaphoreCreateBinary(KeySemaphore);	//创建二值信号量
}

int GUI_X_GetKey(void) 
{
	int r;
	
	r = KeyPressed;
	CheckInit();
	KeyPressed = 0;
	return (r);
	
}



int GUI_X_WaitKey(void)
{
	int r;
	
	CheckInit();
	if(KeyPressed == 0)
	{
		xSemaphoreTake(KeySemaphore,portMAX_DELAY);//请求信号量
	}
	r = KeyPressed;
	KeyPressed = 0;
	return (r);
}

void GUI_X_StoreKey(int k)
{
	KeyPressed = k;
	xSemaphoreGive(KeySemaphore);			 //释放信号量
}



/*************************** End of file ****************************/
