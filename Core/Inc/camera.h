/***
 * @Date: 2024-09-05 21:55:22
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-06 13:33:00
 * @FilePath: \cameraLcd\Core\Inc\camera.h
 */
#ifndef __CAMERA_H
#define __CAMERA_H

#include "main.h"
#define OV2640_USING_DCMI                   0

#if (OV2640_USING_DCMI == 0)
// define DMA
#define OV2640_DMA_INTERFACE            DMA2_Channel5
#define OV2640_DMA_CLK_ENABLE()         do{ __HAL_RCC_DMA2_CLK_ENABLE(); }while(0)
#endif


#if (OV2640_USING_DCMI == 0)
#define OV2640_VSYNC_GPIO_PORT              GPIOD
#define OV2640_VSYNC_GPIO_PIN               GPIO_PIN_6
#define OV2640_VSYNC_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
#define OV2640_HREF_GPIO_PORT               GPIOG
#define OV2640_HREF_GPIO_PIN                GPIO_PIN_14
#define OV2640_HREF_GPIO_CLK_ENABLE()       do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)
#define OV2640_D0_GPIO_PORT                 GPIOC
#define OV2640_D0_GPIO_PIN                  GPIO_PIN_0
#define OV2640_D0_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define OV2640_D1_GPIO_PORT                 GPIOC
#define OV2640_D1_GPIO_PIN                  GPIO_PIN_1
#define OV2640_D1_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define OV2640_D2_GPIO_PORT                 GPIOC
#define OV2640_D2_GPIO_PIN                  GPIO_PIN_2
#define OV2640_D2_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define OV2640_D3_GPIO_PORT                 GPIOC
#define OV2640_D3_GPIO_PIN                  GPIO_PIN_3
#define OV2640_D3_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define OV2640_D4_GPIO_PORT                 GPIOC
#define OV2640_D4_GPIO_PIN                  GPIO_PIN_4
#define OV2640_D4_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define OV2640_D5_GPIO_PORT                 GPIOC
#define OV2640_D5_GPIO_PIN                  GPIO_PIN_5
#define OV2640_D5_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define OV2640_D6_GPIO_PORT                 GPIOC
#define OV2640_D6_GPIO_PIN                  GPIO_PIN_6
#define OV2640_D6_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define OV2640_D7_GPIO_PORT                 GPIOC
#define OV2640_D7_GPIO_PIN                  GPIO_PIN_7
#define OV2640_D7_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define OV2640_PCLK_GPIO_PORT               GPIOB
#define OV2640_PCLK_GPIO_PIN                GPIO_PIN_4
#define OV2640_PCLK_GPIO_CLK_ENABLE()       do{ __HAL_RCC_GPIOB_CLK_ENABLE();   \
                                                    __HAL_RCC_AFIO_CLK_ENABLE();    \
                                                    __HAL_AFIO_REMAP_SWJ_NOJTAG();  \
                                                }while(0)
#endif

#if (OV2640_USING_DCMI == 0)
#define OV2640_READ_VSYNC()                 (OV2640_VSYNC_GPIO_PORT->IDR & OV2640_VSYNC_GPIO_PIN)
#define OV2640_READ_HREF()                  (OV2640_HREF_GPIO_PORT->IDR & OV2640_HREF_GPIO_PIN)
#define OV2640_READ_PCLK()                  (OV2640_PCLK_GPIO_PORT->IDR & OV2640_PCLK_GPIO_PIN)
#endif

#define OV2640_RST_GPIO_PORT                GPIOG
#define OV2640_RST_GPIO_PIN                 GPIO_PIN_15
#define OV2640_PWDN_GPIO_PORT               GPIOB
#define OV2640_PWDN_GPIO_PIN                GPIO_PIN_3

#define OV2640_PWDN(x)                      do { x ? HAL_GPIO_WritePin(OV2640_PWDN_GPIO_PORT, OV2640_PWDN_GPIO_PIN, GPIO_PIN_SET)  \
                                                : HAL_GPIO_WritePin(OV2640_PWDN_GPIO_PORT, OV2640_PWDN_GPIO_PIN, GPIO_PIN_RESET); \
                                               } while(0)

#define OV2640_RST(x)                      do { x ? HAL_GPIO_WritePin(OV2640_RST_GPIO_PORT, OV2640_RST_GPIO_PIN, GPIO_PIN_SET)  \
                                                : HAL_GPIO_WritePin(OV2640_RST_GPIO_PORT, OV2640_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                              } while(0)

#define OV2640_SCCB_SCL_GPIO_PORT           GPIOD
#define OV2640_SCCB_SCL_GPIO_PIN            GPIO_PIN_3
#define OV2640_SCCB_SDA_GPIO_PORT           GPIOG
#define OV2640_SCCB_SDA_GPIO_PIN            GPIO_PIN_13

#define OV2640_SCCB_SCL(x)                  do{ x ?  HAL_GPIO_WritePin(OV2640_SCCB_SCL_GPIO_PORT, OV2640_SCCB_SCL_GPIO_PIN, GPIO_PIN_SET) :  \
                                                HAL_GPIO_WritePin(OV2640_SCCB_SCL_GPIO_PORT, OV2640_SCCB_SCL_GPIO_PIN, GPIO_PIN_RESET); \
                                            }while(0)

#define OV2640_SCCB_SDA(x)                  do{ x ? HAL_GPIO_WritePin(OV2640_SCCB_SDA_GPIO_PORT, OV2640_SCCB_SDA_GPIO_PIN, GPIO_PIN_SET) :  \
                                                HAL_GPIO_WritePin(OV2640_SCCB_SDA_GPIO_PORT, OV2640_SCCB_SDA_GPIO_PIN, GPIO_PIN_RESET); \
                                            }while(0)

#define OV2640_SCCB_READ_SDA()              HAL_GPIO_ReadPin(OV2640_SCCB_SDA_GPIO_PORT, OV2640_SCCB_SDA_GPIO_PIN)

#define OV2640_SCCB_WRITE                   0x00
#define OV2640_SCCB_READ                    0x01
#define OV2640_SCCB_ADDR                    0x30


// error code
#define OV2640_EOK                          0   // ok
#define OV2640_ERROR                        1   // error
#define OV2640_EINVAL                       2   // illegel parameter
#define OV2640_ENOMEM                       3   // out of memory
#define OV2640_EEMPTY                       4   // resource is empty

uint8_t                                     OV2640_CAMERA_Init(void);
void                                        demorunTask(void *argument);

#endif  // __CAMERA_H