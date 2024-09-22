#ifndef __SRAM_H
#define __SRAM_H

#include "main.h"


#define SRAM_WR_GPIO_PORT                   GPIOD
#define SRAM_WR_GPIO_PIN                    GPIO_PIN_5
#define SRAM_WR_GPIO_CLK_ENABLE()           do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define SRAM_RD_GPIO_PORT                   GPIOD
#define SRAM_RD_GPIO_PIN                    GPIO_PIN_4
#define SRAM_RD_GPIO_CLK_ENABLE()           do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define SRAM_CS_GPIO_PORT                   GPIOG
#define SRAM_CS_GPIO_PIN                    GPIO_PIN_10
#define SRAM_CS_GPIO_CLK_ENABLE()           do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)



#define SRAM_FSMC_NEX                       3
#define SRAM_BASE_ADDR                      (0X60000000 + (0X4000000 * (SRAM_FSMC_NEX - 1)))

extern SRAM_HandleTypeDef                   _sram_handler;

void                                        SRAM_Init(void);
void                                        SRAM_Write(uint8_t *pbuf, uint32_t addr, uint32_t datalen);
void                                        SRAM_Read(uint8_t *pbuf, uint32_t addr, uint32_t datalen);
uint8_t                                     SRAM_Test_Read(uint32_t addr);                 // Read 1 byte from the specified address of SRAM
void                                        SRAM_Test_Write(uint32_t addr, uint8_t data);  // Write 1 byte to the specified address of SRAM

#endif  // __SRAM_H