#ifndef __LCD_H
#define __LCD_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* LCD用到引脚宏定义 */

/* 写引脚 */
#define LCD_WR_GPIO_PORT                    GPIOD
#define LCD_WR_GPIO_PIN                     GPIO_PIN_5
#define LCD_WR_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

/* 读引脚 */
#define LCD_RD_GPIO_PORT                    GPIOD
#define LCD_RD_GPIO_PIN                     GPIO_PIN_4
#define LCD_RD_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

/* 16个数据引脚 参考原理图 */

/* LCD_BL背光引脚 */
#define LCD_BL_GPIO_PORT                    GPIOB
#define LCD_BL_GPIO_PIN                     GPIO_PIN_0
#define LCD_BL_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/*  LCD_CS(需要根据LCD_FSMC_NEX设置正确的IO口) 和 LCD_RS(需要根据LCD_FSMC_AX设置正确的IO口) 引脚 定义 */
/* CS片选引脚 */
#define LCD_CS_GPIO_PORT                    GPIOG
#define LCD_CS_GPIO_PIN                     GPIO_PIN_12
#define LCD_CS_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* PG口时钟使能 */

/* RS数据类型引脚 */
#define LCD_RS_GPIO_PORT                    GPIOG
#define LCD_RS_GPIO_PIN                     GPIO_PIN_0
#define LCD_RS_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* PG口时钟使能 */

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

/* LCD背光控制 */
#define LCD_BL(x)       LCD_BL_GPIO_PORT->BSRR = LCD_BL_GPIO_PIN << (16 * (!x))  

/* FSMC相关参数 定义 
 * 注意: 我们默认是通过FSMC块1来连接LCD, 块1有4个片选: FSMC_NE1~4
 *
 * 修改LCD_FSMC_NEX, 对应的LCD_CS_GPIO相关设置也得改
 * 修改LCD_FSMC_AX , 对应的LCD_RS_GPIO相关设置也得改
 */
#define LCD_FSMC_NEX         4              /* 使用FSMC_NE4接LCD_CS,取值范围只能是: 1~4 */
#define LCD_FSMC_AX          10             /* 使用FSMC_A10接LCD_RS,取值范围是: 0 ~ 25 */

/* LCD_BASE = (0X6000 0000 + (0X400 0000 * (x - 1))) | (2^y * 2 - 2) */
#define FSMC_ADDR_DATA          ((uint32_t) 0X6C000800)
#define FSMC_ADDR_CMD           ((uint32_t) 0X6C000000)


/*typedef struct
{
	uint16_t LCD_CMD;
	uint16_t LCD_DATA;
}TFTLCD_TypeDef;
#define TFTLCD_BASE        ((uint32_t)(0x6C000000 | 0x000007FE))
#define TFTLCD             ((TFTLCD_TypeDef *) TFTLCD_BASE)

#define FSMC_ADDR_DATA        （(((TFTLCD->LCD_DATA)>>1)<<8）|((((TFTLCD->LCD_DATA)>>1)<<8)>>1) ）
#define FSMC_ADDR_CMD           LCD_CMD*/

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

/* 函数声明 */

void lcd_init(void);
void lcd_wr_regno(volatile uint16_t cmd);
void lcd_wr_data(volatile uint16_t data);
uint16_t lcd_rd_data(void);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_clear(uint16_t color);
uint16_t lcd_read_point (uint16_t x, uint16_t y);



void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);
void LCD_WriteData_Color(uint16_t color);
uint32_t LCD_RGBColor_Change(uint16_t color);

#endif

