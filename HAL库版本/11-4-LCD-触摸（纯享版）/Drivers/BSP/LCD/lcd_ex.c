#include "./SYSTEM/delay/delay.h"
#include "./BSP/LCD/lcd.h"


/**
 * @brief      R61509VN 普中移植 寄存器初始化代码
 * @param       无
 * @retval      无
 */
void lcd_ex_b509_reginit(void)
{
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

}

/**
 * @brief       ST7789 寄存器初始化代码
 * @param       无
 * @retval      无
 */
void lcd_ex_st7789_reginit(void)
{
    lcd_wr_regno(0x11);

    delay_ms(120); 

    lcd_wr_regno(0x36);
    lcd_wr_data(0x00);

    lcd_wr_regno(0x3A);
    lcd_wr_data(0X05);

    lcd_wr_regno(0xB2);
    lcd_wr_data(0x0C);
    lcd_wr_data(0x0C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x33);
    lcd_wr_data(0x33);

    lcd_wr_regno(0xB7);
    lcd_wr_data(0x35);

    lcd_wr_regno(0xBB); /* vcom */
    lcd_wr_data(0x32);  /* 30 */

    lcd_wr_regno(0xC0);
    lcd_wr_data(0x0C);

    lcd_wr_regno(0xC2);
    lcd_wr_data(0x01);

    lcd_wr_regno(0xC3); /* vrh */
    lcd_wr_data(0x10);  /* 17 0D */

    lcd_wr_regno(0xC4); /* vdv */
    lcd_wr_data(0x20);  /* 20 */

    lcd_wr_regno(0xC6);
    lcd_wr_data(0x0f);

    lcd_wr_regno(0xD0);
    lcd_wr_data(0xA4); 
    lcd_wr_data(0xA1); 

    lcd_wr_regno(0xE0); /* Set Gamma  */
    lcd_wr_data(0xd0);
    lcd_wr_data(0x00);
    lcd_wr_data(0x02);
    lcd_wr_data(0x07);
    lcd_wr_data(0x0a);
    lcd_wr_data(0x28);
    lcd_wr_data(0x32);
    lcd_wr_data(0X44);
    lcd_wr_data(0x42);
    lcd_wr_data(0x06);
    lcd_wr_data(0x0e);
    lcd_wr_data(0x12);
    lcd_wr_data(0x14);
    lcd_wr_data(0x17);


    lcd_wr_regno(0XE1);  /* Set Gamma */
    lcd_wr_data(0xd0);
    lcd_wr_data(0x00);
    lcd_wr_data(0x02);
    lcd_wr_data(0x07);
    lcd_wr_data(0x0a);
    lcd_wr_data(0x28);
    lcd_wr_data(0x31);
    lcd_wr_data(0x54);
    lcd_wr_data(0x47);
    lcd_wr_data(0x0e);
    lcd_wr_data(0x1c);
    lcd_wr_data(0x17);
    lcd_wr_data(0x1b); 
    lcd_wr_data(0x1e);


    lcd_wr_regno(0x2A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0xef);

    lcd_wr_regno(0x2B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x01);
    lcd_wr_data(0x3f);

    lcd_wr_regno(0x29); /* display on */
}

/**
 * @brief       ILI9341寄存器初始化代码
 * @param       无
 * @retval      无
 */
void lcd_ex_ili9341_reginit(void)
{
    lcd_wr_regno(0xCF);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC1);
    lcd_wr_data(0X30);
    lcd_wr_regno(0xED);
    lcd_wr_data(0x64);
    lcd_wr_data(0x03);
    lcd_wr_data(0X12);
    lcd_wr_data(0X81);
    lcd_wr_regno(0xE8);
    lcd_wr_data(0x85);
    lcd_wr_data(0x10);
    lcd_wr_data(0x7A);
    lcd_wr_regno(0xCB);
    lcd_wr_data(0x39);
    lcd_wr_data(0x2C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x34);
    lcd_wr_data(0x02);
    lcd_wr_regno(0xF7);
    lcd_wr_data(0x20);
    lcd_wr_regno(0xEA);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_regno(0xC0); /* Power control */
    lcd_wr_data(0x1B);  /* VRH[5:0] */
    lcd_wr_regno(0xC1); /* Power control */
    lcd_wr_data(0x01);  /* SAP[2:0];BT[3:0] */
    lcd_wr_regno(0xC5); /* VCM control */
    lcd_wr_data(0x30);  /* 3F */
    lcd_wr_data(0x30);  /* 3C */
    lcd_wr_regno(0xC7); /* VCM control2 */
    lcd_wr_data(0XB7);
    lcd_wr_regno(0x36); /*  Memory Access Control */
    lcd_wr_data(0x48);
    lcd_wr_regno(0x3A);
    lcd_wr_data(0x55);
    lcd_wr_regno(0xB1);
    lcd_wr_data(0x00);
    lcd_wr_data(0x1A);
    lcd_wr_regno(0xB6); /*  Display Function Control */
    lcd_wr_data(0x0A);
    lcd_wr_data(0xA2);
    lcd_wr_regno(0xF2); /*  3Gamma Function Disable */
    lcd_wr_data(0x00);
    lcd_wr_regno(0x26); /* Gamma curve selected */
    lcd_wr_data(0x01);
    lcd_wr_regno(0xE0); /* Set Gamma */
    lcd_wr_data(0x0F);
    lcd_wr_data(0x2A);
    lcd_wr_data(0x28);
    lcd_wr_data(0x08);
    lcd_wr_data(0x0E);
    lcd_wr_data(0x08);
    lcd_wr_data(0x54);
    lcd_wr_data(0XA9);
    lcd_wr_data(0x43);
    lcd_wr_data(0x0A);
    lcd_wr_data(0x0F);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_regno(0XE1);    /* Set Gamma */
    lcd_wr_data(0x00);
    lcd_wr_data(0x15);
    lcd_wr_data(0x17);
    lcd_wr_data(0x07);
    lcd_wr_data(0x11);
    lcd_wr_data(0x06);
    lcd_wr_data(0x2B);
    lcd_wr_data(0x56);
    lcd_wr_data(0x3C);
    lcd_wr_data(0x05);
    lcd_wr_data(0x10);
    lcd_wr_data(0x0F);
    lcd_wr_data(0x3F);
    lcd_wr_data(0x3F);
    lcd_wr_data(0x0F);
    lcd_wr_regno(0x2B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x01);
    lcd_wr_data(0x3f);
    lcd_wr_regno(0x2A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0xef);
    lcd_wr_regno(0x11); /* Exit Sleep */
    delay_ms(120);
    lcd_wr_regno(0x29); /* display on */
 }

 