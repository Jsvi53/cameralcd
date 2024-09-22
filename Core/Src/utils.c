/*
 * @Date: 2024-09-16 23:05:26
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-22 03:42:16
 * @FilePath: \cameraLcd\Core\Src\utils.c
 */
#include <stdio.h>

#include "lcd.h"
#include "malloc.h"
#include "usart.h"
#include "utils.h"

// // uint8_t          image_buffer[IMG_SIZE] __attribute__((section(".sram_base_addr"), aligned(64)));
uint8_t         *image_buffer;
uint8_t          line_buffer[LINE_BUFFER_SIZE];
uint8_t          pixel_buffer[2];
volatile uint8_t received_flag = 0;
volatile int     _index         = 0;
volatile int     remaining_size;
ReceiveMode      currentmode;

int _write(int fd, char *ch, int len)
{
    // HAL_UART_Transmit_DMA(&huart1, (uint8_t *)ch, len);
    HAL_UART_Transmit(&huart1, (uint8_t *)ch, len, 0xFFFF);
    return len;
}

/**
 * @description: receive image from usart
 * @param {  }
 * @return {*}
 */
void image_receive_init(ReceiveMode mode)
{
    LCD_Scan_Dir(L2R_U2D);
    LCD_Wr_Ram_Prepare();
    my_mem_init(SRAMEX);
    image_buffer = mymalloc(SRAMEX, IMG_SIZE);
    currentmode  = mode;
}

void image_receive_run(void)
{
    switch (currentmode)
    {
        case frame_mode: {
            if(IMG_SIZE <= CHUNK_SIZE)
            {
                HAL_UART_Receive_DMA(&huart1, image_buffer, IMG_SIZE);
            } else
            {
                HAL_UART_Receive_DMA(&huart1, image_buffer, CHUNK_SIZE);
            }
            received_flag = 0;
            break;
        }
        case line_mode: {
            HAL_UART_Receive_DMA(&huart1, line_buffer, sizeof(line_buffer));
            received_flag = 0;
            break;
        }
        case pixel_mode: {
            HAL_UART_Receive_DMA(&huart1, pixel_buffer, sizeof(pixel_buffer));
            break;
        }
        default: {
            break;
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        switch(currentmode)
        {
            case frame_mode: {
                _index += CHUNK_SIZE;
                if(_index < IMG_SIZE)
                {
                    remaining_size = IMG_SIZE - _index;
                    if(remaining_size < CHUNK_SIZE)
                    {
                        HAL_UART_Receive_DMA(&huart1, image_buffer + _index, remaining_size);
                    } else
                    {
                        HAL_UART_Receive_DMA(&huart1, image_buffer + _index, CHUNK_SIZE);
                    }
                } else
                {
                    _index        = 0;
                    received_flag = 1;
                    process_image_data(image_buffer);
                }
            }
            case line_mode: {
                _index += 1;
                process_image_data(line_buffer);
                HAL_UART_Receive_DMA(&huart1, line_buffer, sizeof(line_buffer));
                break;
            }
            case pixel_mode: {
                uint16_t color = (pixel_buffer[1] << 8) | pixel_buffer[0];
                LCD->_RAM      = color;
                HAL_UART_Receive_DMA(&huart1, pixel_buffer, sizeof(pixel_buffer));
                break;
            }
            default: {
                break;
            }
        }
    }
}

int process_image_data(uint8_t *imageData)
{
    switch (currentmode)
    {
        case frame_mode: {
            for(int i = 0; i < IMG_SIZE; i += 2)
            {
                uint16_t color = (imageData[i + 1] << 8) | imageData[i];
                printf("%x %x\n",  imageData[i + 1], imageData[i]);
                LCD->_RAM      = color;
            }
            break;
        }
        case line_mode: {
            for(int i = 0; i < LINE_BUFFER_SIZE; i += 2)
            {
                uint16_t color = (imageData[i + 1] << 8) | imageData[i];
                LCD->_RAM      = color;
            }

            break;
        }
        default: {
            break;
        }
    }

    return 0;
}
