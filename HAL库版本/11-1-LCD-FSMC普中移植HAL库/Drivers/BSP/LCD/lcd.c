#include "./BSP/LCD/lcd.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
//#include "./BSP/LCD/lcd_ex.c"
#include "./BSP/LCD/lcdfont.h"

SRAM_HandleTypeDef g_sram_handle;    /* SRAM���(���ڿ���LCD) */

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 FRONT_COLOR=BLACK;	//������ɫ
u16 BACK_COLOR=WHITE;  //����ɫ 

_tftlcd_data tftlcd_data; 





/* д���� */
void LCD_WriteCmd(u16 cmd)
{
	TFTLCD->LCD_CMD=(cmd>>8)<<1;
	TFTLCD->LCD_CMD=(cmd&0xff)<<1;
}

/* д���� */
void LCD_WriteData(u16 data)
{
  TFTLCD->LCD_DATA=(data>>8)<<1;
	TFTLCD->LCD_DATA=(data&0xff)<<1;	
}

/* д�Ĵ��� */
void LCD_WriteCmdData(u16 cmd,u16 data)
{
	LCD_WriteCmd(cmd);
	LCD_WriteData(data);
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
/* ������ */
u16 LCD_ReadData(void)
{
   u16 ram;		
	ram=(TFTLCD->LCD_DATA)>>1;
	ram=ram<<8;
	ram|=(TFTLCD->LCD_DATA)>>1;	
	return ram;	
}

//����LCD��ʾ����
//dir:0,������1,����
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)  //Ĭ����������
	{		
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0100);
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1030);
		tftlcd_data.height=400;
		tftlcd_data.width=240;
	}
	else
	{	
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0100);	//����ͷ��Ҫ������������Ϊ0x0100������0x0000
		LCD_WriteCmd(0x0003);
		LCD_WriteData(0x1038);
		tftlcd_data.height=240;
		tftlcd_data.width=400;
		tftlcd_data.dir=1;
	}
}


void TFTLCD_Init(void)
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
    LCD_WriteCmd(0x0000);				   	
		tftlcd_data.id=LCD_ReadData(); 
		printf("lcddev_id1:%#x \r\n", tftlcd_data.id);
   
	 //��ʼ��
		LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	delay_ms(10);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x0000);
	LCD_WriteCmd(0x00A4);LCD_WriteData(0x0001);
	delay_ms(10);

	LCD_WriteCmd(0x0060);LCD_WriteData(0x2700);
	LCD_WriteCmd(0x0008);LCD_WriteData(0x0808);

	//----------- Adjust the Gamma Curve ----------/
	LCD_WriteCmd(0x0300);LCD_WriteData(0x0109);  // Gamma Control
	LCD_WriteCmd(0x0301);LCD_WriteData(0x7E0A); 
	LCD_WriteCmd(0x0302);LCD_WriteData(0x0704); 
	LCD_WriteCmd(0x0303);LCD_WriteData(0x0911); 
	LCD_WriteCmd(0x0304);LCD_WriteData(0x2100); 
	LCD_WriteCmd(0x0305);LCD_WriteData(0x1109); 
	LCD_WriteCmd(0x0306);LCD_WriteData(0x7407); 
	LCD_WriteCmd(0x0307);LCD_WriteData(0x0A0E); 
	LCD_WriteCmd(0x0308);LCD_WriteData(0x0901); 
	LCD_WriteCmd(0x0309);LCD_WriteData(0x0021);

	LCD_WriteCmd(0x0010);LCD_WriteData(0x0010);  // Frame frequence
	LCD_WriteCmd(0x0011);LCD_WriteData(0x0202);  // 
	LCD_WriteCmd(0x0012);LCD_WriteData(0x0300); 
	LCD_WriteCmd(0x0013);LCD_WriteData(0x0007);
	delay_ms(10);
	// -------------- Power On sequence -------------//
	LCD_WriteCmd(0x0100);LCD_WriteData(0x0000);  // VGH/VGL 6/-3
	LCD_WriteCmd(0x0101);LCD_WriteData(0x0007);  // VCI1
	LCD_WriteCmd(0x0102);LCD_WriteData(0x0000);  // VREG1
	LCD_WriteCmd(0x0103);LCD_WriteData(0x0000);  // VDV 
	LCD_WriteCmd(0x0280);LCD_WriteData(0x0000);  // VCM
	delay_ms(200);//delay_ms 200ms
	LCD_WriteCmd(0x0100);LCD_WriteData(0x0330);  // VGH/VGL 6/-3
	LCD_WriteCmd(0x0101);LCD_WriteData(0x0247);  // VCI1
	delay_ms(50);//delay_ms 50ms
	LCD_WriteCmd(0x0102);LCD_WriteData(0xD1B0);  // VREG1
	delay_ms(50);//delay_ms 50ms
	LCD_WriteCmd(0x0103);LCD_WriteData(0x1000);  // VDV          //0900
	LCD_WriteCmd(0x0280);LCD_WriteData(0xC600);  // VCM          //chenyu 0xc600

	delay_ms(200);

	LCD_WriteCmd(0x0001);LCD_WriteData(0x0100);
	LCD_WriteCmd(0x0002);LCD_WriteData(0x0200);
	LCD_WriteCmd(0x0003);LCD_WriteData(0x1030);
	LCD_WriteCmd(0x0009);LCD_WriteData(0x0001);
	LCD_WriteCmd(0x000A);LCD_WriteData(0x0008);
	LCD_WriteCmd(0x000C);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x000D);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x000E);LCD_WriteData(0x0030);
	LCD_WriteCmd(0x0020);LCD_WriteData(0x0000);//H Start
	LCD_WriteCmd(0x0021);LCD_WriteData(0x0000);//V Start
	LCD_WriteCmd(0x0029);LCD_WriteData(0x0052);
	LCD_WriteCmd(0x0050);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0051);LCD_WriteData(0x00EF);
	LCD_WriteCmd(0x0052);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0053);LCD_WriteData(0x013F);
	LCD_WriteCmd(0x0061);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x006A);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0080);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0081);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0082);LCD_WriteData(0x005F);
	LCD_WriteCmd(0x0093);LCD_WriteData(0x0507);

	LCD_WriteCmd(0x0007);LCD_WriteData(0x0100);//DISPLAY ON
	delay_ms(50);
	LCD_WriteCmd(0x0022);//GRAM Data Write
	//LCD��ʼ������
   
	LCD_Display_Dir(TFTLCD_DIR);		//0������  1������  Ĭ������
	LCD_Clear(WHITE);	 
    
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


//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height. 
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{
	if(tftlcd_data.dir==0)
	{
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0211);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0213);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sy);	
	}   	
	else
	{
		LCD_WriteCmd(0x0212);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0213);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0210);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0211);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0201);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0200);   
	    LCD_WriteData(sy);	
	}
	LCD_WriteCmd(0x0202);
}

//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	uint16_t i, j ;

	LCD_Set_Window(0, 0, tftlcd_data.width-1, tftlcd_data.height-1);	 //��������
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
void LCD_Fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,u16 color)
{          
	uint16_t temp;

    if((xState > xEnd) || (yState > yEnd))
    {
        return;
    }   
	LCD_Set_Window(xState, yState, xEnd, yEnd); 
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


//����
//x,y:����
//FRONT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_Set_Window(x, y, x, y);  //���õ��λ��
	LCD_WriteData_Color(FRONT_COLOR);	
}

//���ٻ���
//x,y:����
//color:��ɫ
void LCD_DrawFRONT_COLOR(u16 x,u16 y,u16 color)
{	   
	LCD_Set_Window(x, y, x, y);
	LCD_WriteData_Color(color);	
} 

//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	u16 r1,r2,r3;
	u32 value;
	
	if(x>=tftlcd_data.width||y>=tftlcd_data.height)return 0;	//�����˷�Χ,ֱ�ӷ���		     
	LCD_Set_Window(x, y, x, y);
	LCD_WriteCmd(0X0202);
	
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

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
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
		LCD_DrawPoint(uRow,uCol);//���� 
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


void LCD_DrawLine_Color(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
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
		LCD_DrawFRONT_COLOR(uRow,uCol,color);//���� 
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


// ��һ��ʮ�ֵı��
// x����ǵ�X����
// y����ǵ�Y����
// color����ǵ���ɫ
void LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t i;

    /* ���� */
    LCD_Set_Window(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color);   
    }

    /* ���� */
    LCD_Set_Window(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }

    /* ���� */
    LCD_Set_Window(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }
}

//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 



//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=ascii_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=ascii_1608[num][t];	//����1608����
		else if(size==24)temp=ascii_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
			else if(mode==0)LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=tftlcd_data.height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=tftlcd_data.width)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}


void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)
{
	u8 i, j, wordNum;
	u16 color;
	u16 x0=x; 
	u16 y0=y; 
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
						} 						
						else
						{
							LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
						} 
						color<<=1;
						x++;
						if((x-x0)==32)
						{
							x=x0;
							y++;
							if((y-y0)==29)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)����
				}	
			}
			
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
		x0=x;
	}
}	

void LCD_ShowPicture(u16 x, u16 y, u16 wide, u16 high,u8 *pic)
{
	u16 temp = 0;
	long tmp=0,num=0;
	LCD_Set_Window(x, y, x+wide-1, y+high-1);
	num = wide * high*2 ;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		LCD_WriteData_Color(temp);//�����ʾ
		tmp += 2;
	}
	while(tmp < num);	
}
