#ifndef __LCD_H
#define __LCD_H

#include "stdlib.h"
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* LCD RST/WR/RD/BL/CS/RS ���� ���� 
 * LCD_D0~D15,��������̫��,�Ͳ������ﶨ����,ֱ����lcd_init�����޸�.��������ֲ��ʱ��,���˸�
 * ��6��IO��, ���ø�LCD_Init�����D0~D15���ڵ�IO��.
 */
 
#define LCD_BL_GPIO_PORT                GPIOC
#define LCD_BL_GPIO_PIN                 GPIO_PIN_10
#define LCD_BL_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* �������������IO��ʱ��ʹ�� */

#define LCD_WR_GPIO_PORT                GPIOD
#define LCD_WR_GPIO_PIN                 GPIO_PIN_5
#define LCD_WR_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* ����IO��ʱ��ʹ�� */

#define LCD_RD_GPIO_PORT                GPIOD
#define LCD_RD_GPIO_PIN                 GPIO_PIN_4
#define LCD_RD_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* ����IO��ʱ��ʹ�� */

#define LCD_CS_GPIO_PORT                GPIOG
#define LCD_CS_GPIO_PIN                 GPIO_PIN_12
#define LCD_CS_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* ����IO��ʱ��ʹ�� */

#define LCD_RS_GPIO_PORT                GPIOG
#define LCD_RS_GPIO_PIN                 GPIO_PIN_0
#define LCD_RS_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* ����IO��ʱ��ʹ�� */


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

#define LCD_DATA_PD_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* ����IO��ʱ��ʹ�� */
#define LCD_DATA_PE_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* ����IO��ʱ��ʹ�� */

/* LCD �˿ڿ��ƺ������� */
/* ���ò����Ĵ����ķ�ʽ����IO���������Ļ��ˢ���� */
#define LCD_BL(x)       LCD_BL_GPIO_PORT->BSRR = LCD_BL_GPIO_PIN << (16 * (!x))     /* ����BL���� */

#define LCD_WR(x)       LCD_WR_GPIO_PORT->BSRR = LCD_WR_GPIO_PIN << (16 * (!x))     /* ����WR���� */
#define LCD_RD(x)       LCD_RD_GPIO_PORT->BSRR = LCD_RD_GPIO_PIN << (16 * (!x))     /* ����RD���� */
#define LCD_CS(x)       LCD_CS_GPIO_PORT->BSRR = LCD_CS_GPIO_PIN << (16 * (!x))     /* ����CS���� */
#define LCD_RS(x)       LCD_RS_GPIO_PORT->BSRR = LCD_RS_GPIO_PIN << (16 * (!x))     /* ����RS���� */


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
}while(0)   /* д�������� LCD_DATA_GPIO_PORT->ODR = x  */

#define LCD_DATA_IN     (LCD_DATA_PD_GPIO_PORT->IDR>>14)|((LCD_DATA_PD_GPIO_PORT->IDR&0x0003)<<2)|((LCD_DATA_PD_GPIO_PORT->IDR&0x0700)<<5)|((LCD_DATA_PE_GPIO_PORT->IDR&0xFF80)>>3)     /* ���������� */

/* ������ʹ��HAL�ⷽʽ����IO���� */

///* LCD������� */
//#define LCD_BL(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)

//#define LCD_WR(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_WR_GPIO_PORT, LCD_WR_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_WR_GPIO_PORT, LCD_WR_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)     /* ����WR���� */
//#define LCD_RD(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_RD_GPIO_PORT, LCD_RD_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_RD_GPIO_PORT, LCD_RD_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)     /* ����RD���� */
//#define LCD_CS(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)     /* ����CS���� */
//#define LCD_RS(x)   do{ x ? \
//                      HAL_GPIO_WritePin(LCD_RS_GPIO_PORT, LCD_RS_GPIO_PIN, GPIO_PIN_SET) : \
//                      HAL_GPIO_WritePin(LCD_RS_GPIO_PORT, LCD_RS_GPIO_PIN, GPIO_PIN_RESET); \
//                     }while(0)     /* ����RS���� */

/******************************************************************************************/

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

/* LCD���� */
extern _lcd_dev lcddev; /* ����LCD��Ҫ���� */


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
void lcd_init(void);    /* lcd��ʼ������ */

void lcd_wr_data (uint16_t data);                   /* 8080д���� */
void lcd_wr_regno(volatile uint16_t regno);         /* 8080д���� */
void lcd_write_reg(uint16_t regno, uint16_t data);  /* ���Ĵ���дֵ */
uint16_t lcd_rd_data(void);                         /* 8080������ */

void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
uint16_t  lcd_read_point (uint16_t x, uint16_t y);
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);
void lcd_clear(uint16_t color);
#endif


/* 300 */














