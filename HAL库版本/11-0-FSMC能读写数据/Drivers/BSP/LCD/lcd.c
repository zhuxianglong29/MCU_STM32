#include "./BSP/LCD/lcd.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LCD/lcd_ex.c"

SRAM_HandleTypeDef g_sram_handle;    /* SRAM���(���ڿ���LCD) */

/* LCD�Ļ�����ɫ�ͱ���ɫ */
uint32_t g_point_color = 0XF800;    /* ������ɫ */
uint32_t g_back_color  = 0XFFFF;    /* ����ɫ */


/* ����LCD��Ҫ���� */
_lcd_dev lcddev;

/* д���� */
void lcd_wr_regno(volatile uint16_t cmd)
{
    cmd =( cmd>>8)<<1;
    *(uint16_t *)(FSMC_ADDR_CMD) = cmd;
		*(uint16_t *)(FSMC_ADDR_CMD) =(cmd&0xff)<<1;
}

/* д���� */
void lcd_wr_data(volatile uint16_t data)
{
    data = data;
    *(uint16_t *)(FSMC_ADDR_DATA) = data;
}

/* д�Ĵ��� */
void lcd_write_reg(uint16_t regno, uint16_t data)
{
    lcd_wr_regno(regno);
    lcd_wr_data(data);
}



/* ������ */
uint16_t lcd_rd_data(void)
{
    volatile uint16_t ram;
	//ram = *(uint16_t *)(FSMC_ADDR_DATA);
  ram = (*(uint16_t *)(FSMC_ADDR_DATA))>>1;
	ram=ram<<8;
	ram|=(*(uint16_t *)(FSMC_ADDR_DATA))>>1;
		
    return ram;
}

/* �������� */
void lcd_set_cursor(uint16_t x, uint16_t y)
{
    lcd_wr_regno(0x2A);
    lcd_wr_data(x >> 8);
    lcd_wr_data(x & 0XFF);
    lcd_wr_regno(0x2B);
    lcd_wr_data(y >> 8);
    lcd_wr_data(y & 0XFF);
}

/* ׼��дGRAM */
void lcd_write_ram_prepare(void)
{
    lcd_wr_regno(0x2C);
}

/* ���� */
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    lcd_set_cursor(x, y);
    lcd_write_ram_prepare();
    lcd_wr_data(color);
}

/* ���� */
uint16_t lcd_read_point (uint16_t x, uint16_t y)
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

/* lcd�������� */
void lcd_clear(uint16_t color)
{
    uint16_t i, j ;

	LCD_Set_Window(0, 0, lcddev.width-1, lcddev.height-1);	 //��������
  	for(i=0; i<lcddev.width; i++)
	{
		for (j=0; j<lcddev.height; j++)
		{
			LCD_WriteData_Color(color);
		}
	} 
}


void lcd_init(void)
{
    FSMC_NORSRAM_TimingTypeDef fsmc_read_handle;
    FSMC_NORSRAM_TimingTypeDef fsmc_write_handle;
    
    /* FSMC���ƵĶ��� */
    g_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
    g_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    
    g_sram_handle.Init.NSBank               = FSMC_NORSRAM_BANK4;               /* NOR/PSRAM�洢���е�BANK4 */
    g_sram_handle.Init.DataAddressMux       = FSMC_DATA_ADDRESS_MUX_DISABLE;    /* �����ߺ͵�ַ�߲����� */
    g_sram_handle.Init.MemoryType           = FSMC_MEMORY_TYPE_SRAM;            /* �洢������ SRAM */
    g_sram_handle.Init.MemoryDataWidth      = FSMC_NORSRAM_MEM_BUS_WIDTH_16;    /* �洢�����ݿ�� 16λ */
    g_sram_handle.Init.BurstAccessMode      = FSMC_BURST_ACCESS_MODE_DISABLE;   /* �Ƿ�ʹ��ͻ�����ʣ�����ͬ��ͻ���洢����Ч �˴�δ�õ� */
    g_sram_handle.Init.WaitSignalPolarity   = FSMC_WAIT_SIGNAL_POLARITY_LOW;    /* �ȴ��źŵļ���,����ͻ��ģʽ���������� */
    g_sram_handle.Init.WaitSignalActive     = FSMC_WAIT_TIMING_BEFORE_WS;       /* �洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT */
    g_sram_handle.Init.WriteOperation       = FSMC_WRITE_OPERATION_ENABLE;      /* �洢��дʹ�� */
    g_sram_handle.Init.WaitSignal           = FSMC_WAIT_SIGNAL_DISABLE;         /* �ȴ�ʹ��λ,�˴�δ�õ� */
    g_sram_handle.Init.ExtendedMode         = FSMC_EXTENDED_MODE_ENABLE;        /* ��дʹ�ò�ͬ��ʱ�� */
    g_sram_handle.Init.AsynchronousWait     = FSMC_ASYNCHRONOUS_WAIT_DISABLE;   /* �Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ� */
    g_sram_handle.Init.WriteBurst           = FSMC_WRITE_BURST_DISABLE;         /* ��ֹͻ��д */

    /* FSMC��ʱ����ƼĴ��� */
    fsmc_read_handle.AccessMode         = FSMC_ACCESS_MODE_A;    /* ģʽA */
    fsmc_read_handle.AddressSetupTime   = 1;        /* ��ַ����ʱ��(ADDSET)Ϊ2��HCLK 1/72M = 13.9ns * 2 = 27.8ns (ʵ�� > 200ns) */
    fsmc_read_handle.AddressHoldTime    = 0;        /* ��ַ����ʱ��(ADDHLD) ģʽA��û���õ� */
    /* ��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫��,�����Ǹ�������оƬ */
    fsmc_read_handle.DataSetupTime      = 15;       /* ���ݱ���ʱ��(DATAST)Ϊ16��HCLK = 13.9 * 16 = 222.4ns */

    /* FSMCдʱ����ƼĴ��� ����һ�� */
    fsmc_write_handle.AccessMode        = FSMC_ACCESS_MODE_A;   /* ģʽA */
    fsmc_write_handle.AddressSetupTime  = 15;        /*1 ��ַ����ʱ��(ADDSET)Ϊ2��HCLK = 27.8 ns */
    fsmc_write_handle.AddressHoldTime   = 15;        /* ��ַ����ʱ��(ADDHLD) ģʽA��û���õ� */
    /* ĳЩҺ������IC��д�ź���������Ҳ��50ns�� */
    fsmc_write_handle.DataSetupTime     = 5;        /*3 ���ݱ���ʱ��(DATAST)Ϊ4��HCLK = 13.9 * 4 = 55.6ns (ʵ�� > 200ns) */
    
    HAL_SRAM_Init(&g_sram_handle, &fsmc_read_handle, &fsmc_write_handle);
    delay_ms(50);

    /* ��ȡID */
    lcd_wr_regno(0x0000);
    lcddev.id = lcd_rd_data();  /* ��ID */
		printf("lcddev_id1:%#x \r\n", lcddev.id);
    lcddev.id = lcd_rd_data();  /* 00 */
		
    
    /* ��ɳ�ʼ������ */
    if (lcddev.id == 0xb509)
        lcd_ex_b509_reginit();
    
    
    /* ��LCD���ƽṹ�帳ֵ */
    lcddev.width = 240;
    lcddev.height = 400;
  //  lcddev.setxcmd = 0x2A;
  //  lcddev.setycmd = 0x2B;
   // lcddev.wramcmd = 0x2C;
    
   // lcd_wr_regno(lcddev.setxcmd);
   // lcd_wr_data(0);
   // lcd_wr_data(0);
   // lcd_wr_data((lcddev.width - 1) >> 8);
   // lcd_wr_data((lcddev.width - 1) & 0XFF);
   // lcd_wr_regno(lcddev.setycmd);
   // lcd_wr_data(0);
   // lcd_wr_data(0);
   // lcd_wr_data((lcddev.height - 1) >> 8);
    //lcd_wr_data((lcddev.height - 1) & 0XFF);
    
    /* ����ɨ�跽�� */
    lcd_wr_regno(0x0001);   
		lcd_wr_data(0x0100);
		lcd_wr_regno(0x0003);
		lcd_wr_data(0x1030);
    
    /* �������� */
    //LCD_BL(1);
    
    /* lcd_clear */
    lcd_clear(0xFFFF);
}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_FSMC_CLK_ENABLE();            /* ʹ��FSMCʱ�� */
    __HAL_RCC_GPIOD_CLK_ENABLE();           /* ʹ��GPIODʱ�� */
    __HAL_RCC_GPIOE_CLK_ENABLE();           /* ʹ��GPIOEʱ�� */
    
    LCD_WR_GPIO_CLK_ENABLE();
    LCD_RD_GPIO_CLK_ENABLE();
    LCD_BL_GPIO_CLK_ENABLE();
    LCD_CS_GPIO_CLK_ENABLE();
    LCD_RS_GPIO_CLK_ENABLE();
    
    gpio_init_struct.Pin = LCD_CS_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ���츴�� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(LCD_CS_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_CS���� */
    
    gpio_init_struct.Pin = LCD_WR_GPIO_PIN;
    HAL_GPIO_Init(LCD_WR_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_WR���� */

    gpio_init_struct.Pin = LCD_RD_GPIO_PIN;
    HAL_GPIO_Init(LCD_RD_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_RD���� */

    gpio_init_struct.Pin = LCD_RS_GPIO_PIN;
    HAL_GPIO_Init(LCD_RS_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_RS���� */
    
    gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpio_init_struct);     /* LCD_BL����ģʽ����(�������) */
    
    /* �����߳�ʼ�� */
    /* ��ʼ��PD0,1,8,9,10,14,15 */
    gpio_init_struct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 \
                           | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                  /* ���츴�� */
    gpio_init_struct.Pull = GPIO_PULLUP;                      /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;            /* ���� */
    HAL_GPIO_Init(GPIOD, &gpio_init_struct);                  /* ��ʼ�� */

    /* ��ʼ��PE7,8,9,10,11,12,13,14,15 */
    gpio_init_struct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 \
                           | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);
}


void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	lcd_wr_regno(0x0210);   
	    lcd_wr_data(sx);
		lcd_wr_regno(0x0211);  
	    lcd_wr_data(width);
		lcd_wr_regno(0x0212);   
	    lcd_wr_data(sy);
		lcd_wr_regno(0x0213);   
	    lcd_wr_data(height);
	
		lcd_wr_regno(0x0200);   
	    lcd_wr_data(sx);
		lcd_wr_regno(0x0201);   
	    lcd_wr_data(sy);	
	lcd_wr_regno(0x0202);
}


void LCD_WriteData_Color(uint16_t color)
{
	uint32_t recolor=0;
			recolor=LCD_RGBColor_Change(color);
			*(uint16_t *)(FSMC_ADDR_DATA)=(recolor>>9);
			*(uint16_t *)(FSMC_ADDR_DATA)=recolor;
}

uint32_t LCD_RGBColor_Change(uint16_t color)
{
	uint8_t r,g,b=0;
	
	r=(color>>11)&0x1f;
	g=(color>>5)&0x3f;
	b=color&0x1f;
	
	return ((r<<13)|(g<<6)|(b<<1));
}
