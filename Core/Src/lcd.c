#include "fsmc.h"
#include "gpio.h"
#include "lcd.h"
#include "utils.h"
#include "lcdfont.h"
#include "camera.h"
#include "utils.h"
#include "delay.h"
#include <stdio.h>


// SRAM_HandleTypeDef                      g_sram_handle;  // for control lcd

uint32_t                                g_point_color = RED;
uint32_t                                g_back_color = WHITE;

// manage lcd parameter
_LCD_DEVICE                             lcddev;

DMA_HandleTypeDef                       dma_handle;

// void temp_dma_init(void)
// {
//     OV2640_DMA_CLK_ENABLE();

//     dma_handle.Instance                 = OV2640_DMA_INTERFACE;
//     dma_handle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
//     dma_handle.Init.PeriphInc           = DMA_PINC_ENABLE;
//     dma_handle.Init.MemInc              = DMA_MINC_DISABLE;
//     dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
//     dma_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
//     dma_handle.Init.Mode                = DMA_NORMAL;
//     dma_handle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;

//     HAL_DMA_Init(&dma_handle);
// }


static void LCD_Opt_Delay(uint32_t i)
{
    while(i--);  // unit, ns
}

void LCD_Wr_Reg(volatile uint16_t regno)
{
    // actually it set bit of the chip rs, which means the following send data is a command
    LCD->_REG = regno;
}

void LCD_Wr_Data(volatile uint16_t data)
{
    LCD->_RAM = data;
}

void LCD_Wr_Reg_Data(uint16_t regno, uint16_t data)
{
    LCD_Wr_Reg(regno);
    LCD_Wr_Data(data);
}

uint16_t LCD_Rr_Data(void)
{
    volatile uint16_t ram;
    LCD_Opt_Delay(2);
    ram = LCD->_RAM;
    return ram;
}

void LCD_Set_Cursor(uint16_t x, uint16_t y)
{  // set coordinate according to 9341/5310/7789/7796/9806, driver type
    if(lcddev.id == 0x1963)
    {
        if(lcddev.dir == 0)
        {
            x = lcddev.width - 1 - x;
            LCD_Wr_Reg(lcddev.setxcmd);
            LCD_Wr_Data(0);
            LCD_Wr_Data(0);
            LCD_Wr_Data(x >> 8);
            LCD_Wr_Data(x & 0xFF);
        } else
        {
            LCD_Wr_Reg(lcddev.setxcmd);
            LCD_Wr_Data(x >> 8);
            LCD_Wr_Data(x & 0xFF);
            LCD_Wr_Data((lcddev.width - 1) >> 8);
            LCD_Wr_Data((lcddev.width - 1) & 0xFF);
        }
        LCD_Wr_Reg(lcddev.setycmd);
        LCD_Wr_Data(y >> 8);
        LCD_Wr_Data(y & 0xFF);
        LCD_Wr_Data((lcddev.height - 1) >> 8);
        LCD_Wr_Data((lcddev.height - 1) & 0xFF);
    } else if(lcddev.id == 0X5510)
    {
        LCD_Wr_Reg(lcddev.setxcmd);
        LCD_Wr_Data(x >> 8);
        LCD_Wr_Reg(lcddev.setxcmd + 1);
        LCD_Wr_Data(x & 0XFF);
        LCD_Wr_Reg(lcddev.setycmd);
        LCD_Wr_Data(y >> 8);
        LCD_Wr_Reg(lcddev.setycmd + 1);
        LCD_Wr_Data(y & 0XFF);
    } else  // 9341/5310/7789/7796/9806
    {
        LCD_Wr_Reg(lcddev.setxcmd);
        LCD_Wr_Data(x >> 8);
        LCD_Wr_Data(x & 0XFF);
        LCD_Wr_Reg(lcddev.setycmd);
        LCD_Wr_Data(y >> 8);
        LCD_Wr_Data(y & 0XFF);
    }
}

void LCD_Wr_Ram_Prepare(void)
{
    LCD->_REG = lcddev.wramcmd;
}

void LCD_Draw_Point(uint16_t x, uint16_t y, uint16_t color)
{
    // temp_dma_init();
    // HAL_DMA_Abort(&dma_handle);
    LCD_Set_Cursor(x, y);
    LCD_Wr_Ram_Prepare();
    // HAL_DMA_Start(&dma_handle, (uint32_t) &color, (uint32_t) &LCD->_RAM, 1);
    LCD->_RAM = color;
}

void LCD_Clear(uint16_t color)
{
    uint32_t index      = 0;
    uint32_t totalpoint = lcddev.width;
    totalpoint *= lcddev.height;
    LCD_Set_Cursor(0x00, 0x0000);
    LCD_Wr_Ram_Prepare();
    for(index = 0; index < totalpoint; index++)
    {
        LCD->_RAM = color;
    }
}

void LCD_Ssd_Backlight_Set(uint8_t pwm)
{
    LCD_Wr_Reg(0xBE);         //  Configure PWM output
    LCD_Wr_Data(0x05);        //  1. Set PWM frequency
    LCD_Wr_Data(pwm * 2.55);  //  2. Set PWM duty cycle
    LCD_Wr_Data(0x01);        //  3. Set C
    LCD_Wr_Data(0xFF);        //  4. Set D
    LCD_Wr_Data(0x00);        //  5. Set E
    LCD_Wr_Data(0x00);        //  6. Set F
}

static uint16_t LCD_Rd_Data(void)
{
    volatile uint16_t ram;
    LCD_Opt_Delay(2);
    ram = LCD->_RAM;
    return ram;
}

void LCD_Scan_Dir(uint8_t dir)
{
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;

    //  In landscape mode, do not change the scan direction for 1963, change for other ICs. In portrait mode, change
    //  direction for 1963, do not change for other ICs
    if((lcddev.dir == 1 && lcddev.id != 0X1963) || (lcddev.dir == 0 && lcddev.id == 0X1963))
    {
        switch(dir)  //  Direction conversion
        {
            case 0:
                dir = 6;
                break;

            case 1:
                dir = 7;
                break;

            case 2:
                dir = 4;
                break;

            case 3:
                dir = 5;
                break;

            case 4:
                dir = 1;
                break;

            case 5:
                dir = 0;
                break;

            case 6:
                dir = 3;
                break;

            case 7:
                dir = 2;
                break;
        }
    }

    //  Set the value of bits 5, 6, 7 of register 0X36/0X3600 according to the scan mode
    switch(dir)
    {
        case L2R_U2D:  //  From left to right, from top to bottom
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;

        case L2R_D2U:  //  From left to right, from bottom to top
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;

        case R2L_U2D:  //  From right to left, from top to bottom
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;

        case R2L_D2U:  //  From right to left, from bottom to top
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;

        case U2D_L2R:  //  From top to bottom, from left to right
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;

        case U2D_R2L:  //  From top to bottom, from right to left
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;

        case D2U_L2R:  //  From bottom to top, from left to right
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;

        case D2U_R2L:  //  From bottom to top, from right to left
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
    }

    dirreg = 0X36;  //  For most driver ICs, controlled by register 0X36

    if(lcddev.id == 0X5510)
    {
        dirreg = 0X3600;  //  For 5510, the register differs from other driver ICs
    }

    //  9341 & 7789 & 7796 need to set the BGR bit
    if(lcddev.id == 0X9341 || lcddev.id == 0X7789 || lcddev.id == 0x7796)
    {
        regval |= 0X08;
    }

    LCD_Wr_Reg_Data(dirreg, regval);

    if(lcddev.id != 0X1963)  //  1963 does not handle coordinates
    {
        if(regval & 0X20)
        {
            if(lcddev.width < lcddev.height)  //  Swap X, Y
            {
                temp          = lcddev.width;
                lcddev.width  = lcddev.height;
                lcddev.height = temp;
            }
        } else
        {
            if(lcddev.width > lcddev.height)  //  Swap X, Y
            {
                temp          = lcddev.width;
                lcddev.width  = lcddev.height;
                lcddev.height = temp;
            }
        }
    }

    //  Set the display area (window) size
    if(lcddev.id == 0X5510)
    {
        LCD_Wr_Reg(lcddev.setxcmd);
        LCD_Wr_Data(0);
        LCD_Wr_Reg(lcddev.setxcmd + 1);
        LCD_Wr_Data(0);
        LCD_Wr_Reg(lcddev.setxcmd + 2);
        LCD_Wr_Data((lcddev.width - 1) >> 8);
        LCD_Wr_Reg(lcddev.setxcmd + 3);
        LCD_Wr_Data((lcddev.width - 1) & 0XFF);
        LCD_Wr_Reg(lcddev.setycmd);
        LCD_Wr_Data(0);
        LCD_Wr_Reg(lcddev.setycmd + 1);
        LCD_Wr_Data(0);
        LCD_Wr_Reg(lcddev.setycmd + 2);
        LCD_Wr_Data((lcddev.height - 1) >> 8);
        LCD_Wr_Reg(lcddev.setycmd + 3);
        LCD_Wr_Data((lcddev.height - 1) & 0XFF);
    } else
    {
        LCD_Wr_Reg(lcddev.setxcmd);
        LCD_Wr_Data(0);
        LCD_Wr_Data(0);
        LCD_Wr_Data((lcddev.width - 1) >> 8);
        LCD_Wr_Data((lcddev.width - 1) & 0XFF);
        LCD_Wr_Reg(lcddev.setycmd);
        LCD_Wr_Data(0);
        LCD_Wr_Data(0);
        LCD_Wr_Data((lcddev.height - 1) >> 8);
        LCD_Wr_Data((lcddev.height - 1) & 0XFF);
    }
}

void LCD_Display_Dir(uint8_t dir)
{
    lcddev.dir = dir;  //  Portrait/Landscape mode

    if(dir == 0)  //  Portrait mode
    {
        lcddev.width  = 240;
        lcddev.height = 320;

        if(lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0X2C00;
            lcddev.setxcmd = 0X2A00;
            lcddev.setycmd = 0X2B00;
            lcddev.width   = 480;
            lcddev.height  = 800;
        } else if(lcddev.id == 0X1963)
        {
            lcddev.wramcmd = 0X2C;  //  Set command to write to GRAM
            lcddev.setxcmd = 0X2B;  //  Set command to write X coordinate
            lcddev.setycmd = 0X2A;  //  Set command to write Y coordinate
            lcddev.width   = 480;   //  Set width to 480
            lcddev.height  = 800;   //  Set height to 800
        } else                      //  Other ICs, including: 9341 / 5310 / 7789 / 7796 / 9806 etc.
        {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
        }

        if(lcddev.id == 0X5310 || lcddev.id == 0x7796)  //  If 5310/7796, resolution is 320*480
        {
            lcddev.width  = 320;
            lcddev.height = 480;
        }

        if(lcddev.id == 0X9806)  //  If 9806, resolution is 480*800
        {
            lcddev.width  = 480;
            lcddev.height = 800;
        }
    } else  //  Landscape mode
    {
        lcddev.width  = 320;  //  Default width
        lcddev.height = 240;  //  Default height

        if(lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0X2C00;
            lcddev.setxcmd = 0X2A00;
            lcddev.setycmd = 0X2B00;
            lcddev.width   = 800;
            lcddev.height  = 480;
        } else if(lcddev.id == 0X1963 || lcddev.id == 0x9806)
        {
            lcddev.wramcmd = 0X2C;  //  Set command to write to GRAM
            lcddev.setxcmd = 0X2A;  //  Set command to write X coordinate
            lcddev.setycmd = 0X2B;  //  Set command to write Y coordinate
            lcddev.width   = 800;   //  Set width to 800
            lcddev.height  = 480;   //  Set height to 480
        } else                      //  Other ICs, including: 9341 / 5310 / 7789 / 7796 etc.
        {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
        }

        if(lcddev.id == 0X5310 || lcddev.id == 0x7796)  //  If 5310/7796, resolution is 320*480
        {
            lcddev.width  = 480;
            lcddev.height = 320;
        }
    }

    LCD_Scan_Dir(DFT_SCAN_DIR);  //  Default scan direction
}

void LCD_Show_Char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t  temp, t1, t;
    uint16_t y0    = y;
    uint8_t  csize = 0;
    uint8_t *pfont = 0;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);  // Calculate the size of the font's character matrix in bytes
    chr = chr - ' ';                                     // Offset value to get the corresponding font library

    switch(size)
    {
        case 12:
            pfont = (uint8_t *)asc2_1206[(unsigned char)chr];  // Use 1206 font
            break;

        case 16:
            pfont = (uint8_t *)asc2_1608[(unsigned char)chr];  // Use 1608 font
            break;

        case 24:
            pfont = (uint8_t *)asc2_2412[(unsigned char)chr];  // Use 2412 font
            break;

        case 32:
            pfont = (uint8_t *)asc2_3216[(unsigned char)chr];  // Use 3216 font
            break;

        default:
            return;
    }

    for(t = 0; t < csize; t++)
    {
        temp = pfont[t];  // Get the character's matrix data

        for(t1 = 0; t1 < 8; t1++)  // Process each bit of a byte
        {
            if(temp & 0x80)  // If bit is set, draw the point
            {
                LCD_Draw_Point(x, y, color);
            } else if(mode == 0)  // If bit is not set and mode is 0, draw background color
            {
                LCD_Draw_Point(x, y, g_back_color);
            }

            temp <<= 1;  // Shift to get the next bit
            y++;

            if(y >= lcddev.height)
                return;  // If y exceeds screen height, exit

            if((y - y0) == size)  // If a column is finished
            {
                y = y0;  // Reset y coordinate
                x++;     // Move to next column

                if(x >= lcddev.width)
                    return;  // If x exceeds screen width, exit

                break;
            }
        }
    }
}

/**
 * @description: show a string
 * @param {uint16_t} x
 * @param {uint16_t} y
 * @param {uint16_t} width, width of show region
 * @param {uint16_t} height, height of show region
 * @param {uint8_t} fontsize
 * @param {char} *p
 * @param {uint16_t} color
 * @return {*}
 */
void LCD_Show_String(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)
{
    uint8_t x0 = x;
    width += x;
    height += y;

    while((*p <= '~') && (*p >= ' '))  // Check invalid character
    {
        if(x >= width)
        {
            x = x0;
            y += size;
        }

        if(y >= height)
            break;

        LCD_Show_Char(x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}

static uint32_t LCD_Pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;

    while(n--) result *= m;

    return result;
}

void LCD_Show_Xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t t, temp;
    uint8_t enshow = 0;

    for(t = 0; t < len; t++)  // Loop through total number of digits to display
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;  // Get the digit at the current position

        if(enshow == 0 && t < (len - 1))  //  Not enabled to display and there are more digits to display
        {
            if(temp == 0)
            {
                if(mode & 0X80)  // High position needs to be filled with 0
                {
                    LCD_Show_Char(x + (size / 2) * t, y, '0', size, mode & 0X01, color);  // Use 0 to fill
                } else
                {
                    LCD_Show_Char(x + (size / 2) * t, y, ' ', size, mode & 0X01, color);  // Use space to fill
                }

                continue;
            } else
            {
                enshow = 1;  // Enable display
            }
        }

        LCD_Show_Char(x + (size / 2) * t, y, temp + '0', size, mode & 0X01, color);
    }
}

void LCD_Init(void)
{
    printf("lcd id init\r\n");
    // FSMC_NORSRAM_TimingTypeDef          fsmc_read_handle;
    // FSMC_NORSRAM_TimingTypeDef          fsmc_write_handle;

    // g_sram_handle.Init.NSBank                           = FSMC_NORSRAM_BANK4;
    // g_sram_handle.Init.DataAddressMux                   = FSMC_DATA_ADDRESS_MUX_DISABLE;
    // g_sram_handle.Init.MemoryType                       = FSMC_MEMORY_TYPE_SRAM;
    // g_sram_handle.Init.MemoryDataWidth                  = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
    // g_sram_handle.Init.BurstAccessMode                  = FSMC_BURST_ACCESS_MODE_DISABLE;
    // g_sram_handle.Init.WaitSignalPolarity               = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    // g_sram_handle.Init.WrapMode                         = FSMC_WRAP_MODE_DISABLE;
    // g_sram_handle.Init.WaitSignalActive                 = FSMC_WAIT_TIMING_BEFORE_WS;
    // g_sram_handle.Init.WriteOperation                   = FSMC_WRITE_OPERATION_ENABLE;
    // g_sram_handle.Init.WaitSignal                       = FSMC_WAIT_SIGNAL_DISABLE;
    // g_sram_handle.Init.ExtendedMode                     = FSMC_EXTENDED_MODE_ENABLE;
    // g_sram_handle.Init.AsynchronousWait                 = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
    // g_sram_handle.Init.WriteBurst                       = FSMC_WRITE_BURST_DISABLE;

    // // Timing contrl
    // fsmc_read_handle.AccessMode                         = FSMC_ACCESS_MODE_A;
    // fsmc_read_handle.AddressSetupTime                   = 0;   // > 2 HCLK, 1/72M=13.9ns, actually > 200ns
    // fsmc_read_handle.AddressHoldTime                    = 0;   // no use
    // fsmc_read_handle.DataSetupTime                      = 15;  // HCLK = 13.9 * 16 = 222.4ns, better not ro fast

    // fsmc_write_handle.AccessMode                        = FSMC_ACCESS_MODE_A;
    // fsmc_write_handle.AddressSetupTime                  = 0;  // same as read
    // fsmc_write_handle.AddressHoldTime                   = 0;  // no use
    // fsmc_write_handle.DataSetupTime                     = 1;  // HCLK = 13.9 * 4 = 55.6ns , actually > 200ns
    // test1();
    // if(HAL_SRAM_Init(&g_sram_handle, &fsmc_read_handle, &fsmc_write_handle) != 0)
    // {
    //     Error_Handler();
    // }
    // test2();
    // tim6_delay_ms(50);

    LCD_Wr_Reg(0xD3);   // this cmd will return 4 parameters
    lcddev.id = LCD_Rd_Data();
    lcddev.id = LCD_Rd_Data();
    lcddev.id = LCD_Rd_Data();
    lcddev.id <<= 8;             // make it 16 bit, cat with next read
    lcddev.id |= LCD_Rd_Data();  // cat
    printf("lcd id: %x\n", lcddev.id);
    tim6_delay_ms(40);
    if(lcddev.id != 0x9341)
    {
        LCD_Wr_Reg(0x04);  // same as 0xD3
        lcddev.id = LCD_Rd_Data();
        lcddev.id = LCD_Rd_Data();
        lcddev.id = LCD_Rd_Data();
        lcddev.id <<= 8;             // make it 16 bit, cat with next read
        lcddev.id |= LCD_Rd_Data();  // cat

        if(lcddev.id == 0x8552)
        {
            lcddev.id = 0x7789;
        }
        if(lcddev.id != 0x7789)
        {
            LCD_Wr_Reg(0xD4);
            lcddev.id = LCD_Rd_Data();
            lcddev.id = LCD_Rd_Data();
            lcddev.id = LCD_Rd_Data();
            lcddev.id <<= 8;
            lcddev.id |= LCD_Rd_Data();

            if(lcddev.id != 0x5310)
            {
                LCD_Wr_Reg(0xD3);
                lcddev.id = LCD_Rd_Data();
                lcddev.id = LCD_Rd_Data();
                lcddev.id = LCD_Rd_Data();
                lcddev.id <<= 8;
                lcddev.id |= LCD_Rd_Data();

                if(lcddev.id != 0x7796)
                {
                    // send secret
                    LCD_Wr_Reg_Data(0xF000, 0x0055);
                    LCD_Wr_Reg_Data(0xF001, 0x00AA);
                    LCD_Wr_Reg_Data(0xF002, 0x0052);
                    LCD_Wr_Reg_Data(0xF003, 0x0008);
                    LCD_Wr_Reg_Data(0xF004, 0x0001);

                    LCD_Wr_Reg(0xC500);  // read lower 8 bits
                    lcddev.id = LCD_Rd_Data();
                    lcddev.id <<= 8;
                    LCD_Wr_Reg(0xC501);  // read higher 8 bits
                    lcddev.id |= LCD_Rd_Data();
                    tim6_delay_ms(5);  // unit ms, wait for soft-reset finish

                    if(lcddev.id != 0x5510)
                    {
                        LCD_Wr_Data(0xD3);
                        lcddev.id = LCD_Rd_Data();
                        lcddev.id = LCD_Rd_Data();
                        lcddev.id = LCD_Rd_Data();
                        lcddev.id <<= 8;
                        lcddev.id |= LCD_Rd_Data();

                        if(lcddev.id != 0x9806)
                        {
                            LCD_Wr_Reg(0xA1);
                            lcddev.id = LCD_Rd_Data();
                            lcddev.id = LCD_Rd_Data();
                            lcddev.id <<= 8;
                            lcddev.id |= LCD_Rd_Data();

                            if(lcddev.id == 0x5761)
                                lcddev.id = 0x1963;
                        }
                    }
                }
            }
        }
    }

    if(lcddev.id==0x7789)
    {
        LCD_Ex_St7789_Reginit();
    }
    else if(lcddev.id==0x9341)
    {
        LCD_Ex_Ili9341_Reginit();
    }
    else if(lcddev.id==0x5310)
    {
        LCD_Ex_Nt35310_Reginit();
    }
    else if(lcddev.id==0x7796)
    {
        LCD_Ex_St7796_Reginit();
    }
    else if(lcddev.id==0x5510)
    {
        LCD_Ex_Nt35510_Reginit();
    }
    else if(lcddev.id==0x9806)
    {
        LCD_Ex_Ili9806_Reginit();
        LCD_Ssd_Backlight_Set(100);
    }
    LCD_Display_Dir(0);  // default is 0
    LCD_BL(1);  // default is 1
    LCD_Clear(WHITE);
    printf("\r\n-------------- lcd Info beginning --------------\r\n");
    printf("lcd id: %x\r\n", lcddev.id);
    printf("lcd width x height: %d x %d\r\n", lcddev.width, lcddev.height);
    printf("lcd dir: %d\r\n", lcddev.dir);
    printf("----------------- lcd Info end -----------------\r\n");

}

