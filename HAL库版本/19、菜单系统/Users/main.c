/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       图片显示 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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

/**菜单系统***************************************************************/
void picturefunc(void);
typedef struct menu//定义一个菜单
{
u8 range_from,range_to; //当前显示的项开始及结束序号
u8 itemCount;//项目总数
u8 selected;//当前选择项
u8 *menuItems[17];//菜单项目
struct menu **subMenus;//子菜单
struct menu *parent;//上级菜单 ,如果是顶级则为null
void (**func)();//选择相应项按确定键后执行的函数

}Menu;

Menu MainMenu = { //定义主菜单
0,2,4,0,//默认显示0-3项，总共4项，当前选择第0项
  {
  "设置1          ",
  "设置2          ",
	"设置3          ",
  "图片查询           "
  }
};

Menu pictureMenu = {//图片菜单
0,3,6,0,
{
  "轮播图片    ",
  "test1    ",
  "test2        ",
  "test3      ",
  "test4    ",
  "test5        "
}
};
Menu *currentMenu;//当前的菜单

//用于显示菜单项
void display(u8 line) //显示菜单项并设置选中的项反白
{
int i;
//line = 3-(currentMenu->range_to-line);
lcd_clear(WHITE);
for(i = 0;i<4;i++)
{
  //Lcd_Disp(i+1,0,currentMenu->menuItems[i+currentMenu->range_from]);
	text_show_string(30,(i+1)*20,200,16,currentMenu->menuItems[i+currentMenu->range_from],16,0,BLACK);
}
//highlight(0,line,8,255);//反白显示指定行
lcd_fill_circle(15,(line+1)*20+8,14,BLACK);//圆形光标
}
void func(void)
{

printf("hello");
}
//初始化菜单:
void initMenu()
{
MainMenu.subMenus = mymalloc(SRAMIN,sizeof(&MainMenu)*4);
MainMenu.subMenus[0] = NULL;//第1到3项没有子菜单置null,选择后程序会调用func中相应项中的函数
MainMenu.subMenus[1] = NULL;
MainMenu.subMenus[2] = NULL;
MainMenu.subMenus[3] = &pictureMenu;//第四项查询有子菜单
MainMenu.func = mymalloc(SRAMIN,sizeof(&func)*4);
MainMenu.func[0] = NULL;
MainMenu.func[1] = NULL;
MainMenu.func[2] = NULL;//当选择了并按了确定，会执行func函数
MainMenu.func[3] = NULL;
MainMenu.parent = NULL;//表示是顶级菜单

pictureMenu.subMenus = mymalloc(SRAMIN,sizeof(&pictureMenu)*6);
pictureMenu.subMenus[0] = pictureMenu.subMenus[1] = pictureMenu.subMenus[2] = pictureMenu.subMenus[3] = pictureMenu.subMenus[4] = pictureMenu.subMenus[5] = NULL;
pictureMenu.func = mymalloc(SRAMIN,sizeof(&printf)*6);
pictureMenu.func[0] = &picturefunc;
pictureMenu.func[2] = pictureMenu.func[2] = pictureMenu.func[3] = pictureMenu.func[4] = pictureMenu.func[5] = NULL;
pictureMenu.parent = &MainMenu;//上一级菜单是MainMenu.进入查询子菜单后按返回键，将会显示这个菜单 项

currentMenu = &MainMenu;
}







  
 



/*************************************************************************/


/**
 * @brief       得到path路径下,目标文件的总个数
 * @param       path : 路径
 * @retval      总有效文件数
 */
uint16_t pic_get_tnum(char *path)
{
    uint8_t res;
    uint16_t rval = 0;
    DIR tdir;                                                 /* 临时目录 */
    FILINFO *tfileinfo;                                       /* 临时文件信息 */
    tfileinfo = (FILINFO *)mymalloc(SRAMIN, sizeof(FILINFO)); /* 申请内存 */
    res = f_opendir(&tdir, (const TCHAR *)path);              /* 打开目录 */

    if (res == FR_OK && tfileinfo)
    {
        while (1) /* 查询总的有效文件数 */
        {
            res = f_readdir(&tdir, tfileinfo); /* 读取目录下的一个文件 */

            if (res != FR_OK || tfileinfo->fname[0] == 0)
                break; /* 错误了/到末尾了,退出 */

            res = exfuns_file_type(tfileinfo->fname);

            if ((res & 0XF0) == 0X50) /* 取高四位,看看是不是图片文件 */
            {
                rval++; /* 有效文件数增加1 */
            }
        }
    }

    myfree(SRAMIN, tfileinfo); /* 释放内存 */
    return rval;
}

		uint8_t res;
    DIR picdir;           /* 图片目录 */
    FILINFO *picfileinfo; /* 文件信息 */
    char *pname;          /* 带路径的文件名 */
    uint16_t totpicnum;   /* 图片文件总数 */
    uint16_t curindex;    /* 图片当前索引 */
    uint8_t key;          /* 键值 */
    uint8_t pause = 0;    /* 暂停标记 */
    uint8_t t;
    uint16_t temp;
    uint32_t *picoffsettbl; /* 图片文件offset索引表 */
int main(void)
{
    

    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
    usmart_dev.init(72);                /* 初始化USMART */
    led_init();                         /* 初始化LED */
    lcd_init();                         /* 初始化LCD */
    key_init();                         /* 初始化按键 */
    my_mem_init(SRAMIN);                /* 初始化内部SRAM内存池 */

    exfuns_init();           /* 为fatfs相关变量申请内存 */
    f_mount(fs[0], "0:", 1); /* 挂载SD卡 */
    f_mount(fs[1], "1:", 1); /* 挂载FLASH */

    while (fonts_init()) /* 检查字库 */
    {
        lcd_show_string(30, 50, 200, 16, 16, "Font Error!", RED);
        delay_ms(200);
        lcd_fill(30, 50, 240, 66, WHITE); /* 清除显示 */
        delay_ms(200);
    }
		
		initMenu();//初始化菜单
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
			 case 1://向上
				if(currentMenu->selected == 0)//到了第一项
				 break;
				else
				{
				 currentMenu->selected--;
				 if(currentMenu->selected < currentMenu->range_from)//更新显示的区域
				 {
					currentMenu->range_from = currentMenu->selected;
					currentMenu->range_to = currentMenu->range_from+3;
				 }
				 display(currentMenu->selected);
				 break;
				}
			 case 3://向下
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
			 case 4://Enter键
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
					currentMenu->func[currentMenu->selected]();//执行相应的函数
					display(currentMenu->selected);//返回后恢复原来的菜单状态
				 }
				}
				break;
			 }
			 case 2://返回键
			 {
				if(currentMenu->parent!=NULL)//父菜单不为空，将显示父菜单
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

    text_show_string(30,  50, 200, 16, "正点原子STM32开发板", 16, 0, RED);
    text_show_string(30,  70, 200, 16, "图片显示 实验", 16, 0, RED);
    text_show_string(30,  90, 200, 16, "KEY0:NEXT KEY1:PREV", 16, 0, RED);
    text_show_string(30, 110, 200, 16, "KEY_UP:PAUSE", 16, 0, RED);
    text_show_string(30, 130, 200, 16, "正点原子@ALIENTEK", 16, 0, RED);

    while (f_opendir(&picdir, "0:/PICTURE")) /* 打开图片文件夹 */
    {
        text_show_string(30, 150, 240, 16, "PICTURE文件夹错误!", 16, 0, RED);
        delay_ms(200);
        lcd_fill(30, 150, 240, 186, WHITE); /* 清除显示 */
        delay_ms(200);
    }

    totpicnum = pic_get_tnum("0:/PICTURE"); /* 得到总有效文件数 */

    while (totpicnum == NULL) /* 图片文件为0 */
    {
        text_show_string(30, 150, 240, 16, "没有图片文件!", 16, 0, RED);
        delay_ms(200);
        lcd_fill(30, 150, 240, 186, WHITE); /* 清除显示 */
        delay_ms(200);
    }

    picfileinfo = (FILINFO *)mymalloc(SRAMIN, sizeof(FILINFO)); /* 申请内存 */
    pname = mymalloc(SRAMIN, FF_MAX_LFN * 2 + 1);               /* 为带路径的文件名分配内存 */
    picoffsettbl = mymalloc(SRAMIN, 4 * totpicnum);             /* 申请4*totpicnum个字节的内存,用于存放图片索引 */

    while (!picfileinfo || !pname || !picoffsettbl) /* 内存分配出错 */
    {
        text_show_string(30, 150, 240, 16, "内存分配失败!", 16, 0, RED);
        delay_ms(200);
        lcd_fill(30, 150, 240, 186, WHITE); /* 清除显示 */
        delay_ms(200);
    }

    /* 记录索引 */
    res = f_opendir(&picdir, "0:/PICTURE"); /* 打开目录 */

    if (res == FR_OK)
    {
        curindex = 0; /* 当前索引为0 */

        while (1) /* 全部查询一遍 */
        {
            temp = picdir.dptr;                    /* 记录当前dptr偏移 */
            res = f_readdir(&picdir, picfileinfo); /* 读取目录下的一个文件 */

            if (res != FR_OK || picfileinfo->fname[0] == 0)
                break; /* 错误了/到末尾了,退出 */

            res = exfuns_file_type(picfileinfo->fname);

            if ((res & 0XF0) == 0X50) /* 取高四位,看看是不是图片文件 */
            {
                picoffsettbl[curindex] = temp; /* 记录索引 */
                curindex++;
            }
        }
    }

    text_show_string(30, 150, 240, 16, "开始显示...", 16, 0, RED);
    delay_ms(1500);
    piclib_init();                                         /* 初始化画图 */
    curindex = 0;                                          /* 从0开始显示 */
    res = f_opendir(&picdir, (const TCHAR *)"0:/PICTURE"); /* 打开目录 */

    while (res == FR_OK) /* 打开成功 */
    {
        dir_sdi(&picdir, picoffsettbl[curindex]); /* 改变当前目录索引 */
        res = f_readdir(&picdir, picfileinfo);    /* 读取目录下的一个文件 */

        if (res != FR_OK || picfileinfo->fname[0] == 0)
            break; /* 错误了/到末尾了,退出 */

        strcpy((char *)pname, "0:/PICTURE/");                    /* 复制路径(目录) */
        strcat((char *)pname, (const char *)picfileinfo->fname); /* 将文件名接在后面 */
        lcd_clear(BLACK);
        piclib_ai_load_picfile(pname, 0, 0, lcddev.width, lcddev.height, 1); /* 显示图片 */
        text_show_string(2, 2, lcddev.width, 16, (char *)pname, 16, 1, RED); /* 显示图片名字 */
        t = 0;
				curindex++;


        res = 0;
    }

    myfree(SRAMIN, picfileinfo);  /* 释放内存 */
    myfree(SRAMIN, pname);        /* 释放内存 */
    myfree(SRAMIN, picoffsettbl); /* 释放内存 */
		
		myfree(SRAMIN,MainMenu.subMenus ); /* 释放内存 */
		myfree(SRAMIN,MainMenu.func ); /* 释放内存 */
		myfree(SRAMIN,pictureMenu.subMenus ); /* 释放内存 */
		myfree(SRAMIN,pictureMenu.func ); /* 释放内存 */
	
}











