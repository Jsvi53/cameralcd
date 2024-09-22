
#include "delay.h"
#include "lcd.h"

/**
 * @brief       ST7789 register initialization code
 * @param       None
 * @retval      None
 */
void LCD_Ex_St7789_Reginit(void)
{
    LCD_Wr_Reg(0x11);

    tim6_delay_ms(120); 

    LCD_Wr_Reg(0x36);
    LCD_Wr_Data(0x00);


    LCD_Wr_Reg(0x3A);
    LCD_Wr_Data(0X05);

    LCD_Wr_Reg(0xB2);
    LCD_Wr_Data(0x0C);
    LCD_Wr_Data(0x0C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x33);
    LCD_Wr_Data(0x33);

    LCD_Wr_Reg(0xB7);
    LCD_Wr_Data(0x35);

    LCD_Wr_Reg(0xBB); /* vcom */
    LCD_Wr_Data(0x32);  /* 30 */

    LCD_Wr_Reg(0xC0);
    LCD_Wr_Data(0x0C);

    LCD_Wr_Reg(0xC2);
    LCD_Wr_Data(0x01);

    LCD_Wr_Reg(0xC3); /* vrh */
    LCD_Wr_Data(0x10);  /* 17 0D */

    LCD_Wr_Reg(0xC4); /* vdv */
    LCD_Wr_Data(0x20);  /* 20 */

    LCD_Wr_Reg(0xC6);
    LCD_Wr_Data(0x0f);

    LCD_Wr_Reg(0xD0);
    LCD_Wr_Data(0xA4); 
    LCD_Wr_Data(0xA1); 

    LCD_Wr_Reg(0xE0); /* Set Gamma  */
    LCD_Wr_Data(0xd0);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x02);
    LCD_Wr_Data(0x07);
    LCD_Wr_Data(0x0a);
    LCD_Wr_Data(0x28);
    LCD_Wr_Data(0x32);
    LCD_Wr_Data(0X44);
    LCD_Wr_Data(0x42);
    LCD_Wr_Data(0x06);
    LCD_Wr_Data(0x0e);
    LCD_Wr_Data(0x12);
    LCD_Wr_Data(0x14);
    LCD_Wr_Data(0x17);


    LCD_Wr_Reg(0XE1);  /* Set Gamma */
    LCD_Wr_Data(0xd0);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x02);
    LCD_Wr_Data(0x07);
    LCD_Wr_Data(0x0a);
    LCD_Wr_Data(0x28);
    LCD_Wr_Data(0x31);
    LCD_Wr_Data(0x54);
    LCD_Wr_Data(0x47);
    LCD_Wr_Data(0x0e);
    LCD_Wr_Data(0x1c);
    LCD_Wr_Data(0x17);
    LCD_Wr_Data(0x1b); 
    LCD_Wr_Data(0x1e);


    LCD_Wr_Reg(0x2A);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xef);

    LCD_Wr_Reg(0x2B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x3f);

    LCD_Wr_Reg(0x29); /* display on */
}

void LCD_Ex_Ili9341_Reginit(void)
{
    LCD_Wr_Reg(0xCF);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC1);
    LCD_Wr_Data(0X30);
    LCD_Wr_Reg(0xED);
    LCD_Wr_Data(0x64);
    LCD_Wr_Data(0x03);
    LCD_Wr_Data(0X12);
    LCD_Wr_Data(0X81);
    LCD_Wr_Reg(0xE8);
    LCD_Wr_Data(0x85);
    LCD_Wr_Data(0x10);
    LCD_Wr_Data(0x7A);
    LCD_Wr_Reg(0xCB);
    LCD_Wr_Data(0x39);
    LCD_Wr_Data(0x2C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x34);
    LCD_Wr_Data(0x02);
    LCD_Wr_Reg(0xF7);
    LCD_Wr_Data(0x20);
    LCD_Wr_Reg(0xEA);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Reg(0xC0); /* Power control */
    LCD_Wr_Data(0x1B);  /* VRH[5:0] */
    LCD_Wr_Reg(0xC1); /* Power control */
    LCD_Wr_Data(0x01);  /* SAP[2:0];BT[3:0] */
    LCD_Wr_Reg(0xC5); /* VCM control */
    LCD_Wr_Data(0x30);  /* 3F */
    LCD_Wr_Data(0x30);  /* 3C */
    LCD_Wr_Reg(0xC7); /* VCM control2 */
    LCD_Wr_Data(0XB7);
    LCD_Wr_Reg(0x36); /*  Memory Access Control */
    LCD_Wr_Data(0x48);
    LCD_Wr_Reg(0x3A);
    LCD_Wr_Data(0x55);
    LCD_Wr_Reg(0xB1);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x1A);
    LCD_Wr_Reg(0xB6); /*  Display Function Control */
    LCD_Wr_Data(0x0A);
    LCD_Wr_Data(0xA2);
    LCD_Wr_Reg(0xF2); /*  3Gamma Function Disable */
    LCD_Wr_Data(0x00);
    LCD_Wr_Reg(0x26); /* Gamma curve selected */
    LCD_Wr_Data(0x01);
    LCD_Wr_Reg(0xE0); /* Set Gamma */
    LCD_Wr_Data(0x0F);
    LCD_Wr_Data(0x2A);
    LCD_Wr_Data(0x28);
    LCD_Wr_Data(0x08);
    LCD_Wr_Data(0x0E);
    LCD_Wr_Data(0x08);
    LCD_Wr_Data(0x54);
    LCD_Wr_Data(0XA9);
    LCD_Wr_Data(0x43);
    LCD_Wr_Data(0x0A);
    LCD_Wr_Data(0x0F);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Reg(0XE1);    /* Set Gamma */
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x15);
    LCD_Wr_Data(0x17);
    LCD_Wr_Data(0x07);
    LCD_Wr_Data(0x11);
    LCD_Wr_Data(0x06);
    LCD_Wr_Data(0x2B);
    LCD_Wr_Data(0x56);
    LCD_Wr_Data(0x3C);
    LCD_Wr_Data(0x05);
    LCD_Wr_Data(0x10);
    LCD_Wr_Data(0x0F);
    LCD_Wr_Data(0x3F);
    LCD_Wr_Data(0x3F);
    LCD_Wr_Data(0x0F);
    LCD_Wr_Reg(0x2B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x3f);
    LCD_Wr_Reg(0x2A);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xef);
    LCD_Wr_Reg(0x11); /* Exit Sleep */
    tim6_delay_ms(120);
    LCD_Wr_Reg(0x29); /* display on */
}

void LCD_Ex_Nt35310_Reginit(void)
{
    LCD_Wr_Reg(0xED);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0xFE);

    LCD_Wr_Reg(0xEE);
    LCD_Wr_Data(0xDE);
    LCD_Wr_Data(0x21);

    LCD_Wr_Reg(0xF1);
    LCD_Wr_Data(0x01);
    LCD_Wr_Reg(0xDF);
    LCD_Wr_Data(0x10);

    /* VCOMvoltage */
    LCD_Wr_Reg(0xC4);
    LCD_Wr_Data(0x8F);  /* 5f */

    LCD_Wr_Reg(0xC6);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xE2);
    LCD_Wr_Data(0xE2);
    LCD_Wr_Data(0xE2);
    LCD_Wr_Reg(0xBF);
    LCD_Wr_Data(0xAA);

    LCD_Wr_Reg(0xB0);
    LCD_Wr_Data(0x0D);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x0D);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x11);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x19);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x21);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x2D);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x3D);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x5D);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x5D);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xB1);
    LCD_Wr_Data(0x80);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x8B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x96);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xB2);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x02);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x03);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xB3);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xB4);
    LCD_Wr_Data(0x8B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x96);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA1);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xB5);
    LCD_Wr_Data(0x02);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x03);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x04);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xB6);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xB7);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x3F);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x5E);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x64);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x8C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xAC);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xDC);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x70);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x90);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xEB);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xDC);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xB8);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xBA);
    LCD_Wr_Data(0x24);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC1);
    LCD_Wr_Data(0x20);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x54);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xFF);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC2);
    LCD_Wr_Data(0x0A);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x04);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC3);
    LCD_Wr_Data(0x3C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x3A);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x39);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x37);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x3C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x36);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x32);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x2F);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x2C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x29);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x26);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x24);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x24);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x23);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x3C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x36);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x32);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x2F);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x2C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x29);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x26);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x24);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x24);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x23);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC4);
    LCD_Wr_Data(0x62);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x05);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x84);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xF0);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x18);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA4);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x18);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x50);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x0C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x17);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x95);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xF3);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xE6);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC5);
    LCD_Wr_Data(0x32);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x44);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x65);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x76);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x88);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC6);
    LCD_Wr_Data(0x20);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x17);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC7);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC8);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xC9);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xE0);
    LCD_Wr_Data(0x16);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x1C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x21);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x36);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x46);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x52);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x64);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x7A);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x8B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x99);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA8);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xB9);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC4);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xCA);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD2);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD9);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xE0);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xF3);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xE1);
    LCD_Wr_Data(0x16);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x1C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x22);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x36);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x45);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x52);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x64);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x7A);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x8B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x99);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA8);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xB9);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC4);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xCA);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD2);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD8);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xE0);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xF3);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xE2);
    LCD_Wr_Data(0x05);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x0B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x1B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x34);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x44);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x4F);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x61);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x79);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x88);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x97);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA6);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xB7);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC2);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC7);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD1);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD6);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xDD);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xF3);
    LCD_Wr_Data(0x00);
    LCD_Wr_Reg(0xE3);
    LCD_Wr_Data(0x05);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x1C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x33);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x44);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x50);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x62);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x78);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x88);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x97);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA6);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xB7);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC2);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC7);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD1);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD5);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xDD);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xF3);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xE4);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x02);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x2A);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x3C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x4B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x5D);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x74);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x84);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x93);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA2);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xB3);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xBE);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC4);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xCD);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD3);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xDD);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xF3);
    LCD_Wr_Data(0x00);
    LCD_Wr_Reg(0xE5);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x02);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x29);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x3C);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x4B);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x5D);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x74);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x84);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x93);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xA2);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xB3);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xBE);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xC4);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xCD);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xD3);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xDC);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xF3);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xE6);
    LCD_Wr_Data(0x11);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x34);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x56);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x76);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x77);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x66);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x88);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x99);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xBB);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x99);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x66);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x55);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x55);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x45);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x43);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x44);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xE7);
    LCD_Wr_Data(0x32);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x55);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x76);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x66);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x67);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x67);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x87);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x99);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xBB);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x99);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x77);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x44);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x56);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x23);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x33);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x45);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xE8);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x99);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x87);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x88);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x77);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x66);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x88);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xAA);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xBB);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x99);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x66);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x55);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x55);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x44);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x44);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x55);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xE9);
    LCD_Wr_Data(0xAA);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0x00);
    LCD_Wr_Data(0xAA);

    LCD_Wr_Reg(0xCF);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xF0);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x50);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xF3);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xF9);
    LCD_Wr_Data(0x06);
    LCD_Wr_Data(0x10);
    LCD_Wr_Data(0x29);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0x3A);
    LCD_Wr_Data(0x55);  /* 66 */

    LCD_Wr_Reg(0x11);
    tim6_delay_ms(100);
    LCD_Wr_Reg(0x29);
    LCD_Wr_Reg(0x35);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0x51);
    LCD_Wr_Data(0xFF);
    LCD_Wr_Reg(0x53);
    LCD_Wr_Data(0x2C);
    LCD_Wr_Reg(0x55);
    LCD_Wr_Data(0x82);
    LCD_Wr_Reg(0x2c);
}

void LCD_Ex_St7796_Reginit(void)
{
    LCD_Wr_Reg(0x11);

    tim6_delay_ms(120); 

    LCD_Wr_Reg(0x36); /* Memory Data Access Control MY,MX~~ */
    LCD_Wr_Data(0x48);
    
    LCD_Wr_Reg(0x3A);
    LCD_Wr_Data(0x55);
    
    LCD_Wr_Reg(0xF0);
    LCD_Wr_Data(0xC3);
    
    LCD_Wr_Reg(0xF0);
    LCD_Wr_Data(0x96);

    LCD_Wr_Reg(0xB4);
    LCD_Wr_Data(0x01);
    
    LCD_Wr_Reg(0xB6); /* Display Function Control */
    LCD_Wr_Data(0x0A);
    LCD_Wr_Data(0xA2);

    LCD_Wr_Reg(0xB7);
    LCD_Wr_Data(0xC6);

    LCD_Wr_Reg(0xB9);
    LCD_Wr_Data(0x02);
    LCD_Wr_Data(0xE0);

    LCD_Wr_Reg(0xC0);
    LCD_Wr_Data(0x80);
    LCD_Wr_Data(0x16);

    LCD_Wr_Reg(0xC1);
    LCD_Wr_Data(0x19);

    LCD_Wr_Reg(0xC2);
    LCD_Wr_Data(0xA7);

    LCD_Wr_Reg(0xC5);
    LCD_Wr_Data(0x16);   

    LCD_Wr_Reg(0xE8);
    LCD_Wr_Data(0x40);
    LCD_Wr_Data(0x8A);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x29);
    LCD_Wr_Data(0x19);
    LCD_Wr_Data(0xA5);
    LCD_Wr_Data(0x33);

    LCD_Wr_Reg(0xE0);
    LCD_Wr_Data(0xF0);
    LCD_Wr_Data(0x07);
    LCD_Wr_Data(0x0D);
    LCD_Wr_Data(0x04);
    LCD_Wr_Data(0x05);
    LCD_Wr_Data(0x14);
    LCD_Wr_Data(0x36);
    LCD_Wr_Data(0x54);
    LCD_Wr_Data(0x4C);
    LCD_Wr_Data(0x38);
    LCD_Wr_Data(0x13);
    LCD_Wr_Data(0x14);
    LCD_Wr_Data(0x2E);
    LCD_Wr_Data(0x34);

    LCD_Wr_Reg(0xE1);
    LCD_Wr_Data(0xF0);
    LCD_Wr_Data(0x10);
    LCD_Wr_Data(0x14);
    LCD_Wr_Data(0x0E);
    LCD_Wr_Data(0x0C);
    LCD_Wr_Data(0x08);
    LCD_Wr_Data(0x35);
    LCD_Wr_Data(0x44);
    LCD_Wr_Data(0x4C);
    LCD_Wr_Data(0x26);
    LCD_Wr_Data(0x10);
    LCD_Wr_Data(0x12);
    LCD_Wr_Data(0x2C);
    LCD_Wr_Data(0x32);

    LCD_Wr_Reg(0xF0);
    LCD_Wr_Data(0x3C);

    LCD_Wr_Reg(0xF0);
    LCD_Wr_Data(0x69);

    tim6_delay_ms(120);

    LCD_Wr_Reg(0x21);
    LCD_Wr_Reg(0x29);
}

void LCD_Ex_Nt35510_Reginit(void)
{
    LCD_Wr_Reg_Data(0xF000, 0x55);
    LCD_Wr_Reg_Data(0xF001, 0xAA);
    LCD_Wr_Reg_Data(0xF002, 0x52);
    LCD_Wr_Reg_Data(0xF003, 0x08);
    LCD_Wr_Reg_Data(0xF004, 0x01);
    /* AVDD Set AVDD 5.2V */
    LCD_Wr_Reg_Data(0xB000, 0x0D);
    LCD_Wr_Reg_Data(0xB001, 0x0D);
    LCD_Wr_Reg_Data(0xB002, 0x0D);
    /* AVDD ratio */
    LCD_Wr_Reg_Data(0xB600, 0x34);
    LCD_Wr_Reg_Data(0xB601, 0x34);
    LCD_Wr_Reg_Data(0xB602, 0x34);
    /* AVEE -5.2V */
    LCD_Wr_Reg_Data(0xB100, 0x0D);
    LCD_Wr_Reg_Data(0xB101, 0x0D);
    LCD_Wr_Reg_Data(0xB102, 0x0D);
    /* AVEE ratio */
    LCD_Wr_Reg_Data(0xB700, 0x34);
    LCD_Wr_Reg_Data(0xB701, 0x34);
    LCD_Wr_Reg_Data(0xB702, 0x34);
    /* VCL -2.5V */
    LCD_Wr_Reg_Data(0xB200, 0x00);
    LCD_Wr_Reg_Data(0xB201, 0x00);
    LCD_Wr_Reg_Data(0xB202, 0x00);
    /* VCL ratio */
    LCD_Wr_Reg_Data(0xB800, 0x24);
    LCD_Wr_Reg_Data(0xB801, 0x24);
    LCD_Wr_Reg_Data(0xB802, 0x24);
    /* VGH 15V (Free pump) */
    LCD_Wr_Reg_Data(0xBF00, 0x01);
    LCD_Wr_Reg_Data(0xB300, 0x0F);
    LCD_Wr_Reg_Data(0xB301, 0x0F);
    LCD_Wr_Reg_Data(0xB302, 0x0F);
    /* VGH ratio */
    LCD_Wr_Reg_Data(0xB900, 0x34);
    LCD_Wr_Reg_Data(0xB901, 0x34);
    LCD_Wr_Reg_Data(0xB902, 0x34);
    /* VGL_REG -10V */
    LCD_Wr_Reg_Data(0xB500, 0x08);
    LCD_Wr_Reg_Data(0xB501, 0x08);
    LCD_Wr_Reg_Data(0xB502, 0x08);
    LCD_Wr_Reg_Data(0xC200, 0x03);
    /* VGLX ratio */
    LCD_Wr_Reg_Data(0xBA00, 0x24);
    LCD_Wr_Reg_Data(0xBA01, 0x24);
    LCD_Wr_Reg_Data(0xBA02, 0x24);
    /* VGMP/VGSP 4.5V/0V */
    LCD_Wr_Reg_Data(0xBC00, 0x00);
    LCD_Wr_Reg_Data(0xBC01, 0x78);
    LCD_Wr_Reg_Data(0xBC02, 0x00);
    /* VGMN/VGSN -4.5V/0V */
    LCD_Wr_Reg_Data(0xBD00, 0x00);
    LCD_Wr_Reg_Data(0xBD01, 0x78);
    LCD_Wr_Reg_Data(0xBD02, 0x00);
    /* VCOM */
    LCD_Wr_Reg_Data(0xBE00, 0x00);
    LCD_Wr_Reg_Data(0xBE01, 0x64);
    /* Gamma Setting */
    LCD_Wr_Reg_Data(0xD100, 0x00);
    LCD_Wr_Reg_Data(0xD101, 0x33);
    LCD_Wr_Reg_Data(0xD102, 0x00);
    LCD_Wr_Reg_Data(0xD103, 0x34);
    LCD_Wr_Reg_Data(0xD104, 0x00);
    LCD_Wr_Reg_Data(0xD105, 0x3A);
    LCD_Wr_Reg_Data(0xD106, 0x00);
    LCD_Wr_Reg_Data(0xD107, 0x4A);
    LCD_Wr_Reg_Data(0xD108, 0x00);
    LCD_Wr_Reg_Data(0xD109, 0x5C);
    LCD_Wr_Reg_Data(0xD10A, 0x00);
    LCD_Wr_Reg_Data(0xD10B, 0x81);
    LCD_Wr_Reg_Data(0xD10C, 0x00);
    LCD_Wr_Reg_Data(0xD10D, 0xA6);
    LCD_Wr_Reg_Data(0xD10E, 0x00);
    LCD_Wr_Reg_Data(0xD10F, 0xE5);
    LCD_Wr_Reg_Data(0xD110, 0x01);
    LCD_Wr_Reg_Data(0xD111, 0x13);
    LCD_Wr_Reg_Data(0xD112, 0x01);
    LCD_Wr_Reg_Data(0xD113, 0x54);
    LCD_Wr_Reg_Data(0xD114, 0x01);
    LCD_Wr_Reg_Data(0xD115, 0x82);
    LCD_Wr_Reg_Data(0xD116, 0x01);
    LCD_Wr_Reg_Data(0xD117, 0xCA);
    LCD_Wr_Reg_Data(0xD118, 0x02);
    LCD_Wr_Reg_Data(0xD119, 0x00);
    LCD_Wr_Reg_Data(0xD11A, 0x02);
    LCD_Wr_Reg_Data(0xD11B, 0x01);
    LCD_Wr_Reg_Data(0xD11C, 0x02);
    LCD_Wr_Reg_Data(0xD11D, 0x34);
    LCD_Wr_Reg_Data(0xD11E, 0x02);
    LCD_Wr_Reg_Data(0xD11F, 0x67);
    LCD_Wr_Reg_Data(0xD120, 0x02);
    LCD_Wr_Reg_Data(0xD121, 0x84);
    LCD_Wr_Reg_Data(0xD122, 0x02);
    LCD_Wr_Reg_Data(0xD123, 0xA4);
    LCD_Wr_Reg_Data(0xD124, 0x02);
    LCD_Wr_Reg_Data(0xD125, 0xB7);
    LCD_Wr_Reg_Data(0xD126, 0x02);
    LCD_Wr_Reg_Data(0xD127, 0xCF);
    LCD_Wr_Reg_Data(0xD128, 0x02);
    LCD_Wr_Reg_Data(0xD129, 0xDE);
    LCD_Wr_Reg_Data(0xD12A, 0x02);
    LCD_Wr_Reg_Data(0xD12B, 0xF2);
    LCD_Wr_Reg_Data(0xD12C, 0x02);
    LCD_Wr_Reg_Data(0xD12D, 0xFE);
    LCD_Wr_Reg_Data(0xD12E, 0x03);
    LCD_Wr_Reg_Data(0xD12F, 0x10);
    LCD_Wr_Reg_Data(0xD130, 0x03);
    LCD_Wr_Reg_Data(0xD131, 0x33);
    LCD_Wr_Reg_Data(0xD132, 0x03);
    LCD_Wr_Reg_Data(0xD133, 0x6D);
    LCD_Wr_Reg_Data(0xD200, 0x00);
    LCD_Wr_Reg_Data(0xD201, 0x33);
    LCD_Wr_Reg_Data(0xD202, 0x00);
    LCD_Wr_Reg_Data(0xD203, 0x34);
    LCD_Wr_Reg_Data(0xD204, 0x00);
    LCD_Wr_Reg_Data(0xD205, 0x3A);
    LCD_Wr_Reg_Data(0xD206, 0x00);
    LCD_Wr_Reg_Data(0xD207, 0x4A);
    LCD_Wr_Reg_Data(0xD208, 0x00);
    LCD_Wr_Reg_Data(0xD209, 0x5C);
    LCD_Wr_Reg_Data(0xD20A, 0x00);

    LCD_Wr_Reg_Data(0xD20B, 0x81);
    LCD_Wr_Reg_Data(0xD20C, 0x00);
    LCD_Wr_Reg_Data(0xD20D, 0xA6);
    LCD_Wr_Reg_Data(0xD20E, 0x00);
    LCD_Wr_Reg_Data(0xD20F, 0xE5);
    LCD_Wr_Reg_Data(0xD210, 0x01);
    LCD_Wr_Reg_Data(0xD211, 0x13);
    LCD_Wr_Reg_Data(0xD212, 0x01);
    LCD_Wr_Reg_Data(0xD213, 0x54);
    LCD_Wr_Reg_Data(0xD214, 0x01);
    LCD_Wr_Reg_Data(0xD215, 0x82);
    LCD_Wr_Reg_Data(0xD216, 0x01);
    LCD_Wr_Reg_Data(0xD217, 0xCA);
    LCD_Wr_Reg_Data(0xD218, 0x02);
    LCD_Wr_Reg_Data(0xD219, 0x00);
    LCD_Wr_Reg_Data(0xD21A, 0x02);
    LCD_Wr_Reg_Data(0xD21B, 0x01);
    LCD_Wr_Reg_Data(0xD21C, 0x02);
    LCD_Wr_Reg_Data(0xD21D, 0x34);
    LCD_Wr_Reg_Data(0xD21E, 0x02);
    LCD_Wr_Reg_Data(0xD21F, 0x67);
    LCD_Wr_Reg_Data(0xD220, 0x02);
    LCD_Wr_Reg_Data(0xD221, 0x84);
    LCD_Wr_Reg_Data(0xD222, 0x02);
    LCD_Wr_Reg_Data(0xD223, 0xA4);
    LCD_Wr_Reg_Data(0xD224, 0x02);
    LCD_Wr_Reg_Data(0xD225, 0xB7);
    LCD_Wr_Reg_Data(0xD226, 0x02);
    LCD_Wr_Reg_Data(0xD227, 0xCF);
    LCD_Wr_Reg_Data(0xD228, 0x02);
    LCD_Wr_Reg_Data(0xD229, 0xDE);
    LCD_Wr_Reg_Data(0xD22A, 0x02);
    LCD_Wr_Reg_Data(0xD22B, 0xF2);
    LCD_Wr_Reg_Data(0xD22C, 0x02);
    LCD_Wr_Reg_Data(0xD22D, 0xFE);
    LCD_Wr_Reg_Data(0xD22E, 0x03);
    LCD_Wr_Reg_Data(0xD22F, 0x10);
    LCD_Wr_Reg_Data(0xD230, 0x03);
    LCD_Wr_Reg_Data(0xD231, 0x33);
    LCD_Wr_Reg_Data(0xD232, 0x03);
    LCD_Wr_Reg_Data(0xD233, 0x6D);
    LCD_Wr_Reg_Data(0xD300, 0x00);
    LCD_Wr_Reg_Data(0xD301, 0x33);
    LCD_Wr_Reg_Data(0xD302, 0x00);
    LCD_Wr_Reg_Data(0xD303, 0x34);
    LCD_Wr_Reg_Data(0xD304, 0x00);
    LCD_Wr_Reg_Data(0xD305, 0x3A);
    LCD_Wr_Reg_Data(0xD306, 0x00);
    LCD_Wr_Reg_Data(0xD307, 0x4A);
    LCD_Wr_Reg_Data(0xD308, 0x00);
    LCD_Wr_Reg_Data(0xD309, 0x5C);
    LCD_Wr_Reg_Data(0xD30A, 0x00);

    LCD_Wr_Reg_Data(0xD30B, 0x81);
    LCD_Wr_Reg_Data(0xD30C, 0x00);
    LCD_Wr_Reg_Data(0xD30D, 0xA6);
    LCD_Wr_Reg_Data(0xD30E, 0x00);
    LCD_Wr_Reg_Data(0xD30F, 0xE5);
    LCD_Wr_Reg_Data(0xD310, 0x01);
    LCD_Wr_Reg_Data(0xD311, 0x13);
    LCD_Wr_Reg_Data(0xD312, 0x01);
    LCD_Wr_Reg_Data(0xD313, 0x54);
    LCD_Wr_Reg_Data(0xD314, 0x01);
    LCD_Wr_Reg_Data(0xD315, 0x82);
    LCD_Wr_Reg_Data(0xD316, 0x01);
    LCD_Wr_Reg_Data(0xD317, 0xCA);
    LCD_Wr_Reg_Data(0xD318, 0x02);
    LCD_Wr_Reg_Data(0xD319, 0x00);
    LCD_Wr_Reg_Data(0xD31A, 0x02);
    LCD_Wr_Reg_Data(0xD31B, 0x01);
    LCD_Wr_Reg_Data(0xD31C, 0x02);
    LCD_Wr_Reg_Data(0xD31D, 0x34);
    LCD_Wr_Reg_Data(0xD31E, 0x02);
    LCD_Wr_Reg_Data(0xD31F, 0x67);
    LCD_Wr_Reg_Data(0xD320, 0x02);
    LCD_Wr_Reg_Data(0xD321, 0x84);
    LCD_Wr_Reg_Data(0xD322, 0x02);
    LCD_Wr_Reg_Data(0xD323, 0xA4);
    LCD_Wr_Reg_Data(0xD324, 0x02);
    LCD_Wr_Reg_Data(0xD325, 0xB7);
    LCD_Wr_Reg_Data(0xD326, 0x02);
    LCD_Wr_Reg_Data(0xD327, 0xCF);
    LCD_Wr_Reg_Data(0xD328, 0x02);
    LCD_Wr_Reg_Data(0xD329, 0xDE);
    LCD_Wr_Reg_Data(0xD32A, 0x02);
    LCD_Wr_Reg_Data(0xD32B, 0xF2);
    LCD_Wr_Reg_Data(0xD32C, 0x02);
    LCD_Wr_Reg_Data(0xD32D, 0xFE);
    LCD_Wr_Reg_Data(0xD32E, 0x03);
    LCD_Wr_Reg_Data(0xD32F, 0x10);
    LCD_Wr_Reg_Data(0xD330, 0x03);
    LCD_Wr_Reg_Data(0xD331, 0x33);
    LCD_Wr_Reg_Data(0xD332, 0x03);
    LCD_Wr_Reg_Data(0xD333, 0x6D);
    LCD_Wr_Reg_Data(0xD400, 0x00);
    LCD_Wr_Reg_Data(0xD401, 0x33);
    LCD_Wr_Reg_Data(0xD402, 0x00);
    LCD_Wr_Reg_Data(0xD403, 0x34);
    LCD_Wr_Reg_Data(0xD404, 0x00);
    LCD_Wr_Reg_Data(0xD405, 0x3A);
    LCD_Wr_Reg_Data(0xD406, 0x00);
    LCD_Wr_Reg_Data(0xD407, 0x4A);
    LCD_Wr_Reg_Data(0xD408, 0x00);
    LCD_Wr_Reg_Data(0xD409, 0x5C);
    LCD_Wr_Reg_Data(0xD40A, 0x00);
    LCD_Wr_Reg_Data(0xD40B, 0x81);

    LCD_Wr_Reg_Data(0xD40C, 0x00);
    LCD_Wr_Reg_Data(0xD40D, 0xA6);
    LCD_Wr_Reg_Data(0xD40E, 0x00);
    LCD_Wr_Reg_Data(0xD40F, 0xE5);
    LCD_Wr_Reg_Data(0xD410, 0x01);
    LCD_Wr_Reg_Data(0xD411, 0x13);
    LCD_Wr_Reg_Data(0xD412, 0x01);
    LCD_Wr_Reg_Data(0xD413, 0x54);
    LCD_Wr_Reg_Data(0xD414, 0x01);
    LCD_Wr_Reg_Data(0xD415, 0x82);
    LCD_Wr_Reg_Data(0xD416, 0x01);
    LCD_Wr_Reg_Data(0xD417, 0xCA);
    LCD_Wr_Reg_Data(0xD418, 0x02);
    LCD_Wr_Reg_Data(0xD419, 0x00);
    LCD_Wr_Reg_Data(0xD41A, 0x02);
    LCD_Wr_Reg_Data(0xD41B, 0x01);
    LCD_Wr_Reg_Data(0xD41C, 0x02);
    LCD_Wr_Reg_Data(0xD41D, 0x34);
    LCD_Wr_Reg_Data(0xD41E, 0x02);
    LCD_Wr_Reg_Data(0xD41F, 0x67);
    LCD_Wr_Reg_Data(0xD420, 0x02);
    LCD_Wr_Reg_Data(0xD421, 0x84);
    LCD_Wr_Reg_Data(0xD422, 0x02);
    LCD_Wr_Reg_Data(0xD423, 0xA4);
    LCD_Wr_Reg_Data(0xD424, 0x02);
    LCD_Wr_Reg_Data(0xD425, 0xB7);
    LCD_Wr_Reg_Data(0xD426, 0x02);
    LCD_Wr_Reg_Data(0xD427, 0xCF);
    LCD_Wr_Reg_Data(0xD428, 0x02);
    LCD_Wr_Reg_Data(0xD429, 0xDE);
    LCD_Wr_Reg_Data(0xD42A, 0x02);
    LCD_Wr_Reg_Data(0xD42B, 0xF2);
    LCD_Wr_Reg_Data(0xD42C, 0x02);
    LCD_Wr_Reg_Data(0xD42D, 0xFE);
    LCD_Wr_Reg_Data(0xD42E, 0x03);
    LCD_Wr_Reg_Data(0xD42F, 0x10);
    LCD_Wr_Reg_Data(0xD430, 0x03);
    LCD_Wr_Reg_Data(0xD431, 0x33);
    LCD_Wr_Reg_Data(0xD432, 0x03);
    LCD_Wr_Reg_Data(0xD433, 0x6D);
    LCD_Wr_Reg_Data(0xD500, 0x00);
    LCD_Wr_Reg_Data(0xD501, 0x33);
    LCD_Wr_Reg_Data(0xD502, 0x00);
    LCD_Wr_Reg_Data(0xD503, 0x34);
    LCD_Wr_Reg_Data(0xD504, 0x00);
    LCD_Wr_Reg_Data(0xD505, 0x3A);
    LCD_Wr_Reg_Data(0xD506, 0x00);
    LCD_Wr_Reg_Data(0xD507, 0x4A);
    LCD_Wr_Reg_Data(0xD508, 0x00);
    LCD_Wr_Reg_Data(0xD509, 0x5C);
    LCD_Wr_Reg_Data(0xD50A, 0x00);
    LCD_Wr_Reg_Data(0xD50B, 0x81);

    LCD_Wr_Reg_Data(0xD50C, 0x00);
    LCD_Wr_Reg_Data(0xD50D, 0xA6);
    LCD_Wr_Reg_Data(0xD50E, 0x00);
    LCD_Wr_Reg_Data(0xD50F, 0xE5);
    LCD_Wr_Reg_Data(0xD510, 0x01);
    LCD_Wr_Reg_Data(0xD511, 0x13);
    LCD_Wr_Reg_Data(0xD512, 0x01);
    LCD_Wr_Reg_Data(0xD513, 0x54);
    LCD_Wr_Reg_Data(0xD514, 0x01);
    LCD_Wr_Reg_Data(0xD515, 0x82);
    LCD_Wr_Reg_Data(0xD516, 0x01);
    LCD_Wr_Reg_Data(0xD517, 0xCA);
    LCD_Wr_Reg_Data(0xD518, 0x02);
    LCD_Wr_Reg_Data(0xD519, 0x00);
    LCD_Wr_Reg_Data(0xD51A, 0x02);
    LCD_Wr_Reg_Data(0xD51B, 0x01);
    LCD_Wr_Reg_Data(0xD51C, 0x02);
    LCD_Wr_Reg_Data(0xD51D, 0x34);
    LCD_Wr_Reg_Data(0xD51E, 0x02);
    LCD_Wr_Reg_Data(0xD51F, 0x67);
    LCD_Wr_Reg_Data(0xD520, 0x02);
    LCD_Wr_Reg_Data(0xD521, 0x84);
    LCD_Wr_Reg_Data(0xD522, 0x02);
    LCD_Wr_Reg_Data(0xD523, 0xA4);
    LCD_Wr_Reg_Data(0xD524, 0x02);
    LCD_Wr_Reg_Data(0xD525, 0xB7);
    LCD_Wr_Reg_Data(0xD526, 0x02);
    LCD_Wr_Reg_Data(0xD527, 0xCF);
    LCD_Wr_Reg_Data(0xD528, 0x02);
    LCD_Wr_Reg_Data(0xD529, 0xDE);
    LCD_Wr_Reg_Data(0xD52A, 0x02);
    LCD_Wr_Reg_Data(0xD52B, 0xF2);
    LCD_Wr_Reg_Data(0xD52C, 0x02);
    LCD_Wr_Reg_Data(0xD52D, 0xFE);
    LCD_Wr_Reg_Data(0xD52E, 0x03);
    LCD_Wr_Reg_Data(0xD52F, 0x10);
    LCD_Wr_Reg_Data(0xD530, 0x03);
    LCD_Wr_Reg_Data(0xD531, 0x33);
    LCD_Wr_Reg_Data(0xD532, 0x03);
    LCD_Wr_Reg_Data(0xD533, 0x6D);
    LCD_Wr_Reg_Data(0xD600, 0x00);
    LCD_Wr_Reg_Data(0xD601, 0x33);
    LCD_Wr_Reg_Data(0xD602, 0x00);
    LCD_Wr_Reg_Data(0xD603, 0x34);
    LCD_Wr_Reg_Data(0xD604, 0x00);
    LCD_Wr_Reg_Data(0xD605, 0x3A);
    LCD_Wr_Reg_Data(0xD606, 0x00);
    LCD_Wr_Reg_Data(0xD607, 0x4A);
    LCD_Wr_Reg_Data(0xD608, 0x00);
    LCD_Wr_Reg_Data(0xD609, 0x5C);
    LCD_Wr_Reg_Data(0xD60A, 0x00);
    LCD_Wr_Reg_Data(0xD60B, 0x81);

    LCD_Wr_Reg_Data(0xD60C, 0x00);
    LCD_Wr_Reg_Data(0xD60D, 0xA6);
    LCD_Wr_Reg_Data(0xD60E, 0x00);
    LCD_Wr_Reg_Data(0xD60F, 0xE5);
    LCD_Wr_Reg_Data(0xD610, 0x01);
    LCD_Wr_Reg_Data(0xD611, 0x13);
    LCD_Wr_Reg_Data(0xD612, 0x01);
    LCD_Wr_Reg_Data(0xD613, 0x54);
    LCD_Wr_Reg_Data(0xD614, 0x01);
    LCD_Wr_Reg_Data(0xD615, 0x82);
    LCD_Wr_Reg_Data(0xD616, 0x01);
    LCD_Wr_Reg_Data(0xD617, 0xCA);
    LCD_Wr_Reg_Data(0xD618, 0x02);
    LCD_Wr_Reg_Data(0xD619, 0x00);
    LCD_Wr_Reg_Data(0xD61A, 0x02);
    LCD_Wr_Reg_Data(0xD61B, 0x01);
    LCD_Wr_Reg_Data(0xD61C, 0x02);
    LCD_Wr_Reg_Data(0xD61D, 0x34);
    LCD_Wr_Reg_Data(0xD61E, 0x02);
    LCD_Wr_Reg_Data(0xD61F, 0x67);
    LCD_Wr_Reg_Data(0xD620, 0x02);
    LCD_Wr_Reg_Data(0xD621, 0x84);
    LCD_Wr_Reg_Data(0xD622, 0x02);
    LCD_Wr_Reg_Data(0xD623, 0xA4);
    LCD_Wr_Reg_Data(0xD624, 0x02);
    LCD_Wr_Reg_Data(0xD625, 0xB7);
    LCD_Wr_Reg_Data(0xD626, 0x02);
    LCD_Wr_Reg_Data(0xD627, 0xCF);
    LCD_Wr_Reg_Data(0xD628, 0x02);
    LCD_Wr_Reg_Data(0xD629, 0xDE);
    LCD_Wr_Reg_Data(0xD62A, 0x02);
    LCD_Wr_Reg_Data(0xD62B, 0xF2);
    LCD_Wr_Reg_Data(0xD62C, 0x02);
    LCD_Wr_Reg_Data(0xD62D, 0xFE);
    LCD_Wr_Reg_Data(0xD62E, 0x03);
    LCD_Wr_Reg_Data(0xD62F, 0x10);
    LCD_Wr_Reg_Data(0xD630, 0x03);
    LCD_Wr_Reg_Data(0xD631, 0x33);
    LCD_Wr_Reg_Data(0xD632, 0x03);
    LCD_Wr_Reg_Data(0xD633, 0x6D);
    /* LV2 Page 0 enable */
    LCD_Wr_Reg_Data(0xF000, 0x55);
    LCD_Wr_Reg_Data(0xF001, 0xAA);
    LCD_Wr_Reg_Data(0xF002, 0x52);
    LCD_Wr_Reg_Data(0xF003, 0x08);
    LCD_Wr_Reg_Data(0xF004, 0x00);
    /* Display control */
    LCD_Wr_Reg_Data(0xB100, 0xCC);
    LCD_Wr_Reg_Data(0xB101, 0x00);
    /* Source hold time */
    LCD_Wr_Reg_Data(0xB600, 0x05);
    /* Gate EQ control */
    LCD_Wr_Reg_Data(0xB700, 0x70);
    LCD_Wr_Reg_Data(0xB701, 0x70);
    /* Source EQ control (Mode 2) */
    LCD_Wr_Reg_Data(0xB800, 0x01);
    LCD_Wr_Reg_Data(0xB801, 0x03);
    LCD_Wr_Reg_Data(0xB802, 0x03);
    LCD_Wr_Reg_Data(0xB803, 0x03);
    /* Inversion mode (2-dot) */
    LCD_Wr_Reg_Data(0xBC00, 0x02);
    LCD_Wr_Reg_Data(0xBC01, 0x00);
    LCD_Wr_Reg_Data(0xBC02, 0x00);
    /* Timing control 4H w/ 4-delay */
    LCD_Wr_Reg_Data(0xC900, 0xD0);
    LCD_Wr_Reg_Data(0xC901, 0x02);
    LCD_Wr_Reg_Data(0xC902, 0x50);
    LCD_Wr_Reg_Data(0xC903, 0x50);
    LCD_Wr_Reg_Data(0xC904, 0x50);
    LCD_Wr_Reg_Data(0x3500, 0x00);
    LCD_Wr_Reg_Data(0x3A00, 0x55); /* 16-bit/pixel */
    LCD_Wr_Reg(0x1100);
    tim6_delay_us(120);
    LCD_Wr_Reg(0x2900);
}

void LCD_Ex_Ili9806_Reginit(void)
{
    LCD_Wr_Reg(0xFF); /* EXTC Command Set enable register */
    LCD_Wr_Data(0xFF);
    LCD_Wr_Data(0x98);
    LCD_Wr_Data(0x06);

    LCD_Wr_Reg(0xBC); /* GIP 1 */
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x0F);
    LCD_Wr_Data(0x61);
    LCD_Wr_Data(0xFF);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x0B);
    LCD_Wr_Data(0x10);
    LCD_Wr_Data(0x37);
    LCD_Wr_Data(0x63);
    LCD_Wr_Data(0xFF);
    LCD_Wr_Data(0xFF);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0xFF);
    LCD_Wr_Data(0x52);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x40);

    LCD_Wr_Reg(0xBD); /* GIP 2 */
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x23);
    LCD_Wr_Data(0x45);
    LCD_Wr_Data(0x67);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0x23);
    LCD_Wr_Data(0x45);
    LCD_Wr_Data(0x67);

    LCD_Wr_Reg(0xBE); /* GIP 3 */
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0xAB);
    LCD_Wr_Data(0x60);
    LCD_Wr_Data(0x22);
    LCD_Wr_Data(0x22);
    LCD_Wr_Data(0x22);
    LCD_Wr_Data(0x22);
    LCD_Wr_Data(0x22);

    LCD_Wr_Reg(0xC7); /* VCOM Control */
    LCD_Wr_Data(0x36);

    LCD_Wr_Reg(0xED); /* EN_volt_reg VGMP / VGMN /VGSP / VGSN voltage to output */
    LCD_Wr_Data(0x7F);
    LCD_Wr_Data(0x0F);

    LCD_Wr_Reg(0XC0); /* Power Control 1 Setting AVDD / AVEE / VGH / VGL */
    LCD_Wr_Data(0x0F);
    LCD_Wr_Data(0x0B);
    LCD_Wr_Data(0x0A);  /* VGH 15V,VGLO-10V */

    LCD_Wr_Reg(0XFC); /* AVDD / AVEE generated by internal pumping. */
    LCD_Wr_Data(0x08);

    LCD_Wr_Reg(0XDF); 
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x20);

    LCD_Wr_Reg(0XF3); /* DVDD Voltage Setting */
    LCD_Wr_Data(0x74);

    LCD_Wr_Reg(0xB4); /* Inversion Type */
    LCD_Wr_Data(0x00);  /* 02 */
    LCD_Wr_Data(0x00);  /* 02 */
    LCD_Wr_Data(0x00);  /* 02 */

    LCD_Wr_Reg(0xF7); /* Resolution Control */
    LCD_Wr_Data(0x82);  /* 480*800 */

    LCD_Wr_Reg(0xB1); /* FRAME RATE Setting */
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x13);
    LCD_Wr_Data(0x13); 

    LCD_Wr_Reg(0XF2); /* CR_EQ_PC_SDT  #C0,06,40,28 */
    LCD_Wr_Data(0x80);
    LCD_Wr_Data(0x04);
    LCD_Wr_Data(0x40);
    LCD_Wr_Data(0x28);

    LCD_Wr_Reg(0XC1); /* Power Control 2  SD OP Bias_VRH1_VRH2_EXT_CPCK_SEL */
    LCD_Wr_Data(0x17);
    LCD_Wr_Data(0x88);  /* VGMP */
    LCD_Wr_Data(0x88);  /* VGMN */
    LCD_Wr_Data(0x20);

    LCD_Wr_Reg(0xE0); /* Positive Gamma Control */
    LCD_Wr_Data(0x00);  /* P1 */
    LCD_Wr_Data(0x0A);  /* P2 */
    LCD_Wr_Data(0x12);  /* P3 */
    LCD_Wr_Data(0x10);  /* P4 */
    LCD_Wr_Data(0x0E);  /* P5 */
    LCD_Wr_Data(0x20);  /* P6 */
    LCD_Wr_Data(0xCC);  /* P7 */
    LCD_Wr_Data(0x07);  /* P8 */
    LCD_Wr_Data(0x06);  /* P9 */
    LCD_Wr_Data(0x0B);  /* P10 */
    LCD_Wr_Data(0x0E);  /* P11 */
    LCD_Wr_Data(0x0F);  /* P12 */
    LCD_Wr_Data(0x0D);  /* P13 */
    LCD_Wr_Data(0x15);  /* P14 */
    LCD_Wr_Data(0x10);  /* P15 */
    LCD_Wr_Data(0x00);  /* P16 */

    LCD_Wr_Reg(0xE1); /* Negative Gamma Correction */
    LCD_Wr_Data(0x00);  /* P1 */
    LCD_Wr_Data(0x0B);  /* P2 */
    LCD_Wr_Data(0x13);  /* P3 */
    LCD_Wr_Data(0x0D);  /* P4 */
    LCD_Wr_Data(0x0E);  /* P5 */
    LCD_Wr_Data(0x1B);  /* P6 */
    LCD_Wr_Data(0x71);  /* P7 */
    LCD_Wr_Data(0x06);  /* P8 */
    LCD_Wr_Data(0x06);  /* P9 */
    LCD_Wr_Data(0x0A);  /* P10 */
    LCD_Wr_Data(0x0F);  /* P11 */
    LCD_Wr_Data(0x0E);  /* P12 */
    LCD_Wr_Data(0x0F);  /* P13 */
    LCD_Wr_Data(0x15);  /* P14 */
    LCD_Wr_Data(0x0C);  /* P15 */
    LCD_Wr_Data(0x00);  /* P16 */

    LCD_Wr_Reg(0x2a);   
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x01);
    LCD_Wr_Data(0xdf);

    LCD_Wr_Reg(0x2b);   
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x03);
    LCD_Wr_Data(0x1f);

    LCD_Wr_Reg(0x3A); /* Pixel Format */
    LCD_Wr_Data(0x55);

    LCD_Wr_Reg(0x36); /* Memory Access Control */
    LCD_Wr_Data(0x00);  /* 02-180 */

    LCD_Wr_Reg(0x11);
    tim6_delay_ms(120);   
    LCD_Wr_Reg(0x29);  
    tim6_delay_ms(20);  
    LCD_Wr_Reg(0x2C);
}

void LCD_Ex_Ssd1963_Reginit(void)
{
    LCD_Wr_Reg(0xE2); /* Set PLL with OSC = 10MHz (hardware), Multiplier N = 35, 250MHz < VCO < 800MHz = OSC*(N+1), VCO = 300MHz */
    LCD_Wr_Data(0x1D);  /* Parameter 1 */
    LCD_Wr_Data(0x02);  /* Parameter 2 Divider M = 2, PLL = 300/(M+1) = 100MHz */
    LCD_Wr_Data(0x04);  /* Parameter 3 Validate M and N values */
    tim6_delay_us(100);
    LCD_Wr_Reg(0xE0); /* Start PLL command */
    LCD_Wr_Data(0x01);  /* Enable PLL */
    tim6_delay_ms(10);
    LCD_Wr_Reg(0xE0); /* Start PLL command again */
    LCD_Wr_Data(0x03);  /* Now, use PLL output as system clock */
    tim6_delay_ms(12);
    LCD_Wr_Reg(0x01); /* Soft reset */
    tim6_delay_ms(10);

    LCD_Wr_Reg(0xE6); /* Set pixel frequency, 33MHz */
    LCD_Wr_Data(0x2F);
    LCD_Wr_Data(0xFF);
    LCD_Wr_Data(0xFF);

    LCD_Wr_Reg(0xB0); /* Set LCD mode */
    LCD_Wr_Data(0x20);  /* 24-bit mode */
    LCD_Wr_Data(0x00);  /* TFT mode */

    LCD_Wr_Data((SSD_HOR_RESOLUTION - 1) >> 8); /* Set LCD horizontal pixels */
    LCD_Wr_Data(SSD_HOR_RESOLUTION - 1);
    LCD_Wr_Data((SSD_VER_RESOLUTION - 1) >> 8); /* Set LCD vertical pixels */
    LCD_Wr_Data(SSD_VER_RESOLUTION - 1);
    LCD_Wr_Data(0x00);  /* RGB sequence */

    LCD_Wr_Reg(0xB4); /* Set horizontal period */
    LCD_Wr_Data((SSD_HT - 1) >> 8);
    LCD_Wr_Data(SSD_HT - 1);
    LCD_Wr_Data(SSD_HPS >> 8);
    LCD_Wr_Data(SSD_HPS);
    LCD_Wr_Data(SSD_HOR_PULSE_WIDTH - 1);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);
    LCD_Wr_Reg(0xB6); /* Set vertical period */
    LCD_Wr_Data((SSD_VT - 1) >> 8);
    LCD_Wr_Data(SSD_VT - 1);
    LCD_Wr_Data(SSD_VPS >> 8);
    LCD_Wr_Data(SSD_VPS);
    LCD_Wr_Data(SSD_VER_FRONT_PORCH - 1);
    LCD_Wr_Data(0x00);
    LCD_Wr_Data(0x00);

    LCD_Wr_Reg(0xF0); /* Set SSD1963 and CPU interface to 16-bit */
    LCD_Wr_Data(0x03);  /* 16-bit (565 format) data for 16bpp */

    LCD_Wr_Reg(0x29); /* Turn on display */
    /* Set PWM output, backlight adjustable via duty cycle */
    LCD_Wr_Reg(0xD0); /* Set automatic white balance DBC */
    LCD_Wr_Data(0x00);  /* Disable */

    LCD_Wr_Reg(0xBE); /* Configure PWM output */
    LCD_Wr_Data(0x05);  /* Set PWM frequency */
    LCD_Wr_Data(0xFE);  /* Set PWM duty cycle */
    LCD_Wr_Data(0x01);  /* Set C */
    LCD_Wr_Data(0x00);  /* Set D */
    LCD_Wr_Data(0x00);  /* Set E */
    LCD_Wr_Data(0x00);  /* Set F */

    LCD_Wr_Reg(0xB8); /* Set GPIO configuration */
    LCD_Wr_Data(0x03);  /* Set 2 IO ports to output */
    LCD_Wr_Data(0x01);  /* GPIO uses normal IO function */
    LCD_Wr_Reg(0xBA);
    LCD_Wr_Data(0X01);  /* GPIO[1:0]=01, control LCD direction */
}