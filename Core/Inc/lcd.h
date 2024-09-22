#ifndef __LCD_H__
#define __LCD_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>

// led definition
#define LED0_GPIO_PORT                  GPIOB
#define LED0_GPIO_PIN                   GPIO_PIN_5
#define LED0(x)   do{ x ? HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET) : \
                        HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)

// toggle led
#define LED0_TOGGLE()   do{ HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN); }while(0)

#define LCD_BL_GPIO_Port                 GPIOB
#define LCD_BL_Pin                       GPIO_PIN_0
#define LCD_BL_GPIO_CLK_ENABLE()         do{__HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define LCD_CS_GPIO_Port                 GPIOG
#define LCD_CS_Pin                       GPIO_PIN_12
#define LCD_WR_GPIO_CLK_ENABLE()         do{__HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)

#define LCD_WR_GPIO_PORT                 GPIOD
#define LCD_WR_Pin                       GPIO_PIN_5
#define LCD_RD_GPIO_CLK_ENABLE()         do{__HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define LCD_RD_GPIO_PORT                 GPIOD
#define LCD_RD_Pin                       GPIO_PIN_4
#define LCD_RS_GPIO_CLK_ENABLE()         do{__HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define LCD_RS_GPIO_PORT                 GPIOG
#define LCD_RS_Pin                       GPIO_PIN_0
#define LCD_RS_GPIO_Init()               do{__HAL_RCC_GPIOG_CLK_ENABLE()}while(0)

#define LCD_BL(X)                         do{X ? HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET) : \
											HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);}while(0)

typedef struct {
    uint16_t                            width;
    uint16_t                            height;
    uint16_t                            id;
    uint8_t                             dir;
    uint16_t                            wramcmd;
    uint16_t                            setxcmd;
    uint16_t                            setycmd;
} _LCD_DEVICE;

extern _LCD_DEVICE lcddev;

#define LCD_FSMC_NEX					4
#define LCD_FSMC_AX						10
#define LCD_FSMC_BCRX                   FSMC_BANK1->BTCR[(LCD_FSMC_NEX - 1) * 2]        // CS Register
#define LCD_FSMC_BTRX                   FSMC_BANK1->BTCR[(LCD_FSMC_NEX - 1) * 2 + 1]    // CS Timing Register
#define LCD_FSMC_BWTRX                  FSMC_BanklE->BWTR[(LCD_FSMC_NEX - 1) * 2]       // Write Timing Register

typedef struct {
    volatile uint16_t _REG;             // A10=0， r/w cmd
    volatile uint16_t _RAM;             // A10=1， r/w data
} LCD_TypeDef;

#define LCD_BASE						(uint32_t)((0X60000000 + (0X4000000 * (LCD_FSMC_NEX - 1))) | (((1 << LCD_FSMC_AX) * 2) - 2))    // x2 is for correspondence with haddr[25:1], -2 is for offset to base
#define LCD    							((LCD_TypeDef *)LCD_BASE)

#define DFT_SCAN_DIR                    L2R_U2D  //  Default scan direction

// LCD resolution settings
#define SSD_HOR_RESOLUTION              800     // LCD horizontal resolution
#define SSD_VER_RESOLUTION              480     // LCD vertical resolution
// LCD driver parameter settings
#define SSD_HOR_PULSE_WIDTH             1    // Horizontal pulse width
#define SSD_HOR_BACK_PORCH              46   // Horizontal back porch
#define SSD_HOR_FRONT_PORCH             210  // Horizontal front porch
#define SSD_VER_PULSE_WIDTH             1    // Vertical pulse width
#define SSD_VER_BACK_PORCH              23   // Vertical back porch
#define SSD_VER_FRONT_PORCH             22   // Vertical front porch
#define SSD_HT                          (SSD_HOR_RESOLUTION + SSD_HOR_BACK_PORCH + SSD_HOR_FRONT_PORCH)
#define SSD_HPS                         (SSD_HOR_BACK_PORCH)
#define SSD_VT                          (SSD_VER_RESOLUTION + SSD_VER_BACK_PORCH + SSD_VER_FRONT_PORCH)
#define SSD_VPS                         (SSD_VER_BACK_PORCH)

//  Scan direction definitions
#define L2R_U2D                         0  //  From left to right, from top to bottom
#define L2R_D2U                         1  //  From left to right, from bottom to top
#define R2L_U2D                         2  //  From right to left, from top to bottom
#define R2L_D2U                         3  //  From right to left, from bottom to top

#define U2D_L2R                         4  //  From top to bottom, from left to right
#define U2D_R2L                         5  //  From top to bottom, from right to left
#define D2U_L2R                         6  //  From bottom to top, from left to right
#define D2U_R2L                         7  //  From bottom to top, from right to left

// color
#define WHITE                               0xFFFF
#define BLACK                               0x0000
#define RED                                 0xF800
#define GREEN                               0x07E0
#define BLUE                                0x001F
#define MAGENTA                             0XF81F  // zi hong
#define YELLOW                              0XFFE0
#define CYAN                                0X07FF
#define BROWN                               0XBC40
#define BRRED                               0XFC07
#define GRAY                                0X8430
#define DARKBLUE                            0X01CF
#define LIGHTBLUE                           0X7D7C
#define GRAYBLUE                            0X5458
#define LIGHTGREEN                          0X841F
#define LGRAY                               0XC618
#define LGRAYBLUE                           0XA651
#define LBBLUE                              0X2B12

static void LCD_Opt_Delay(uint32_t i);
void LCD_Wr_Reg(volatile uint16_t regno);
void LCD_Wr_Data(volatile uint16_t data);
void LCD_Wr_Reg_Data(uint16_t regno, uint16_t data);
uint16_t LCD_Rr_Data(void);
void LCD_Set_Cursor(uint16_t x, uint16_t y);
void LCD_Wr_Ram_Prepare(void);
void LCD_Draw_Point(uint16_t x, uint16_t y, uint16_t color);
void LCD_Clear(uint16_t color);
void LCD_Ssd_Backlight_Set(uint8_t pwm);
static uint16_t LCD_Rd_Data(void);
void LCD_Scan_Dir(uint8_t dir);
void LCD_Display_Dir(uint8_t dir);
void LCD_Show_Char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color);
void LCD_Show_String(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color);
void LCD_Show_Xnum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint16_t color);
void LCD_Init(void);

// lcd_ex.c
void LCD_Ex_St7789_Reginit(void);
void LCD_Ex_Ili9341_Reginit(void);
void LCD_Ex_Nt35310_Reginit(void);
void LCD_Ex_St7796_Reginit(void);
void LCD_Ex_Nt35510_Reginit(void);
void LCD_Ex_Ili9806_Reginit(void);
void LCD_Ex_Ssd1963_Reginit(void);

#ifdef __cplusplus
}
#endif

// test
void test(void);

#endif // __LCD_H__
