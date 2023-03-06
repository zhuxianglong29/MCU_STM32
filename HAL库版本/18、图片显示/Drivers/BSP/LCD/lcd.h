#ifndef __LCD_H
#define __LCD_H

#include "./SYSTEM/sys/sys.h"
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uin64_t
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

/* LCD_BL�������� ����Ҫ��Ӳ������*/
//#define LCD_BL_GPIO_PORT                    GPIOB
//#define LCD_BL_GPIO_PIN                     GPIO_PIN_0
//#define LCD_BL_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/*  LCD_CS(��Ҫ����LCD_FSMC_NEX������ȷ��IO��) �� LCD_RS(��Ҫ����LCD_FSMC_AX������ȷ��IO��) ���� ���� */
/* CSƬѡ���� */
#define LCD_CS_GPIO_PORT                    GPIOG
#define LCD_CS_GPIO_PIN                     GPIO_PIN_12
#define LCD_CS_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* PG��ʱ��ʹ�� */

/* RS������������ */
#define LCD_RS_GPIO_PORT                    GPIOG
#define LCD_RS_GPIO_PIN                     GPIO_PIN_0
#define LCD_RS_GPIO_CLK_ENABLE()            do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)     /* PG��ʱ��ʹ�� */

#define TFTLCD_DIR	0	//0������  1������  Ĭ������

//TFTLCD��ַ�ṹ��
typedef struct
{
	u16 LCD_CMD;
	u16 LCD_DATA;
}TFTLCD_TypeDef;


//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������16λ����ʱSTM32�ڲ�������һλ����!			    
#define TFTLCD_BASE        ((u32)(0x6C000000 | 0x000007FE))//2046,2^10*2-2,A10
#define TFTLCD             ((TFTLCD_TypeDef *) TFTLCD_BASE)
  
//TFTLCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;            //LCD ����
}_tftlcd_data;


//LCD����
extern _tftlcd_data lcddev;	//����LCD��Ҫ����
//LCD��ǰ����ɫ�ͱ���ɫ	   
extern u16  FRONT_COLOR;//ǰ����ɫ Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ






void LCD_WriteCmd(u16 cmd);
void LCD_WriteData(u16 data);
void LCD_WriteCmdData(u16 cmd,u16 data);
void LCD_WriteData_Color(u16 color);
void TFTLCD_Init(void);           //��ʼ��
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);
void LCD_Clear(u16 Color);	 												//����
void LCD_Fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,u16 color);
void LCD_DrawPoint(u16 x,u16 y);//����
void LCD_DrawFRONT_COLOR(u16 x,u16 y,u16 color);
u16 LCD_ReadPoint(u16 x,u16 y);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawLine_Color(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn);					   						   																			
void LCD_ShowPicture(u16 x, u16 y, u16 wide, u16 high,u8 *pic);

/******************************************************************************************/

/* LCD�Ļ�����ɫ�ͱ���ɫ */
extern uint32_t  g_point_color;     /* Ĭ�Ϻ�ɫ */
extern uint32_t  g_back_color;      /* ������ɫ.Ĭ��Ϊ��ɫ */

/* LCDɨ�跽�����ɫ ���� */

/* ɨ�跽���� */
#define L2R_U2D         0           /* ������,���ϵ��� */
#define L2R_D2U         1           /* ������,���µ��� */
#define R2L_U2D         2           /* ���ҵ���,���ϵ��� */
#define R2L_D2U         3           /* ���ҵ���,���µ��� */

#define U2D_L2R         4           /* ���ϵ���,������ */
#define U2D_R2L         5           /* ���ϵ���,���ҵ��� */
#define D2U_L2R         6           /* ���µ���,������ */
#define D2U_R2L         7           /* ���µ���,���ҵ��� */

#define DFT_SCAN_DIR    L2R_U2D     /* Ĭ�ϵ�ɨ�跽�� */

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

/******************************************************************************************/
/* SSD1963������ò���(һ�㲻�ø�) */

/* LCD�ֱ������� */ 
#define SSD_HOR_RESOLUTION      800     /* LCDˮƽ�ֱ��� */ 
#define SSD_VER_RESOLUTION      480     /* LCD��ֱ�ֱ��� */ 

/* LCD������������ */ 
#define SSD_HOR_PULSE_WIDTH     1       /* ˮƽ���� */ 
#define SSD_HOR_BACK_PORCH      46      /* ˮƽǰ�� */ 
#define SSD_HOR_FRONT_PORCH     210     /* ˮƽ���� */ 

#define SSD_VER_PULSE_WIDTH     1       /* ��ֱ���� */ 
#define SSD_VER_BACK_PORCH      23      /* ��ֱǰ�� */ 
#define SSD_VER_FRONT_PORCH     22      /* ��ֱǰ�� */ 

/* ���¼����������Զ����� */ 
#define SSD_HT          (SSD_HOR_RESOLUTION + SSD_HOR_BACK_PORCH + SSD_HOR_FRONT_PORCH)
#define SSD_HPS         (SSD_HOR_BACK_PORCH)
#define SSD_VT          (SSD_VER_RESOLUTION + SSD_VER_BACK_PORCH + SSD_VER_FRONT_PORCH)
#define SSD_VPS         (SSD_VER_BACK_PORCH)

/* �������� */

void lcd_wr_data(volatile uint16_t data);            /* LCDд���� */
void lcd_wr_regno(volatile uint16_t regno);          /* LCDд�Ĵ������/��ַ */
void lcd_write_reg(uint16_t regno, uint16_t data);   /* LCDд�Ĵ�����ֵ */


void lcd_init(void);                        /* ��ʼ��LCD */ 
void lcd_display_on(void);                  /* ����ʾ */ 
void lcd_display_off(void);                 /* ����ʾ */
void lcd_scan_dir(uint8_t dir);             /* ������ɨ�跽�� */ 
void lcd_display_dir(uint8_t dir);          /* ������Ļ��ʾ���� */ 
void lcd_ssd_backlight_set(uint8_t pwm);    /* SSD1963 ������� */ 

void lcd_write_ram_prepare(void);               /* ׼��ЩGRAM */ 
void lcd_set_cursor(uint16_t x, uint16_t y);    /* ���ù�� */ 
uint32_t lcd_read_point(uint16_t x, uint16_t y);/* ����(32λ��ɫ,����LTDC)  */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color);/* ����(32λ��ɫ,����LTDC) */

void lcd_clear(uint16_t color);     /* LCD���� */
void lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);                   /* ���ʵ��Բ */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);                  /* ��Բ */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color);                  /* ��ˮƽ�� */
void lcd_set_window(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);             /* ���ô��� */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color);          /* ��ɫ������(32λ��ɫ,����LTDC) */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);   /* ��ɫ������ */
void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);     /* ��ֱ�� */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);/* ������ */


void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color);
void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color);
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color);

#endif

