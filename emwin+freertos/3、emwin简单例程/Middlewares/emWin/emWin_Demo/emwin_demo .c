#include "dialog.h"//����window�Ի��� ͷ�ļ�
#include "emwin_demo.h"
#include "GUI.h"


void emwin_main(void)

{

    GUI_Init();                     //��ʼ��emWin
    mainCreateWindow();
    
    while (1)
    {
        GUI_Delay(20);
    }       //����GUI_Delay������ʱ20MS(����Ŀ���ǵ���GUI_Exec()����)

}
