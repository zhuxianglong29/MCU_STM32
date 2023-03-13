#include "dialog.h"//包含window对话框 头文件
#include "emwin_demo.h"
#include "GUI.h"


void emwin_main(void)

{

    GUI_Init();                     //初始化emWin
    mainCreateWindow();
    
    while (1)
    {
        GUI_Delay(20);
    }       //调用GUI_Delay函数延时20MS(最终目的是调用GUI_Exec()函数)

}
