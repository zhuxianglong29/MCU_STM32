/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH                         *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 6.16                          *
*        Compiled Nov 13 2020, 12:50:00                              *
*        (c) 2019 Segger Microcontroller GmbH                        *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "emwin_demo.h"
#include "./FATFS/exfuns/fattester.h"
#include "./FATFS/exfuns/exfuns.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_0 (GUI_ID_USER + 0x02)
#define ID_BUTTON_1 (GUI_ID_USER + 0x03)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 240, 400, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Fatfs", ID_TEXT_0, 0, 0, 240, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "open", ID_BUTTON_0, 80, 100, 80, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "home", ID_BUTTON_1, 180, 360, 60, 40, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
extern GUI_CONST_STORAGE GUI_BITMAP bmCheckpic;
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Window'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_MAKE_COLOR(0x00A00000));
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
    TEXT_SetTextColor(hItem, GUI_MAKE_COLOR(0x00FFFFFF));
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'open'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
			 GUI_EndDialog(pMsg->hWin, 0);
			GUI_SetBkColor(GUI_WHITE);
			vTaskDelay(1000);
			GUI_Clear();
			taskENTER_CRITICAL();           /* 进入临界区 */	
			lcd_clear(WHITE);
			uint32_t total, free;
			while (exfuns_get_free((uint8_t*)"0", &total, &free)) /* 得到SD卡的总容量和剩余容量 */
    {
        lcd_show_string(30, 130, 200, 16, 16, "SD Card Fatfs Error!", RED);
        vTaskDelay(200);
        lcd_fill(30, 130, 240, 150 + 16, WHITE); /* 清除显示 */
        vTaskDelay(200);
        
    }
    lcd_show_string(30, 130, 200, 16, 16, "FATFS OK!", BLUE);
    lcd_show_string(30, 150, 200, 16, 16, "SD Total Size:     MB", BLUE);
    lcd_show_string(30, 170, 200, 16, 16, "SD  Free Size:     MB", BLUE);
    lcd_show_num(30 + 8 * 14, 150, total >> 10, 5, 16, BLUE); /* 显示SD卡总容量 MB */
    lcd_show_num(30 + 8 * 14, 170, free >> 10, 5, 16, BLUE);  /* 显示SD卡剩余容量 MB */
		vTaskDelay(5000);
		taskEXIT_CRITICAL();            /* 退出临界区 */
		SubFatfsCreateWindow();
			
			
			
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'home'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
          GUI_EndDialog(pMsg->hWin, 0);
          MainCreateWindow();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN SubFatfsCreateWindow(void);
WM_HWIN SubFatfsCreateWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
