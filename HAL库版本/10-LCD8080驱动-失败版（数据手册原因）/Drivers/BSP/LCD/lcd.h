#ifndef __LCD_H
#define __LCD_H

#include "stdlib.h"
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* LCD RST/WR/RD/BL/CS/RS 引脚 定义 
 * LCD_D0~D15,由于引脚太多,就不在这里定义了,直接在lcd_init里面修改.所以在移植的时候,除了改
 * 这6个IO口, 还得改LCD_Init里面的D0~D15所在的IO口.
 */
 
#define LCD_BL_GPIO_PORT                GPIOC
#define LCD_BL_GPIO_PIN                 GPIO_PIN_10
#define LCD_BL_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 背光好像不用所在IO口时钟使能 */

#define LCD_WR_GPIO_PORT                GPIOD
#define LCD_WR_GPIO_PIN                 GPIO_PIN_5
#define LCD_WR_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

#define LCD_RD_GPIO_PORT                GPIOD
#define LCD_RD_GPIO_PIN                 GPIO_PIN_4
#define LCD_RD_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

#define LCD_CS_GPIO_PORT                GPIOG
#define LCD_CS_GPIO_PIN                 GPIO_PIN_12
#define LCD_CS_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

#define LCD_RS_GPIO_PORT                GPIOG
#define LCD_RS_GPIO_PIN                 GPIO_PIN_0
#define LCD_RS_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */


#define LCD_DATA_PD_GPIO_PORT                GPIOD
#define LCD_DATA_PE_GPIO_PORT            		 GPIOE

#define LCD_DATA_PD_GPIO_PIN14               GPIO_PIN_14 		/* D0 */
#define LCD_DATA_PD_GPIO_PIN15               GPIO_PIN_15 
#define LCD_DATA_PD_GPIO_PIN0                GPIO_PIN_0 
#define LCD_DATA_PD_GPIO_PIN1              	 GPIO_PIN_1

#define LCD_DATA_PE_GPIO_PIN7              	 GPIO_PIN_7
#define LCD_DATA_PE_GPIO_PIN8              	 GPIO_PIN_8
#define LCD_DATA_PE_GPIO_PIN9             	 GPIO_PIN_9
#define LCD_DATA_PE_GPIO_PIN10               GPIO_PIN_10
#define LCD_DATA_PE_GPIO_PIN11               GPIO_PIN_11
#define LCD_DATA_PE_GPIO_PIN12               GPIO_PIN_12
#define LCD_DATA_PE_GPIO_PIN13               GPIO_PIN_13
#define LCD_DATA_PE_GPIO_PIN14               GPIO_PIN_14
#define LCD_DATA_PE_GPIO_PIN15               GPIO_PIN_15

#define LCD_DATA_PD_GPIO_PIN8              	 GPIO_PIN_8
#define LCD_DATA_PD_GPIO_PIN9                GPIO_PIN_9
#define LCD_DATA_PD_GPIO_PIN10               GPIO_PIN_10 /* D15 */

#define LCD_DATA_PD_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */
#define LCD_DATA_PE_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

/* LCD 端口控制函数定义 */
/* 利用操作寄存器的方式控制IO引脚提高屏幕的刷新率 */
#define LCD_BL(x)       LCD_BL_GPIO_PORT->BSRR = LCD_BL_GPIO_PIN << (16 * (!x))     /* 设置BL引脚 */

#define LCD_WR(x)       LCD_WR_GPIO_PORT->BSRR = LCD_WR_GPIO_PIN << (16 * (!x))     /* 设置WR引脚 */
#define LCD_RD(x)       LCD_RD_GPIO_PORT->BSRR = LCD_RD_GPIO_PIN << (16 * (!x))     /* 设置RD引脚 */
#define LCD_CS(x)       LCD_CS_GPIO_PORT->BSRR = LCD_CS_GPIO_PIN << (16 * (!x))     /* 设置CS引脚 */
#define LCD_RS(x)       LCD_RS_GPIO_PORT->BSRR = LCD_RS_GPIO_PIN << (16 * (!x))     /* 设置RS引脚 */


#define LCD_DATA_OUT(x) do{ ((x&(0x0001))==0x0001)?HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN14, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN14, GPIO_PIN_RESET);\
	((x&(0x0002))==0x0002)?HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN15, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN15, GPIO_PIN_RESET);\
	((x&(0x0004))==0x0004)?HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN0, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN0, GPIO_PIN_RESET);\
	((x&(0x0008))==0x0008)?HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN1, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN1, GPIO_PIN_RESET);\
	((x&(0x0010))==0x0010)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN7, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN7, GPIO_PIN_RESET);\
	((x&(0x0020))==0x0020)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN8, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN8, GPIO_PIN_RESET);\
	((x&(0x0040))==0x0040)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN9, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN9, GPIO_PIN_RESET);\
	((x&(0x0080))==0x0080)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN10, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN10, GPIO_PIN_RESET);\
	((x&(0x0100))==0x0100)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN11, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN11, GPIO_PIN_RESET);\
	((x&(0x0200))==0x0200)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN12, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN12, GPIO_PIN_RESET);\
	((x&(0x0400))==0x0400)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN13, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN13, GPIO_PIN_RESET);\
	((x&(0x0800))==0x0800)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN14, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN14, GPIO_PIN_RESET);\
	((x&(0x1000))==0x1000)?HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN15, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PE_GPIO_PORT, LCD_DATA_PE_GPIO_PIN15, GPIO_PIN_RESET);\
	((x&(0x2000))==0x2000)?HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN8, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN8, GPIO_PIN_RESET);\
	((x&(0x4000))==0x4000)?HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN9, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN9, GPIO_PIN_RESET);\
	((x&(0x8000))==0x8000)?HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN10, GPIO_PIN_SET) : HAL_GPIO_WritePin(LCD_DATA_PD_GPIO_PORT, LCD_DATA_PD_GPIO_PIN10, GPIO_PIN_RESET);\
}while(0)   /* 写数据引脚 LCD_DATA_GPIO_PORT->ODR = x  */

#define LCD_DATA_IN     (LCD_DATA_PD_GPIO_PORT->IDR>>14)|((LCD_DATA_PD_GPIO_PORT->IDR&0x0003)<<2)|((LCD_DATA_PD_GPIO_PORT->IDR&0x0700)<<5)|((LCD_DATA_PE_GPIO_PORT->IDR&0xFF80)>>3)     /* 读数据引脚 */

/* 以下是使用HAL库方式控制IO引脚 */

///* LCD背光控制 */
//#define LCD_BL(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)

//#define LCD_WR(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_WR_GPIO_PORT, LCD_WR_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_WR_GPIO_PORT, LCD_WR_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)     /* 设置WR引脚 */
//#define LCD_RD(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_RD_GPIO_PORT, LCD_RD_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_RD_GPIO_PORT, LCD_RD_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)     /* 设置RD引脚 */
//#define LCD_CS(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)     /* 设置CS引脚 */
//#define LCD_RS(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_RS_GPIO_PORT, LCD_RS_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_RS_GPIO_PORT, LCD_RS_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)     /* 设置RS引脚 */

/******************************************************************************************/

/* LCD重要参数集 */
typedef struct
{
    uint16_t width;     /* LCD 宽度 */
    uint16_t height;    /* LCD 高度 */
    uint16_t id;        /* LCD ID */
    uint8_t dir;        /* 横屏还是竖屏控制：0，竖屏；1，横屏。 */
    uint16_t wramcmd;   /* 开始写gram指令 */
    uint16_t setxcmd;   /* 设置x坐标指令 */
    uint16_t setycmd;   /* 设置y坐标指令 */
} _lcd_dev;

/* LCD参数 */
extern _lcd_dev lcddev; /* 管理LCD重要参数 */


/* 常用画笔颜色 */
#define WHITE           0xFFFF      /* 白色 */
#define BLACK           0x0000      /* 黑色 */
#define RED             0xF800      /* 红色 */
#define GREEN           0x07E0      /* 绿色 */
#define BLUE            0x001F      /* 蓝色 */ 
#define MAGENTA         0XF81F      /* 品红色/紫红色 = BLUE + RED */
#define YELLOW          0XFFE0      /* 黄色 = GREEN + RED */
#define CYAN            0X07FF      /* 青色 = GREEN + BLUE */  

/* 非常用颜色 */
#define BROWN           0XBC40      /* 棕色 */
#define BRRED           0XFC07      /* 棕红色 */
#define GRAY            0X8430      /* 灰色 */ 
#define DARKBLUE        0X01CF      /* 深蓝色 */
#define LIGHTBLUE       0X7D7C      /* 浅蓝色 */ 
#define GRAYBLUE        0X5458      /* 灰蓝色 */ 
#define LIGHTGREEN      0X841F      /* 浅绿色 */  
#define LGRAY           0XC618      /* 浅灰色(PANNEL),窗体背景色 */ 
#define LGRAYBLUE       0XA651      /* 浅灰蓝色(中间层颜色) */ 
#define LBBLUE          0X2B12      /* 浅棕蓝色(选择条目的反色) */ 

/* 函数申明 */
void lcd_init(void);    /* lcd初始化函数 */

void lcd_wr_data (uint16_t data);                   /* 8080写数据 */
void lcd_wr_regno(volatile uint16_t regno);         /* 8080写命令 */
void lcd_write_reg(uint16_t regno, uint16_t data);  /* 往寄存器写值 */
uint16_t lcd_rd_data(void);                         /* 8080读数据 */

void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
uint16_t  lcd_read_point (uint16_t x, uint16_t y);
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);
void lcd_clear(uint16_t color);
#endif


/* 300 */














