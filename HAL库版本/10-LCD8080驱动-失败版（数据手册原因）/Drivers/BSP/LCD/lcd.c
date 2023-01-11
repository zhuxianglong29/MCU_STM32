#include "stdlib.h"
#include "./BSP/LCD/lcd.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LCD/lcd_ex.c"
#include "./BSP/LCD/lcdfont.h"

/* LCD�Ļ�����ɫ�ͱ���ɫ */
uint32_t g_point_color = 0XF800;    /* ������ɫ */
uint32_t g_back_color  = 0XFFFF;    /* ����ɫ */

/* ����LCD��Ҫ���� */
_lcd_dev lcddev;

/* 8080 д���� */
void lcd_wr_data (uint16_t data)
{
    LCD_RS(1);          /* �������� */
    LCD_CS(0);          /* ѡ�� */
    LCD_DATA_OUT(data); /* ���� */
    LCD_WR(0);          /* WR�͵�ƽ */
    LCD_WR(1);          /* WR�ߵ�ƽ */
    LCD_CS(1);          /* �ͷ�Ƭѡ */
}

/* 8080 д���� */
//void lcd_wr_regno(uint16_t regno)
//{
		
//    LCD_RS(0);          /* RS=0,��ʾд�Ĵ��� */
//    LCD_CS(0);          /* ѡ�� */

//    LCD_DATA_OUT(regno);/* ���� */
//    LCD_WR(0);          /* WR�͵�ƽ */
 //   LCD_WR(1);          /* WR�ߵ�ƽ */
 //   LCD_CS(1);          /* �ͷ�Ƭѡ */
//}
void lcd_wr_regno(uint16_t regno)
{
		LCD_CS(0);          /* ѡ�� */
		LCD_RS(0);          /* RS=0,��ʾд�Ĵ��� */
		LCD_WR(0);          /* WR�͵�ƽ */
    LCD_DATA_OUT(regno);/* ���� */
    LCD_WR(1);          /* WR�͵�ƽ */
    LCD_RS(1);          /* WR�ߵ�ƽ */
    LCD_CS(1);          /* �ͷ�Ƭѡ */
}

/* ���Ĵ���дֵ */
void lcd_write_reg(uint16_t regno, uint16_t data)
{
    lcd_wr_regno(regno);    /* д��Ҫд�ļĴ������ */
    lcd_wr_data(data);      /* д������ */
}

static void lcd_opt_delay(uint32_t i)
{
    while(i--);
}

/* LCD������ */
uint16_t lcd_rd_data(void)
{
    volatile uint16_t ram;  /* ��ֹ���Ż� */
    
    GPIO_InitTypeDef gpio_init_struct;
    /* LCD_DATA ����ģʽ����, ��������, ׼���������� */
    gpio_init_struct.Pin = (LCD_DATA_PD_GPIO_PIN14|LCD_DATA_PD_GPIO_PIN15|LCD_DATA_PD_GPIO_PIN0|LCD_DATA_PD_GPIO_PIN1|LCD_DATA_PD_GPIO_PIN8|LCD_DATA_PD_GPIO_PIN9|LCD_DATA_PD_GPIO_PIN10);
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_DATA_PD_GPIO_PORT, &gpio_init_struct); 
	
		gpio_init_struct.Pin = (LCD_DATA_PE_GPIO_PIN7|LCD_DATA_PE_GPIO_PIN8|LCD_DATA_PE_GPIO_PIN9|LCD_DATA_PE_GPIO_PIN10|LCD_DATA_PE_GPIO_PIN11|LCD_DATA_PE_GPIO_PIN12|LCD_DATA_PE_GPIO_PIN13|LCD_DATA_PE_GPIO_PIN14|LCD_DATA_PE_GPIO_PIN15);
     HAL_GPIO_Init(LCD_DATA_PE_GPIO_PORT, &gpio_init_struct); 
/*
    LCD_RS(1);            
    LCD_CS(0);
    LCD_RD(0);
    lcd_opt_delay(2);
    ram = LCD_DATA_IN;     
	//printf("ram:%#x \r\n",ram);
    LCD_RD(1);
    LCD_CS(1);
*/  
		LCD_CS(0);
		
		LCD_RD(0); 
	 		       
    lcd_opt_delay(2);
/*
	ram=(TFTLCD->LCD_DATA)>>1;
	ram=ram<<8;
	ram|=(TFTLCD->LCD_DATA)>>1;
*/	
    ram = LCD_DATA_IN>>1; 
		ram=ram<<8;
		ram|=LCD_DATA_IN>>1;
	  LCD_RD(1);
    LCD_CS(1);

    /* LCD_DATA ����ģʽ����, �������, �ָ����״̬ */	
		gpio_init_struct.Pin = (LCD_DATA_PD_GPIO_PIN14|LCD_DATA_PD_GPIO_PIN15|LCD_DATA_PD_GPIO_PIN0|LCD_DATA_PD_GPIO_PIN1|LCD_DATA_PD_GPIO_PIN8|LCD_DATA_PD_GPIO_PIN9|LCD_DATA_PD_GPIO_PIN10);
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_DATA_PD_GPIO_PORT, &gpio_init_struct); 
	
		gpio_init_struct.Pin = (LCD_DATA_PE_GPIO_PIN7|LCD_DATA_PE_GPIO_PIN8|LCD_DATA_PE_GPIO_PIN9|LCD_DATA_PE_GPIO_PIN10|LCD_DATA_PE_GPIO_PIN11|LCD_DATA_PE_GPIO_PIN12|LCD_DATA_PE_GPIO_PIN13|LCD_DATA_PE_GPIO_PIN14|LCD_DATA_PE_GPIO_PIN15);
    HAL_GPIO_Init(LCD_DATA_PE_GPIO_PORT, &gpio_init_struct); 


    return ram;
}

/* ׼��дGRAM */
void lcd_write_ram_prepare(void)
{
    lcd_wr_regno(lcddev.wramcmd);
}

/* �������� */
void lcd_set_cursor(uint16_t x, uint16_t y)
{
    lcd_wr_regno(lcddev.setxcmd);
    lcd_wr_data(x >> 8);
    lcd_wr_data(x & 0xFF);
    lcd_wr_regno(lcddev.setycmd);
    lcd_wr_data(y >> 8);
    lcd_wr_data(y & 0xFF);
}

/* ���� */
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    lcd_set_cursor(x, y);
    lcd_write_ram_prepare();
    lcd_wr_data(color);
}

/* ���� */
uint16_t  lcd_read_point (uint16_t x, uint16_t y)
{
    uint16_t r = 0, g = 0, b = 0;   /* ������� */
    
    lcd_set_cursor(x, y);           /* �������� */
    lcd_wr_regno(0X2E);             /* ���������� */
    r = lcd_rd_data();              /* �ٶ� */
    r = lcd_rd_data();              /* ��rg */
    b = lcd_rd_data();              /* ��b */
    g = r & 0XFF;                   /* �õ�gֵ */
    return (((r >> 11) << 11) | ((g >> 2) << 5) | (b >> 11));
}

void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t t, t1, temp;
    uint8_t *pfont = NULL;
    uint8_t csize = (size / 8+((size % 8) ? 1 : 0)) * (size / 2);
    chr = chr - ' ';
    uint16_t y0 = y;
    
    switch(size)
    {
        case 12:
            pfont = (uint8_t *)asc2_1206[chr];  /* ����1206���� */
            break;

        case 16:
            pfont = (uint8_t *)asc2_1608[chr];  /* ����1608���� */
            break;

        case 24:
            pfont = (uint8_t *)asc2_2412[chr];  /* ����2412���� */
            break;

        case 32:
            pfont = (uint8_t *)asc2_3216[chr];  /* ����3216���� */
            break;

        default:
            return ;
    }
    
    for (t = 0; t < csize; t++)
    {
        temp = pfont[t];
        
        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80)
            {
                lcd_draw_point(x, y, color);
            }
            else if (mode == 0)
            {
                lcd_draw_point(x, y, g_back_color);
            }
            
            temp <<= 1;
            y++;
            
            if ((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
        
    }

}


void lcd_clear(uint16_t color)
{
    uint32_t index = 0;
    uint32_t totalpoint = lcddev.width;
    
    totalpoint *= lcddev.height;    /* �õ��ܵ��� */
    lcd_set_cursor(0, 0);   /* ���ù��λ�� */
    lcd_write_ram_prepare();        /* ��ʼд��GRAM */

    LCD_RS(1);                      /* RS=1,��ʾд���� */
    LCD_CS(0);
    
    for (index = 0; index < totalpoint; index++)
    {
        LCD_DATA_OUT(color);        /* д��Ҫд������ */
        LCD_WR(0);
        LCD_WR(1);
    }
    
    LCD_CS(1);
}

/* ��ʼ��LCD */
void lcd_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    LCD_BL_GPIO_CLK_ENABLE();   /* LCD_BL��ʱ��ʹ�� */
    LCD_CS_GPIO_CLK_ENABLE();   /* LCD_CS��ʱ��ʹ�� */
    LCD_WR_GPIO_CLK_ENABLE();   /* LCD_WR��ʱ��ʹ�� */
    LCD_RD_GPIO_CLK_ENABLE();   /* LCD_RD��ʱ��ʹ�� */
    LCD_RS_GPIO_CLK_ENABLE();   /* LCD_RS��ʱ��ʹ�� */
	
    LCD_DATA_PD_GPIO_CLK_ENABLE() ;
	  LCD_DATA_PE_GPIO_CLK_ENABLE() ; /* LCD_DATA��ʱ��ʹ�� */
    __HAL_RCC_AFIO_CLK_ENABLE();
    //__HAL_AFIO_REMAP_SWJ_NOJTAG(); /* ��ֹJTAG, ʹ��SWD, �ͷ�PB3,PB4������������ͨIO�� */
    
    gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ���츴�� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpio_init_struct);     /* LCD_BL����ģʽ����(�������) */

    gpio_init_struct.Pin = LCD_CS_GPIO_PIN;
    HAL_GPIO_Init(LCD_CS_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_CS���� */

    gpio_init_struct.Pin = LCD_WR_GPIO_PIN;
    HAL_GPIO_Init(LCD_WR_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_WR���� */

    gpio_init_struct.Pin = LCD_RD_GPIO_PIN;
    HAL_GPIO_Init(LCD_RD_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_RD���� */

    gpio_init_struct.Pin = LCD_RS_GPIO_PIN;
    HAL_GPIO_Init(LCD_RS_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_RS���� */

     /* ������� */
     /* LCD_DATA����ģʽ���� */	
		gpio_init_struct.Pin = (LCD_DATA_PD_GPIO_PIN14|LCD_DATA_PD_GPIO_PIN15|LCD_DATA_PD_GPIO_PIN0|LCD_DATA_PD_GPIO_PIN1|LCD_DATA_PD_GPIO_PIN8|LCD_DATA_PD_GPIO_PIN9|LCD_DATA_PD_GPIO_PIN10);
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(LCD_DATA_PD_GPIO_PORT, &gpio_init_struct); 
		gpio_init_struct.Pin = (LCD_DATA_PE_GPIO_PIN7|LCD_DATA_PE_GPIO_PIN8|LCD_DATA_PE_GPIO_PIN9|LCD_DATA_PE_GPIO_PIN10|LCD_DATA_PE_GPIO_PIN11|LCD_DATA_PE_GPIO_PIN12|LCD_DATA_PE_GPIO_PIN13|LCD_DATA_PE_GPIO_PIN14|LCD_DATA_PE_GPIO_PIN15);
    HAL_GPIO_Init(LCD_DATA_PE_GPIO_PORT, &gpio_init_struct); 
    
    LCD_WR(1);                  /* WR Ĭ�ϸߵ�ƽ */
    LCD_RD(1);                  /* RD Ĭ�ϸߵ�ƽ */
    LCD_CS(1);                  /* CS Ĭ�ϸߵ�ƽ */
    LCD_RS(1);                  /* RS Ĭ�ϸߵ�ƽ */
    LCD_DATA_OUT(0XFFFF);       /* DATA Ĭ�ϸߵ�ƽ */

    /* ��ȡID */
		uint16_t regno=0x8000;
		uint16_t testout;
		testout=regno&0x8000;
		printf("testout:%#x \r\n",testout);
		if(testout==0x8000)
			printf("test ok\r\n");
		
    lcd_wr_regno(0x0000);
    lcddev.id = lcd_rd_data();  /* �ٶ� */
		printf("lcddev_id1:%#x \r\n", lcddev.id);
    lcddev.id = lcd_rd_data();  /* 00 */
		printf("lcddev_id2:%#x \r\n", lcddev.id);
    lcddev.id = lcd_rd_data();  /* 93 */
    lcddev.id <<= 8;
    lcddev.id |= lcd_rd_data();  /* 41 */
    
    printf("lcddev_id3:%#x \r\n", lcddev.id);
    
    /* ��ɳ�ʼ������ */
    if (lcddev.id == 0x9341)
        lcd_ex_ili9341_reginit();
    else
        lcd_ex_st7789_reginit();
    
    /* ��LCD���ƽṹ�帳ֵ */
    lcddev.width = 240;
    lcddev.height = 320;
    lcddev.setxcmd = 0x2A;
    lcddev.setycmd = 0x2B;
    lcddev.wramcmd = 0x2C;
    
    lcd_wr_regno(lcddev.setxcmd);
    lcd_wr_data(0);
    lcd_wr_data(0);
    lcd_wr_data((lcddev.width - 1) >> 8);
    lcd_wr_data((lcddev.width - 1) & 0XFF);
    lcd_wr_regno(lcddev.setycmd);
    lcd_wr_data(0);
    lcd_wr_data(0);
    lcd_wr_data((lcddev.height - 1) >> 8);
    lcd_wr_data((lcddev.height - 1) & 0XFF);
    
    /* ����ɨ�跽�� */
    lcd_write_reg(0x36, 1 << 3);
    
    /* �������� */
    LCD_BL(1);
    
    /* lcd_clear */
    lcd_clear(0xFFFF);
}






