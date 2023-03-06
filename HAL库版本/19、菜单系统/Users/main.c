/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       ͼƬ��ʾ ʵ��
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

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./MALLOC/malloc.h"
#include "./FATFS/exfuns/exfuns.h"
#include "./TEXT/text.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDIO/sdio_sdcard.h"
#include "./BSP/NORFLASH/norflash.h"
#include "./PICTURE/piclib.h"
#include "string.h"
#include "math.h"

/**�˵�ϵͳ***************************************************************/
void picturefunc(void);
typedef struct menu//����һ���˵�
{
u8 range_from,range_to; //��ǰ��ʾ���ʼ���������
u8 itemCount;//��Ŀ����
u8 selected;//��ǰѡ����
u8 *menuItems[17];//�˵���Ŀ
struct menu **subMenus;//�Ӳ˵�
struct menu *parent;//�ϼ��˵� ,����Ƕ�����Ϊnull
void (**func)();//ѡ����Ӧ�ȷ������ִ�еĺ���

}Menu;

Menu MainMenu = { //�������˵�
0,2,4,0,//Ĭ����ʾ0-3��ܹ�4���ǰѡ���0��
  {
  "����1          ",
  "����2          ",
	"����3          ",
  "ͼƬ��ѯ           "
  }
};

Menu pictureMenu = {//ͼƬ�˵�
0,3,6,0,
{
  "�ֲ�ͼƬ    ",
  "test1    ",
  "test2        ",
  "test3      ",
  "test4    ",
  "test5        "
}
};
Menu *currentMenu;//��ǰ�Ĳ˵�

//������ʾ�˵���
void display(u8 line) //��ʾ�˵������ѡ�е����
{
int i;
//line = 3-(currentMenu->range_to-line);
lcd_clear(WHITE);
for(i = 0;i<4;i++)
{
  //Lcd_Disp(i+1,0,currentMenu->menuItems[i+currentMenu->range_from]);
	text_show_string(30,(i+1)*20,200,16,currentMenu->menuItems[i+currentMenu->range_from],16,0,BLACK);
}
//highlight(0,line,8,255);//������ʾָ����
lcd_fill_circle(15,(line+1)*20+8,14,BLACK);//Բ�ι��
}
void func(void)
{

printf("hello");
}
//��ʼ���˵�:
void initMenu()
{
MainMenu.subMenus = mymalloc(SRAMIN,sizeof(&MainMenu)*4);
MainMenu.subMenus[0] = NULL;//��1��3��û���Ӳ˵���null,ѡ����������func����Ӧ���еĺ���
MainMenu.subMenus[1] = NULL;
MainMenu.subMenus[2] = NULL;
MainMenu.subMenus[3] = &pictureMenu;//�������ѯ���Ӳ˵�
MainMenu.func = mymalloc(SRAMIN,sizeof(&func)*4);
MainMenu.func[0] = NULL;
MainMenu.func[1] = NULL;
MainMenu.func[2] = NULL;//��ѡ���˲�����ȷ������ִ��func����
MainMenu.func[3] = NULL;
MainMenu.parent = NULL;//��ʾ�Ƕ����˵�

pictureMenu.subMenus = mymalloc(SRAMIN,sizeof(&pictureMenu)*6);
pictureMenu.subMenus[0] = pictureMenu.subMenus[1] = pictureMenu.subMenus[2] = pictureMenu.subMenus[3] = pictureMenu.subMenus[4] = pictureMenu.subMenus[5] = NULL;
pictureMenu.func = mymalloc(SRAMIN,sizeof(&printf)*6);
pictureMenu.func[0] = &picturefunc;
pictureMenu.func[2] = pictureMenu.func[2] = pictureMenu.func[3] = pictureMenu.func[4] = pictureMenu.func[5] = NULL;
pictureMenu.parent = &MainMenu;//��һ���˵���MainMenu.�����ѯ�Ӳ˵��󰴷��ؼ���������ʾ����˵� ��

currentMenu = &MainMenu;
}







  
 



/*************************************************************************/


/**
 * @brief       �õ�path·����,Ŀ���ļ����ܸ���
 * @param       path : ·��
 * @retval      ����Ч�ļ���
 */
uint16_t pic_get_tnum(char *path)
{
    uint8_t res;
    uint16_t rval = 0;
    DIR tdir;                                                 /* ��ʱĿ¼ */
    FILINFO *tfileinfo;                                       /* ��ʱ�ļ���Ϣ */
    tfileinfo = (FILINFO *)mymalloc(SRAMIN, sizeof(FILINFO)); /* �����ڴ� */
    res = f_opendir(&tdir, (const TCHAR *)path);              /* ��Ŀ¼ */

    if (res == FR_OK && tfileinfo)
    {
        while (1) /* ��ѯ�ܵ���Ч�ļ��� */
        {
            res = f_readdir(&tdir, tfileinfo); /* ��ȡĿ¼�µ�һ���ļ� */

            if (res != FR_OK || tfileinfo->fname[0] == 0)
                break; /* ������/��ĩβ��,�˳� */

            res = exfuns_file_type(tfileinfo->fname);

            if ((res & 0XF0) == 0X50) /* ȡ����λ,�����ǲ���ͼƬ�ļ� */
            {
                rval++; /* ��Ч�ļ�������1 */
            }
        }
    }

    myfree(SRAMIN, tfileinfo); /* �ͷ��ڴ� */
    return rval;
}

		uint8_t res;
    DIR picdir;           /* ͼƬĿ¼ */
    FILINFO *picfileinfo; /* �ļ���Ϣ */
    char *pname;          /* ��·�����ļ��� */
    uint16_t totpicnum;   /* ͼƬ�ļ����� */
    uint16_t curindex;    /* ͼƬ��ǰ���� */
    uint8_t key;          /* ��ֵ */
    uint8_t pause = 0;    /* ��ͣ��� */
    uint8_t t;
    uint16_t temp;
    uint32_t *picoffsettbl; /* ͼƬ�ļ�offset������ */
int main(void)
{
    

    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(72);                /* ��ʼ��USMART */
    led_init();                         /* ��ʼ��LED */
    lcd_init();                         /* ��ʼ��LCD */
    key_init();                         /* ��ʼ������ */
    my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */

    exfuns_init();           /* Ϊfatfs��ر��������ڴ� */
    f_mount(fs[0], "0:", 1); /* ����SD�� */
    f_mount(fs[1], "1:", 1); /* ����FLASH */

    while (fonts_init()) /* ����ֿ� */
    {
        lcd_show_string(30, 50, 200, 16, 16, "Font Error!", RED);
        delay_ms(200);
        lcd_fill(30, 50, 240, 66, WHITE); /* �����ʾ */
        delay_ms(200);
    }
		
		initMenu();//��ʼ���˵�
		display(currentMenu->selected);
		while(1)
		{
			key = key_scan(0);
			if(key == 0)
			{
			 delay_ms(10);
			 continue;
			}
			printf("key %d is press",key);
			switch(key)
			{
			 case 1://����
				if(currentMenu->selected == 0)//���˵�һ��
				 break;
				else
				{
				 currentMenu->selected--;
				 if(currentMenu->selected < currentMenu->range_from)//������ʾ������
				 {
					currentMenu->range_from = currentMenu->selected;
					currentMenu->range_to = currentMenu->range_from+3;
				 }
				 display(currentMenu->selected);
				 break;
				}
			 case 3://����
				if(currentMenu->selected == currentMenu->itemCount-1)
				 break;
				else
				{
				 currentMenu->selected++;
				 if(currentMenu->selected>currentMenu->range_to)
				 {
					currentMenu->range_to = currentMenu->selected;
					currentMenu->range_from = currentMenu->range_to-3;
				 }
				 display(currentMenu->selected);
				 break;
				}
			 case 4://Enter��
			 {
				if(currentMenu->subMenus[currentMenu->selected] !=NULL)
				{
				 currentMenu = currentMenu->subMenus[currentMenu->selected];
				 display(0);
				}
				else
				{
				 if(currentMenu->func[currentMenu->selected] != NULL)
				 {
					currentMenu->func[currentMenu->selected]();//ִ����Ӧ�ĺ���
					display(currentMenu->selected);//���غ�ָ�ԭ���Ĳ˵�״̬
				 }
				}
				break;
			 }
			 case 2://���ؼ�
			 {
				if(currentMenu->parent!=NULL)//���˵���Ϊ�գ�����ʾ���˵�
				{
				 currentMenu = currentMenu->parent;
				 display(currentMenu->selected);
				}
				break;
			 }
			 default:
				 break;
			}
			delay_ms(10);
		}
}


void picturefunc(void)
{

    text_show_string(30,  50, 200, 16, "����ԭ��STM32������", 16, 0, RED);
    text_show_string(30,  70, 200, 16, "ͼƬ��ʾ ʵ��", 16, 0, RED);
    text_show_string(30,  90, 200, 16, "KEY0:NEXT KEY1:PREV", 16, 0, RED);
    text_show_string(30, 110, 200, 16, "KEY_UP:PAUSE", 16, 0, RED);
    text_show_string(30, 130, 200, 16, "����ԭ��@ALIENTEK", 16, 0, RED);

    while (f_opendir(&picdir, "0:/PICTURE")) /* ��ͼƬ�ļ��� */
    {
        text_show_string(30, 150, 240, 16, "PICTURE�ļ��д���!", 16, 0, RED);
        delay_ms(200);
        lcd_fill(30, 150, 240, 186, WHITE); /* �����ʾ */
        delay_ms(200);
    }

    totpicnum = pic_get_tnum("0:/PICTURE"); /* �õ�����Ч�ļ��� */

    while (totpicnum == NULL) /* ͼƬ�ļ�Ϊ0 */
    {
        text_show_string(30, 150, 240, 16, "û��ͼƬ�ļ�!", 16, 0, RED);
        delay_ms(200);
        lcd_fill(30, 150, 240, 186, WHITE); /* �����ʾ */
        delay_ms(200);
    }

    picfileinfo = (FILINFO *)mymalloc(SRAMIN, sizeof(FILINFO)); /* �����ڴ� */
    pname = mymalloc(SRAMIN, FF_MAX_LFN * 2 + 1);               /* Ϊ��·�����ļ��������ڴ� */
    picoffsettbl = mymalloc(SRAMIN, 4 * totpicnum);             /* ����4*totpicnum���ֽڵ��ڴ�,���ڴ��ͼƬ���� */

    while (!picfileinfo || !pname || !picoffsettbl) /* �ڴ������� */
    {
        text_show_string(30, 150, 240, 16, "�ڴ����ʧ��!", 16, 0, RED);
        delay_ms(200);
        lcd_fill(30, 150, 240, 186, WHITE); /* �����ʾ */
        delay_ms(200);
    }

    /* ��¼���� */
    res = f_opendir(&picdir, "0:/PICTURE"); /* ��Ŀ¼ */

    if (res == FR_OK)
    {
        curindex = 0; /* ��ǰ����Ϊ0 */

        while (1) /* ȫ����ѯһ�� */
        {
            temp = picdir.dptr;                    /* ��¼��ǰdptrƫ�� */
            res = f_readdir(&picdir, picfileinfo); /* ��ȡĿ¼�µ�һ���ļ� */

            if (res != FR_OK || picfileinfo->fname[0] == 0)
                break; /* ������/��ĩβ��,�˳� */

            res = exfuns_file_type(picfileinfo->fname);

            if ((res & 0XF0) == 0X50) /* ȡ����λ,�����ǲ���ͼƬ�ļ� */
            {
                picoffsettbl[curindex] = temp; /* ��¼���� */
                curindex++;
            }
        }
    }

    text_show_string(30, 150, 240, 16, "��ʼ��ʾ...", 16, 0, RED);
    delay_ms(1500);
    piclib_init();                                         /* ��ʼ����ͼ */
    curindex = 0;                                          /* ��0��ʼ��ʾ */
    res = f_opendir(&picdir, (const TCHAR *)"0:/PICTURE"); /* ��Ŀ¼ */

    while (res == FR_OK) /* �򿪳ɹ� */
    {
        dir_sdi(&picdir, picoffsettbl[curindex]); /* �ı䵱ǰĿ¼���� */
        res = f_readdir(&picdir, picfileinfo);    /* ��ȡĿ¼�µ�һ���ļ� */

        if (res != FR_OK || picfileinfo->fname[0] == 0)
            break; /* ������/��ĩβ��,�˳� */

        strcpy((char *)pname, "0:/PICTURE/");                    /* ����·��(Ŀ¼) */
        strcat((char *)pname, (const char *)picfileinfo->fname); /* ���ļ������ں��� */
        lcd_clear(BLACK);
        piclib_ai_load_picfile(pname, 0, 0, lcddev.width, lcddev.height, 1); /* ��ʾͼƬ */
        text_show_string(2, 2, lcddev.width, 16, (char *)pname, 16, 1, RED); /* ��ʾͼƬ���� */
        t = 0;
				curindex++;


        res = 0;
    }

    myfree(SRAMIN, picfileinfo);  /* �ͷ��ڴ� */
    myfree(SRAMIN, pname);        /* �ͷ��ڴ� */
    myfree(SRAMIN, picoffsettbl); /* �ͷ��ڴ� */
		
		myfree(SRAMIN,MainMenu.subMenus ); /* �ͷ��ڴ� */
		myfree(SRAMIN,MainMenu.func ); /* �ͷ��ڴ� */
		myfree(SRAMIN,pictureMenu.subMenus ); /* �ͷ��ڴ� */
		myfree(SRAMIN,pictureMenu.func ); /* �ͷ��ڴ� */
	
}











