#ifndef __LCD_H
#define __LCD_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* LCD�õ����ź궨�� */

/* д���� */
#define LCD_WR_GPIO_PORT                    GPIOD
#define LCD_WR_GPIO_PIN                     GPIO_PIN_5
#define LCD_WR_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

/* ������ */
#define LCD_RD_GPIO_PORT                    GPIOD
#define LCD_RD_GPIO_PIN                     GPIO_PIN_4
#define LCD_RD_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

/* 16���������� �ο�ԭ��ͼ */

/* LCD_BL�������� */
#define LCD_BL_GPIO_PORT                    GPIOB
#define LCD_BL_GPIO_PIN                     GPIO_PIN_0
#define LCD_BL_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/*  LCD_CS(��Ҫ����LCD_FSMC_NEX������ȷ��IO��) �� LCD_RS(��Ҫ����LCD_FSMC_AX������ȷ��IO��) ���� ���� */
/* CSƬѡ���� */
#define LCD_CS_GPIO_PORT                    GPIOG
#define LCD_CS_GPIO_PIN                     GPIO_PIN_12
#define LCD_CS_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* PG��ʱ��ʹ�� */

/* RS������������ */
#define LCD_RS_GPIO_PORT                    GPIOG
#define LCD_RS_GPIO_PIN                     GPIO_PIN_0
#define LCD_RS_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* PG��ʱ��ʹ�� */

/* LCD��Ҫ������ */
typedef struct
{
    uint16_t width;     /* LCD ��� */
    uint16_t height;    /* LCD �߶� */
    uint16_t id;        /* LCD ID */
    uint8_t dir;        /* ���������������ƣ�0��������1�������� */
    uint16_t wramcmd;   /* ��ʼдgramָ�� */
    uint16_t setxcmd;   /* ����x����ָ�� */
    uint16_t setycmd;   /* ����y����ָ�� */
} _lcd_dev;

/* LCD������� */
#define LCD_BL(x)       LCD_BL_GPIO_PORT->BSRR = LCD_BL_GPIO_PIN << (16 * (!x))  

/* FSMC��ز��� ���� 
 * ע��: ����Ĭ����ͨ��FSMC��1������LCD, ��1��4��Ƭѡ: FSMC_NE1~4
 *
 * �޸�LCD_FSMC_NEX, ��Ӧ��LCD_CS_GPIO�������Ҳ�ø�
 * �޸�LCD_FSMC_AX , ��Ӧ��LCD_RS_GPIO�������Ҳ�ø�
 */
#define LCD_FSMC_NEX         4              /* ʹ��FSMC_NE4��LCD_CS,ȡֵ��Χֻ����: 1~4 */
#define LCD_FSMC_AX          10             /* ʹ��FSMC_A10��LCD_RS,ȡֵ��Χ��: 0 ~ 25 */

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

#define FSMC_ADDR_DATA        ��(((TFTLCD->LCD_DATA)>>1)<<8��|((((TFTLCD->LCD_DATA)>>1)<<8)>>1) ��
#define FSMC_ADDR_CMD           LCD_CMD*/

/* ���û�����ɫ */
#define WHITE           0xFFFF      /* ��ɫ */
#define BLACK           0x0000      /* ��ɫ */
#define RED             0xF800      /* ��ɫ */
#define GREEN           0x07E0      /* ��ɫ */
#define BLUE            0x001F      /* ��ɫ */ 
#define MAGENTA         0XF81F      /* Ʒ��ɫ/�Ϻ�ɫ = BLUE + RED */
#define YELLOW          0XFFE0      /* ��ɫ = GREEN + RED */
#define CYAN            0X07FF      /* ��ɫ = GREEN + BLUE */  

/* �ǳ�����ɫ */
#define BROWN           0XBC40      /* ��ɫ */
#define BRRED           0XFC07      /* �غ�ɫ */
#define GRAY            0X8430      /* ��ɫ */ 
#define DARKBLUE        0X01CF      /* ����ɫ */
#define LIGHTBLUE       0X7D7C      /* ǳ��ɫ */ 
#define GRAYBLUE        0X5458      /* ����ɫ */ 
#define LIGHTGREEN      0X841F      /* ǳ��ɫ */  
#define LGRAY           0XC618      /* ǳ��ɫ(PANNEL),���屳��ɫ */ 
#define LGRAYBLUE       0XA651      /* ǳ����ɫ(�м����ɫ) */ 
#define LBBLUE          0X2B12      /* ǳ����ɫ(ѡ����Ŀ�ķ�ɫ) */ 

/* �������� */

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

