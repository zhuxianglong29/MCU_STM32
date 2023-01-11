#include "stdlib.h"
#include "./BSP/LCD/lcd.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LCD/lcd_ex.c"
#include "./BSP/LCD/lcdfont.h"

/* LCD的画笔颜色和背景色 */
uint32_t g_point_color = 0XF800;    /* 画笔颜色 */
uint32_t g_back_color  = 0XFFFF;    /* 背景色 */

/* 管理LCD重要参数 */
_lcd_dev lcddev;

/* 8080 写数据 */
void lcd_wr_data (uint16_t data)
{
    LCD_RS(1);          /* 操作数据 */
    LCD_CS(0);          /* 选中 */
    LCD_DATA_OUT(data); /* 数据 */
    LCD_WR(0);          /* WR低电平 */
    LCD_WR(1);          /* WR高电平 */
    LCD_CS(1);          /* 释放片选 */
}

/* 8080 写命令 */
//void lcd_wr_regno(uint16_t regno)
//{
		
//    LCD_RS(0);          /* RS=0,表示写寄存器 */
//    LCD_CS(0);          /* 选中 */

//    LCD_DATA_OUT(regno);/* 命令 */
//    LCD_WR(0);          /* WR低电平 */
 //   LCD_WR(1);          /* WR高电平 */
 //   LCD_CS(1);          /* 释放片选 */
//}
void lcd_wr_regno(uint16_t regno)
{
		LCD_CS(0);          /* 选中 */
		LCD_RS(0);          /* RS=0,表示写寄存器 */
		LCD_WR(0);          /* WR低电平 */
    LCD_DATA_OUT(regno);/* 命令 */
    LCD_WR(1);          /* WR低电平 */
    LCD_RS(1);          /* WR高电平 */
    LCD_CS(1);          /* 释放片选 */
}

/* 往寄存器写值 */
void lcd_write_reg(uint16_t regno, uint16_t data)
{
    lcd_wr_regno(regno);    /* 写入要写的寄存器序号 */
    lcd_wr_data(data);      /* 写入数据 */
}

static void lcd_opt_delay(uint32_t i)
{
    while(i--);
}

/* LCD读数据 */
uint16_t lcd_rd_data(void)
{
    volatile uint16_t ram;  /* 防止被优化 */
    
    GPIO_InitTypeDef gpio_init_struct;
    /* LCD_DATA 引脚模式设置, 上拉输入, 准备接收数据 */
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

    /* LCD_DATA 引脚模式设置, 推挽输出, 恢复输出状态 */	
		gpio_init_struct.Pin = (LCD_DATA_PD_GPIO_PIN14|LCD_DATA_PD_GPIO_PIN15|LCD_DATA_PD_GPIO_PIN0|LCD_DATA_PD_GPIO_PIN1|LCD_DATA_PD_GPIO_PIN8|LCD_DATA_PD_GPIO_PIN9|LCD_DATA_PD_GPIO_PIN10);
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_DATA_PD_GPIO_PORT, &gpio_init_struct); 
	
		gpio_init_struct.Pin = (LCD_DATA_PE_GPIO_PIN7|LCD_DATA_PE_GPIO_PIN8|LCD_DATA_PE_GPIO_PIN9|LCD_DATA_PE_GPIO_PIN10|LCD_DATA_PE_GPIO_PIN11|LCD_DATA_PE_GPIO_PIN12|LCD_DATA_PE_GPIO_PIN13|LCD_DATA_PE_GPIO_PIN14|LCD_DATA_PE_GPIO_PIN15);
    HAL_GPIO_Init(LCD_DATA_PE_GPIO_PORT, &gpio_init_struct); 


    return ram;
}

/* 准备写GRAM */
void lcd_write_ram_prepare(void)
{
    lcd_wr_regno(lcddev.wramcmd);
}

/* 设置坐标 */
void lcd_set_cursor(uint16_t x, uint16_t y)
{
    lcd_wr_regno(lcddev.setxcmd);
    lcd_wr_data(x >> 8);
    lcd_wr_data(x & 0xFF);
    lcd_wr_regno(lcddev.setycmd);
    lcd_wr_data(y >> 8);
    lcd_wr_data(y & 0xFF);
}

/* 画点 */
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    lcd_set_cursor(x, y);
    lcd_write_ram_prepare();
    lcd_wr_data(color);
}

/* 读点 */
uint16_t  lcd_read_point (uint16_t x, uint16_t y)
{
    uint16_t r = 0, g = 0, b = 0;   /* 定义变量 */
    
    lcd_set_cursor(x, y);           /* 设置坐标 */
    lcd_wr_regno(0X2E);             /* 发读点命令 */
    r = lcd_rd_data();              /* 假读 */
    r = lcd_rd_data();              /* 读rg */
    b = lcd_rd_data();              /* 读b */
    g = r & 0XFF;                   /* 得到g值 */
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
            pfont = (uint8_t *)asc2_1206[chr];  /* 调用1206字体 */
            break;

        case 16:
            pfont = (uint8_t *)asc2_1608[chr];  /* 调用1608字体 */
            break;

        case 24:
            pfont = (uint8_t *)asc2_2412[chr];  /* 调用2412字体 */
            break;

        case 32:
            pfont = (uint8_t *)asc2_3216[chr];  /* 调用3216字体 */
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
    
    totalpoint *= lcddev.height;    /* 得到总点数 */
    lcd_set_cursor(0, 0);   /* 设置光标位置 */
    lcd_write_ram_prepare();        /* 开始写入GRAM */

    LCD_RS(1);                      /* RS=1,表示写数据 */
    LCD_CS(0);
    
    for (index = 0; index < totalpoint; index++)
    {
        LCD_DATA_OUT(color);        /* 写入要写的数据 */
        LCD_WR(0);
        LCD_WR(1);
    }
    
    LCD_CS(1);
}

/* 初始化LCD */
void lcd_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    LCD_BL_GPIO_CLK_ENABLE();   /* LCD_BL脚时钟使能 */
    LCD_CS_GPIO_CLK_ENABLE();   /* LCD_CS脚时钟使能 */
    LCD_WR_GPIO_CLK_ENABLE();   /* LCD_WR脚时钟使能 */
    LCD_RD_GPIO_CLK_ENABLE();   /* LCD_RD脚时钟使能 */
    LCD_RS_GPIO_CLK_ENABLE();   /* LCD_RS脚时钟使能 */
	
    LCD_DATA_PD_GPIO_CLK_ENABLE() ;
	  LCD_DATA_PE_GPIO_CLK_ENABLE() ; /* LCD_DATA脚时钟使能 */
    __HAL_RCC_AFIO_CLK_ENABLE();
    //__HAL_AFIO_REMAP_SWJ_NOJTAG(); /* 禁止JTAG, 使能SWD, 释放PB3,PB4两个引脚做普通IO用 */
    
    gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽复用 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpio_init_struct);     /* LCD_BL引脚模式设置(推挽输出) */

    gpio_init_struct.Pin = LCD_CS_GPIO_PIN;
    HAL_GPIO_Init(LCD_CS_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_CS引脚 */

    gpio_init_struct.Pin = LCD_WR_GPIO_PIN;
    HAL_GPIO_Init(LCD_WR_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_WR引脚 */

    gpio_init_struct.Pin = LCD_RD_GPIO_PIN;
    HAL_GPIO_Init(LCD_RD_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_RD引脚 */

    gpio_init_struct.Pin = LCD_RS_GPIO_PIN;
    HAL_GPIO_Init(LCD_RS_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_RS引脚 */

     /* 推挽输出 */
     /* LCD_DATA引脚模式设置 */	
		gpio_init_struct.Pin = (LCD_DATA_PD_GPIO_PIN14|LCD_DATA_PD_GPIO_PIN15|LCD_DATA_PD_GPIO_PIN0|LCD_DATA_PD_GPIO_PIN1|LCD_DATA_PD_GPIO_PIN8|LCD_DATA_PD_GPIO_PIN9|LCD_DATA_PD_GPIO_PIN10);
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(LCD_DATA_PD_GPIO_PORT, &gpio_init_struct); 
		gpio_init_struct.Pin = (LCD_DATA_PE_GPIO_PIN7|LCD_DATA_PE_GPIO_PIN8|LCD_DATA_PE_GPIO_PIN9|LCD_DATA_PE_GPIO_PIN10|LCD_DATA_PE_GPIO_PIN11|LCD_DATA_PE_GPIO_PIN12|LCD_DATA_PE_GPIO_PIN13|LCD_DATA_PE_GPIO_PIN14|LCD_DATA_PE_GPIO_PIN15);
    HAL_GPIO_Init(LCD_DATA_PE_GPIO_PORT, &gpio_init_struct); 
    
    LCD_WR(1);                  /* WR 默认高电平 */
    LCD_RD(1);                  /* RD 默认高电平 */
    LCD_CS(1);                  /* CS 默认高电平 */
    LCD_RS(1);                  /* RS 默认高电平 */
    LCD_DATA_OUT(0XFFFF);       /* DATA 默认高电平 */

    /* 读取ID */
		uint16_t regno=0x8000;
		uint16_t testout;
		testout=regno&0x8000;
		printf("testout:%#x \r\n",testout);
		if(testout==0x8000)
			printf("test ok\r\n");
		
    lcd_wr_regno(0x0000);
    lcddev.id = lcd_rd_data();  /* 假读 */
		printf("lcddev_id1:%#x \r\n", lcddev.id);
    lcddev.id = lcd_rd_data();  /* 00 */
		printf("lcddev_id2:%#x \r\n", lcddev.id);
    lcddev.id = lcd_rd_data();  /* 93 */
    lcddev.id <<= 8;
    lcddev.id |= lcd_rd_data();  /* 41 */
    
    printf("lcddev_id3:%#x \r\n", lcddev.id);
    
    /* 完成初始化序列 */
    if (lcddev.id == 0x9341)
        lcd_ex_ili9341_reginit();
    else
        lcd_ex_st7789_reginit();
    
    /* 对LCD控制结构体赋值 */
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
    
    /* 设置扫描方向 */
    lcd_write_reg(0x36, 1 << 3);
    
    /* 点亮背光 */
    LCD_BL(1);
    
    /* lcd_clear */
    lcd_clear(0xFFFF);
}






