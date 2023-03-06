#include "./BSP/LCD/lcd.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
//#include "./BSP/LCD/lcd_ex.c"
#include "./BSP/LCD/lcdfont.h"

SRAM_HandleTypeDef g_sram_handle;    /* SRAM���(���ڿ���LCD) */

/* LCD�Ļ�����ɫ�ͱ���ɫ */
uint32_t g_point_color = 0XF800;    /* ������ɫ */
uint32_t g_back_color  = 0XFFFF;    /* ����ɫ */

_tftlcd_data tftlcd_data; 





/**
 * @brief       LCDд����
 * @param       data: Ҫд�������
 * @retval      ��
 */
void lcd_wr_data(volatile uint16_t data)
{
   TFTLCD->LCD_DATA=(data>>8)<<1;
	 TFTLCD->LCD_DATA=(data&0xff)<<1;	
}

/**
 * @brief       LCDд�Ĵ������/��ַ����
 * @param       regno: �Ĵ������/��ַ
 * @retval      ��
 */
void lcd_wr_regno(volatile uint16_t regno)
{
    	TFTLCD->LCD_CMD=(regno>>8)<<1;
			TFTLCD->LCD_CMD=(regno&0xff)<<1;
}

/**
 * @brief       LCDд�Ĵ���
 * @param       regno:�Ĵ������/��ַ
 * @param       data:Ҫд�������
 * @retval      ��
 */
void lcd_write_reg(uint16_t regno, uint16_t data)
{
   TFTLCD->LCD_DATA=(data>>8)<<1;
	 TFTLCD->LCD_DATA=(data&0xff)<<1;	
	 TFTLCD->LCD_CMD=(regno>>8)<<1;
	 TFTLCD->LCD_CMD=(regno&0xff)<<1;
}

/**
 * @brief       LCD��ʱ����,�����ڲ�����mdk -O1ʱ���Ż�ʱ��Ҫ���õĵط�
 * @param       t:��ʱ����ֵ
 * @retval      ��
 */


/**
 * @brief       LCD������
 * @param       ��
 * @retval      ��ȡ��������
 */
static uint16_t lcd_rd_data(void)
{
   u16 ram;		
	ram=(TFTLCD->LCD_DATA)>>1;
	ram=ram<<8;
	ram|=(TFTLCD->LCD_DATA)>>1;	
	return ram;	
}


/**
 * @brief       ��ȡ��ĳ�����ɫֵ
 * @param       x,y:����
 * @retval      �˵����ɫ(32λ��ɫ,�������LTDC)
 */
uint32_t lcd_read_point(uint16_t x, uint16_t y)
{
	 	u16 r=0;
	u16 r1,r2,r3;
	u32 value;
	
	if(x>=tftlcd_data.width||y>=tftlcd_data.height)return 0;	//�����˷�Χ,ֱ�ӷ���		     
	lcd_set_window(x, y, x, y);
	lcd_wr_regno(0X0202);
	
	value=TFTLCD->LCD_DATA;
	value=value<<9;
	value|=TFTLCD->LCD_DATA;
	
	value=TFTLCD->LCD_DATA;
	value=value<<9;
	value|=TFTLCD->LCD_DATA;
//	printf("value=%X\r\n",value);
	r1=value>>13;
	r2=(value>>6)&0x3f;
	r3=(value>>1)&0x1f;	
	r=(r1<<11)|(r2<<5)|r3;
//	printf("r=%X\r\n",r);
	return r;
}




//����LCD��ʾ����
//dir:0,������1,����
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)  //Ĭ����������
	{		
		lcd_wr_regno(0x0001);   
		lcd_wr_data(0x0100);
		lcd_wr_regno(0x0003);
		lcd_wr_data(0x1030);
		tftlcd_data.height=400;
		tftlcd_data.width=240;
	}
	else
	{	
		lcd_wr_regno(0x0001);   
		lcd_wr_data(0x0100);	//����ͷ��Ҫ������������Ϊ0x0100������0x0000
		lcd_wr_regno(0x0003);
		lcd_wr_data(0x1038);
		tftlcd_data.height=240;
		tftlcd_data.width=400;
		tftlcd_data.dir=1;
	}
}		




u32 LCD_RGBColor_Change(u16 color)
{
	u8 r,g,b=0;
	
	r=(color>>11)&0x1f;
	g=(color>>5)&0x3f;
	b=color&0x1f;
	
	return ((r<<13)|(g<<6)|(b<<1));
}

void LCD_WriteData_Color(u16 color)
{
	u32 recolor=0;
			recolor=LCD_RGBColor_Change(color);
			TFTLCD->LCD_DATA=(recolor>>9);
			TFTLCD->LCD_DATA=recolor;
}


/**
 * @brief       ����
 * @param       x,y: ����
 * @param       color: �����ɫ(32λ��ɫ,�������LTDC)
 * @retval      ��
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
		lcd_set_window(x, y, x, y);  //���õ��λ��
    LCD_WriteData_Color(color);
}

//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height. 
void lcd_set_window(u16 sx,u16 sy,u16 width,u16 height)
{
	if(tftlcd_data.dir==0)
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
	}   	
	else
	{
		lcd_wr_regno(0x0212);   
	    lcd_wr_data(sx);
		lcd_wr_regno(0x0213);  
	    lcd_wr_data(width);
		lcd_wr_regno(0x0210);   
	    lcd_wr_data(sy);
		lcd_wr_regno(0x0211);   
	    lcd_wr_data(height);
	
		lcd_wr_regno(0x0201);   
	    lcd_wr_data(sx);
		lcd_wr_regno(0x0200);   
	    lcd_wr_data(sy);	
	}
	lcd_wr_regno(0x0202);
}





//��������
//color:Ҫ���������ɫ
void lcd_clear(u16 color)
{
	uint16_t i, j ;

	lcd_set_window(0, 0, tftlcd_data.width-1, tftlcd_data.height-1);	 //��������
  	for(i=0; i<tftlcd_data.width; i++)
	{
		for (j=0; j<tftlcd_data.height; j++)
		{
			LCD_WriteData_Color(color);
		}
	} 
}


//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void lcd_fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,uint32_t color)
{          
	uint16_t temp;

    if((xState > xEnd) || (yState > yEnd))
    {
        return;
    }   
	lcd_set_window(xState, yState, xEnd, yEnd); 
    xState = xEnd - xState + 1;
	yState = yEnd - yState + 1;

	while(xState--)
	{
	 	temp = yState;
		while (temp--)
	 	{			
			LCD_WriteData_Color(color);	
		}
	}	
} 




/**
 * @brief       ����
 * @param       x1,y1: �������
 * @param       x2,y2: �յ�����
 * @param       color: �ߵ���ɫ
 * @retval      ��
 */
void lcd_draw_line(u16 x1, u16 y1, u16 x2, u16 y2,uint16_t color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		lcd_draw_point(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

/**
 * @brief       ������
 * @param       x1,y1: �������
 * @param       x2,y2: �յ�����
 * @param       color: ���ε���ɫ
 * @retval      ��
 */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    lcd_draw_line(x1, y1, x2, y1, color);
    lcd_draw_line(x1, y1, x1, y2, color);
    lcd_draw_line(x1, y2, x2, y2, color);
    lcd_draw_line(x2, y1, x2, y2, color);
}

/**
 * @brief       ��Բ
 * @param       x,y  : Բ��������
 * @param       r    : �뾶
 * @param       color: Բ����ɫ
 * @retval      ��
 */
void lcd_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);       /* �ж��¸���λ�õı�־ */

    while (a <= b)
    {
        lcd_draw_point(x0 + a, y0 - b, color);  /* 5 */
        lcd_draw_point(x0 + b, y0 - a, color);  /* 0 */
        lcd_draw_point(x0 + b, y0 + a, color);  /* 4 */
        lcd_draw_point(x0 + a, y0 + b, color);  /* 6 */
        lcd_draw_point(x0 - a, y0 + b, color);  /* 1 */
        lcd_draw_point(x0 - b, y0 + a, color);
        lcd_draw_point(x0 - a, y0 - b, color);  /* 2 */
        lcd_draw_point(x0 - b, y0 - a, color);  /* 7 */
        a++;

        /* ʹ��Bresenham�㷨��Բ */
        if (di < 0)
        {
            di += 4 * a + 6;
        }
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}


/**
 * @brief       ��ˮƽ��
 * @param       x0,y0: �������
 * @param       len  : �߳���
 * @param       color: ���ε���ɫ
 * @retval      ��
 */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color)
{
    if ((len == 0) || (x > tftlcd_data.width) || (y > tftlcd_data.height))return;

    lcd_fill(x, y, x + len - 1, y, color);
}


/**
 * @brief       ���ʵ��Բ
 * @param       x0,y0: Բ��������
 * @param       r    : �뾶
 * @param       color: Բ����ɫ
 * @retval      ��
 */
void lcd_fill_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color)
{
    uint32_t i;
    uint32_t imax = ((uint32_t)r * 707) / 1000 + 1;
    uint32_t sqmax = (uint32_t)r * (uint32_t)r + (uint32_t)r / 2;
    uint32_t xr = r;

    lcd_draw_hline(x - r, y, 2 * r, color);

    for (i = 1; i <= imax; i++)
    {
        if ((i * i + xr * xr) > sqmax)
        {
            /* draw lines from outside */
            if (xr > imax)
            {
                lcd_draw_hline (x - i + 1, y + xr, 2 * (i - 1), color);
                lcd_draw_hline (x - i + 1, y - xr, 2 * (i - 1), color);
            }

            xr--;
        }

        /* draw lines from inside (center) */
        lcd_draw_hline(x - xr, y + i, 2 * xr, color);
        lcd_draw_hline(x - xr, y - i, 2 * xr, color);
    }
}

/**
 * @brief       ��ָ��λ����ʾһ���ַ�
 * @param       x,y  : ����
 * @param       chr  : Ҫ��ʾ���ַ�:" "--->"~"
 * @param       size : �����С 12/16/24/32
 * @param       mode : ���ӷ�ʽ(1); �ǵ��ӷ�ʽ(0);
 * @retval      ��
 */
void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = 0;
    uint8_t *pfont = 0;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); /* �õ�����һ���ַ���Ӧ������ռ���ֽ��� */
    chr = chr - ' ';    /* �õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩ */

    switch (size)
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
        temp = pfont[t];    /* ��ȡ�ַ��ĵ������� */

        for (t1 = 0; t1 < 8; t1++)   /* һ���ֽ�8���� */
        {
            if (temp & 0x80)        /* ��Ч��,��Ҫ��ʾ */
            {
                lcd_draw_point(x, y, color);        /* �������,Ҫ��ʾ����� */
            }
            else if (mode == 0)     /* ��Ч��,����ʾ */
            {
                lcd_draw_point(x, y, g_back_color); /* ������ɫ,�൱������㲻��ʾ(ע�ⱳ��ɫ��ȫ�ֱ�������) */
            }

            temp <<= 1; /* ��λ, �Ա��ȡ��һ��λ��״̬ */
            y++;

            if (y >= tftlcd_data.height)return;  /* �������� */

            if ((y - y0) == size)   /* ��ʾ��һ����? */
            {
                y = y0; /* y���긴λ */
                x++;    /* x������� */

                if (x >= tftlcd_data.width)return;   /* x���곬������ */

                break;
            }
        }
    }
}

/**
 * @brief       ƽ������, m^n
 * @param       m: ����
 * @param       n: ָ��
 * @retval      m��n�η�
 */
static uint32_t lcd_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;

    while (n--)result *= m;

    return result;
}

/**
 * @brief       ��ʾlen������
 * @param       x,y : ��ʼ����
 * @param       num : ��ֵ(0 ~ 2^32)
 * @param       len : ��ʾ���ֵ�λ��
 * @param       size: ѡ������ 12/16/24/32
 * @retval      ��
 */
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint16_t color)
{
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++)   /* ������ʾλ��ѭ�� */
    {
        temp = (num / lcd_pow(10, len - t - 1)) % 10;   /* ��ȡ��Ӧλ������ */

        if (enshow == 0 && t < (len - 1))   /* û��ʹ����ʾ,�һ���λҪ��ʾ */
        {
            if (temp == 0)
            {
                lcd_show_char(x + (size / 2)*t, y, ' ', size, 0, color);/* ��ʾ�ո�,ռλ */
                continue;   /* �����¸�һλ */
            }
            else
            {
                enshow = 1; /* ʹ����ʾ */
            }

        }

        lcd_show_char(x + (size / 2)*t, y, temp + '0', size, 0, color); /* ��ʾ�ַ� */
    }
}

/**
 * @brief       ��չ��ʾlen������(��λ��0Ҳ��ʾ)
 * @param       x,y : ��ʼ����
 * @param       num : ��ֵ(0 ~ 2^32)
 * @param       len : ��ʾ���ֵ�λ��
 * @param       size: ѡ������ 12/16/24/32
 * @param       mode: ��ʾģʽ
 *              [7]:0,�����;1,���0.
 *              [6:1]:����
 *              [0]:0,�ǵ�����ʾ;1,������ʾ.
 *
 * @retval      ��
 */
void lcd_show_xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++)   /* ������ʾλ��ѭ�� */
    {
        temp = (num / lcd_pow(10, len - t - 1)) % 10;    /* ��ȡ��Ӧλ������ */

        if (enshow == 0 && t < (len - 1))   /* û��ʹ����ʾ,�һ���λҪ��ʾ */
        {
            if (temp == 0)
            {
                if (mode & 0X80)   /* ��λ��Ҫ���0 */
                {
                    lcd_show_char(x + (size / 2)*t, y, '0', size, mode & 0X01, color);  /* ��0ռλ */
                }
                else
                {
                    lcd_show_char(x + (size / 2)*t, y, ' ', size, mode & 0X01, color);  /* �ÿո�ռλ */
                }

                continue;
            }
            else
            {
                enshow = 1; /* ʹ����ʾ */
            }

        }

        lcd_show_char(x + (size / 2)*t, y, temp + '0', size, mode & 0X01, color);
    }
}

/**
 * @brief       ��ʾ�ַ���
 * @param       x,y         : ��ʼ����
 * @param       width,height: �����С
 * @param       size        : ѡ������ 12/16/24/32
 * @param       p           : �ַ����׵�ַ
 * @retval      ��
 */
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)
{
    uint8_t x0 = x;
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' '))   /* �ж��ǲ��ǷǷ��ַ�! */
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }

        if (y >= height)break;  /* �˳� */

        lcd_show_char(x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}

void lcd_init()
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
		tftlcd_data.id=lcd_rd_data(); 
		printf("lcddev_id1:%#x \r\n", tftlcd_data.id);
   
	 //��ʼ��
		lcd_wr_regno(0x0000);
	lcd_wr_regno(0x0000);
	delay_ms(10);
	lcd_wr_regno(0x0000);
	lcd_wr_regno(0x0000);
	lcd_wr_regno(0x0000);
	lcd_wr_regno(0x0000);
	lcd_wr_regno(0x00A4);lcd_wr_data(0x0001);
	delay_ms(10);

	lcd_wr_regno(0x0060);lcd_wr_data(0x2700);
	lcd_wr_regno(0x0008);lcd_wr_data(0x0808);

	//----------- Adjust the Gamma Curve ----------/
	lcd_wr_regno(0x0300);lcd_wr_data(0x0109);  // Gamma Control
	lcd_wr_regno(0x0301);lcd_wr_data(0x7E0A); 
	lcd_wr_regno(0x0302);lcd_wr_data(0x0704); 
	lcd_wr_regno(0x0303);lcd_wr_data(0x0911); 
	lcd_wr_regno(0x0304);lcd_wr_data(0x2100); 
	lcd_wr_regno(0x0305);lcd_wr_data(0x1109); 
	lcd_wr_regno(0x0306);lcd_wr_data(0x7407); 
	lcd_wr_regno(0x0307);lcd_wr_data(0x0A0E); 
	lcd_wr_regno(0x0308);lcd_wr_data(0x0901); 
	lcd_wr_regno(0x0309);lcd_wr_data(0x0021);

	lcd_wr_regno(0x0010);lcd_wr_data(0x0010);  // Frame frequence
	lcd_wr_regno(0x0011);lcd_wr_data(0x0202);  // 
	lcd_wr_regno(0x0012);lcd_wr_data(0x0300); 
	lcd_wr_regno(0x0013);lcd_wr_data(0x0007);
	delay_ms(10);
	// -------------- Power On sequence -------------//
	lcd_wr_regno(0x0100);lcd_wr_data(0x0000);  // VGH/VGL 6/-3
	lcd_wr_regno(0x0101);lcd_wr_data(0x0007);  // VCI1
	lcd_wr_regno(0x0102);lcd_wr_data(0x0000);  // VREG1
	lcd_wr_regno(0x0103);lcd_wr_data(0x0000);  // VDV 
	lcd_wr_regno(0x0280);lcd_wr_data(0x0000);  // VCM
	delay_ms(200);//delay_ms 200ms
	lcd_wr_regno(0x0100);lcd_wr_data(0x0330);  // VGH/VGL 6/-3
	lcd_wr_regno(0x0101);lcd_wr_data(0x0247);  // VCI1
	delay_ms(50);//delay_ms 50ms
	lcd_wr_regno(0x0102);lcd_wr_data(0xD1B0);  // VREG1
	delay_ms(50);//delay_ms 50ms
	lcd_wr_regno(0x0103);lcd_wr_data(0x1000);  // VDV          //0900
	lcd_wr_regno(0x0280);lcd_wr_data(0xC600);  // VCM          //chenyu 0xc600

	delay_ms(200);

	lcd_wr_regno(0x0001);lcd_wr_data(0x0100);
	lcd_wr_regno(0x0002);lcd_wr_data(0x0200);
	lcd_wr_regno(0x0003);lcd_wr_data(0x1030);
	lcd_wr_regno(0x0009);lcd_wr_data(0x0001);
	lcd_wr_regno(0x000A);lcd_wr_data(0x0008);
	lcd_wr_regno(0x000C);lcd_wr_data(0x0000);
	lcd_wr_regno(0x000D);lcd_wr_data(0x0000);
	lcd_wr_regno(0x000E);lcd_wr_data(0x0030);
	lcd_wr_regno(0x0020);lcd_wr_data(0x0000);//H Start
	lcd_wr_regno(0x0021);lcd_wr_data(0x0000);//V Start
	lcd_wr_regno(0x0029);lcd_wr_data(0x0052);
	lcd_wr_regno(0x0050);lcd_wr_data(0x0000);
	lcd_wr_regno(0x0051);lcd_wr_data(0x00EF);
	lcd_wr_regno(0x0052);lcd_wr_data(0x0000);
	lcd_wr_regno(0x0053);lcd_wr_data(0x013F);
	lcd_wr_regno(0x0061);lcd_wr_data(0x0000);
	lcd_wr_regno(0x006A);lcd_wr_data(0x0000);
	lcd_wr_regno(0x0080);lcd_wr_data(0x0000);
	lcd_wr_regno(0x0081);lcd_wr_data(0x0000);
	lcd_wr_regno(0x0082);lcd_wr_data(0x005F);
	lcd_wr_regno(0x0093);lcd_wr_data(0x0507);

	lcd_wr_regno(0x0007);lcd_wr_data(0x0100);//DISPLAY ON
	delay_ms(50);
	lcd_wr_regno(0x0022);//GRAM Data Write
	//LCD��ʼ������
   
	LCD_Display_Dir(TFTLCD_DIR);		//0������  1������  Ĭ������
	lcd_clear(WHITE);	 
    
}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_FSMC_CLK_ENABLE();            /* ʹ��FSMCʱ�� */
    __HAL_RCC_GPIOD_CLK_ENABLE();           /* ʹ��GPIODʱ�� */
    __HAL_RCC_GPIOE_CLK_ENABLE();           /* ʹ��GPIOEʱ�� */
    
    LCD_WR_GPIO_CLK_ENABLE();
    LCD_RD_GPIO_CLK_ENABLE();

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
