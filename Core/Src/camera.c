/*
 * @Date: 2024-09-05 21:55:06
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-16 04:12:53
 * @FilePath: \cameraLcd\Core\Src\camera.c
 */
#include <stdio.h>

#include "camera.h"
#include "cmsis_os2.h"
#include "delay.h"
#include "lcd.h"
#include "malloc.h"
#include "ov2640_cfg.h"

#define OV2640_MID 0x7FA2
#define OV2640_PID 0x2642

extern osSemaphoreId_t dma_semaphoreHandle;

typedef enum {
    OV2640_REG_BANK_DSP = 0x00,
    OV2640_REG_BANK_SENSOR,
} OV2640_reg_bank_t;

static struct {
    struct {
        uint16_t width;
        uint16_t height;
    } output;

#if(OV2640_USING_DCMI == 0)
    struct {
        uint8_t          *line_buf;
        DMA_HandleTypeDef dma_handle;
    } read;
#endif
} g_OV2640_sta = {0};

void OV2640_SCCB_delay()
{
    tim6_delay_us(5);
}

static void OV2640_SCCB_start(void)
{
    OV2640_SCCB_SDA(1);
    OV2640_SCCB_SCL(1);
    OV2640_SCCB_delay();
    OV2640_SCCB_SDA(0);
    OV2640_SCCB_delay();
    OV2640_SCCB_SCL(0);
}

static void OV2640_SCCB_write_byte(uint8_t dat)
{
    int8_t  dat_index;
    uint8_t dat_bit;
    for(dat_index = 7; dat_index >= 0; dat_index--)
    {
        dat_bit = (dat >> dat_index) & 0x01;
        OV2640_SCCB_SDA(dat_bit);
        OV2640_SCCB_delay();
        OV2640_SCCB_SCL(1);
        OV2640_SCCB_delay();
        OV2640_SCCB_SCL(0);
    }
    OV2640_SCCB_SDA(1);
    OV2640_SCCB_delay();
    OV2640_SCCB_SCL(1);
    OV2640_SCCB_delay();
    OV2640_SCCB_SCL(0);
}

static void OV2640_SCCB_stop(void)
{
    OV2640_SCCB_SDA(0);
    OV2640_SCCB_delay();
    OV2640_SCCB_SCL(1);
    OV2640_SCCB_delay();
    OV2640_SCCB_SDA(1);
    OV2640_SCCB_delay();
}

void OV2640_SCCB_3_phase_write(uint8_t id_addr, uint8_t sub_addr, uint8_t dat)
{
    OV2640_SCCB_start();
    OV2640_SCCB_write_byte((id_addr << 1) | OV2640_SCCB_WRITE);
    OV2640_SCCB_write_byte(sub_addr);
    OV2640_SCCB_write_byte(dat);
    OV2640_SCCB_stop();
}

static void OV2640_write_reg(uint8_t reg, uint8_t dat)
{
    OV2640_SCCB_3_phase_write(OV2640_SCCB_ADDR, reg, dat);
}

static uint8_t OV2640_reg_bank_select(OV2640_reg_bank_t bank)
{
    switch(bank)
    {
        case OV2640_REG_BANK_DSP: {
            OV2640_write_reg(OV2640_REG_BANK_SEL, 0x00);
            break;
        }
        case OV2640_REG_BANK_SENSOR: {
            OV2640_write_reg(OV2640_REG_BANK_SEL, 0x01);
            break;
        }
        default: {
            return OV2640_EINVAL;
        }
    }
    return OV2640_EOK;
}

#if(OV2640_SCCB_GPIO_PULLUP != 0)
static void OV2640_SCCB_set_sda_output(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};

    gpio_init_struct.Pin   = OV2640_SCCB_SDA_GPIO_PIN;
    gpio_init_struct.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OV2640_SCCB_SDA_GPIO_PORT, &gpio_init_struct);
}

static void OV2640_SCCB_set_sda_input(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};

    gpio_init_struct.Pin   = OV2640_SCCB_SDA_GPIO_PIN;
    gpio_init_struct.Mode  = GPIO_MODE_INPUT;
    gpio_init_struct.Pull  = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OV2640_SCCB_SDA_GPIO_PORT, &gpio_init_struct);
}
#endif

#if(OV2640_USING_DCMI == 0)
// Get one byte of data from ATK-MD2640 port D0~D7
static inline uint8_t OV2640_get_byte_data(void)
{
    #if(OV2640_DATA_PIN_IN_SAME_GPIO_PORT == 0)
        uint8_t dat = 0;
        dat |= (((OV2640_D0_GPIO_PORT->IDR & OV2640_D0_GPIO_PIN) == 0) ? (0) : (1)) << 0;
        dat |= (((OV2640_D1_GPIO_PORT->IDR & OV2640_D1_GPIO_PIN) == 0) ? (0) : (1)) << 1;
        dat |= (((OV2640_D2_GPIO_PORT->IDR & OV2640_D2_GPIO_PIN) == 0) ? (0) : (1)) << 2;
        dat |= (((OV2640_D3_GPIO_PORT->IDR & OV2640_D3_GPIO_PIN) == 0) ? (0) : (1)) << 3;
        dat |= (((OV2640_D4_GPIO_PORT->IDR & OV2640_D4_GPIO_PIN) == 0) ? (0) : (1)) << 4;
        dat |= (((OV2640_D5_GPIO_PORT->IDR & OV2640_D5_GPIO_PIN) == 0) ? (0) : (1)) << 5;
        dat |= (((OV2640_D6_GPIO_PORT->IDR & OV2640_D6_GPIO_PIN) == 0) ? (0) : (1)) << 6;
        dat |= (((OV2640_D7_GPIO_PORT->IDR & OV2640_D7_GPIO_PIN) == 0) ? (0) : (1)) << 7;
        return dat;
    #else
        return OV2640_DATE_GPIO_PORT->IDR & OV2640_DATA_READ_MASK;
    #endif
}
#endif

#if(OV2640_USING_DCMI == 0)
// Initialize ATK-MC2640 module DMA
static void OV2640_dma_init(uint32_t meminc, uint32_t memdataalignment)
{
    OV2640_DMA_CLK_ENABLE();

    g_OV2640_sta.read.dma_handle.Instance                 = OV2640_DMA_INTERFACE;
    g_OV2640_sta.read.dma_handle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
    g_OV2640_sta.read.dma_handle.Init.PeriphInc           = DMA_PINC_ENABLE;
    g_OV2640_sta.read.dma_handle.Init.MemInc              = meminc;
    g_OV2640_sta.read.dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    g_OV2640_sta.read.dma_handle.Init.MemDataAlignment    = memdataalignment;
    g_OV2640_sta.read.dma_handle.Init.Mode                = DMA_NORMAL;
    g_OV2640_sta.read.dma_handle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;

    HAL_DMA_Init(&g_OV2640_sta.read.dma_handle);

    // // using DMA interrupt
    // __HAL_DMA_ENABLE_IT(&g_OV2640_sta.read.dma_handle, DMA_IT_TC);
    // // config DMA interrupt
    // HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    // // enable interrupt
    // HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

// Read one line of data from ATK-MC2640
// void DMA1_Channel1_IRQHandler(void)
// {
//     HAL_DMA_IRQHandler(&g_OV2640_sta.read.dma_handle);
// }

// void HAL_DMA_ConvCpltCallback(DMA_HandleTypeDef *hdma)
// {
//     if (hdma == &g_OV2640_sta.read.dma_handle)
//     {
//         osSemaphoreRelease(dma_semaphoreHandle);
//     }
// }

#endif

static void OV2640_SCCB_read_byte(uint8_t *dat)
{
    int8_t  dat_index;
    uint8_t dat_bit;

#if(OV2640_SCCB_GPIO_PULLUP != 0)
    OV2640_SCCB_set_sda_input();
#endif

    for(dat_index = 7; dat_index >= 0; dat_index--)
    {
        OV2640_SCCB_delay();
        OV2640_SCCB_SCL(1);
        dat_bit = OV2640_SCCB_READ_SDA();
        *dat |= (dat_bit << dat_index);
        OV2640_SCCB_delay();
        OV2640_SCCB_SCL(0);
    }

    OV2640_SCCB_delay();
    OV2640_SCCB_SCL(1);
    OV2640_SCCB_delay();
    OV2640_SCCB_SCL(0);
    OV2640_SCCB_delay();
    OV2640_SCCB_SDA(0);
    OV2640_SCCB_delay();

#if(OV2640_SCCB_GPIO_PULLUP != 0)
    OV2640_SCCB_set_sda_output();
#endif
}

void OV2640_SCCB_2_phase_write(uint8_t id_addr, uint8_t sub_addr)
{
    OV2640_SCCB_start();
    OV2640_SCCB_write_byte((id_addr << 1) | OV2640_SCCB_WRITE);
    OV2640_SCCB_write_byte(sub_addr);
    OV2640_SCCB_stop();
}

void OV2640_SCCB_2_phase_read(uint8_t id_addr, uint8_t *dat)
{
    OV2640_SCCB_start();
    OV2640_SCCB_write_byte((id_addr << 1) | OV2640_SCCB_READ);
    OV2640_SCCB_read_byte(dat);
    OV2640_SCCB_stop();
}

static uint8_t OV2640_read_reg(uint8_t reg)
{
    uint8_t dat = 0;
    OV2640_SCCB_2_phase_write(OV2640_SCCB_ADDR, reg);
    OV2640_SCCB_2_phase_read(OV2640_SCCB_ADDR, &dat);
    return dat;
}

static uint16_t OV2640_get_mid(void)
{
    uint16_t mid;
    OV2640_reg_bank_select(OV2640_REG_BANK_SENSOR);
    mid = OV2640_read_reg(OV2640_REG_SENSOR_MIDH) << 8;
    mid |= OV2640_read_reg(OV2640_REG_SENSOR_MIDL);
    printf("mid: %x\r\n", mid);
    return mid;
}

static uint16_t OV2640_get_pid(void)
{
    uint16_t pid;
    OV2640_reg_bank_select(OV2640_REG_BANK_SENSOR);
    pid = OV2640_read_reg(OV2640_REG_SENSOR_PIDH) << 8;
    pid |= OV2640_read_reg(OV2640_REG_SENSOR_PIDL);
    printf("pid: %x\r\n", pid);
    return pid;
}

static void OV2640_init_reg(void)
{
    uint32_t cfg_index;
    uint8_t  zmow;
    uint8_t  zmoh;
    uint8_t  zmhh;

    for(cfg_index = 0; cfg_index < (sizeof(OV2640_init_uxga_cfg) / sizeof(OV2640_init_uxga_cfg[0])); cfg_index++)
    {
        OV2640_write_reg(OV2640_init_uxga_cfg[cfg_index][0], OV2640_init_uxga_cfg[cfg_index][1]);
    }

    OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
    zmow = OV2640_read_reg(OV2640_REG_DSP_ZMOW);
    zmoh = OV2640_read_reg(OV2640_REG_DSP_ZMOH);
    zmhh = OV2640_read_reg(OV2640_REG_DSP_ZMHH);

    g_OV2640_sta.output.width  = ((uint16_t)zmow | ((zmhh & 0x03) << 8)) << 2;
    g_OV2640_sta.output.height = ((uint16_t)zmoh | ((zmhh & 0x04) << 6)) << 2;
}

uint8_t OV2640_CAMERA_Init(void)
{
    uint16_t mid;
    uint16_t pid;

    OV2640_PWDN(0);  // exit power-down
    tim6_delay_ms(10);

    OV2640_RST(0);  // reset
    tim6_delay_ms(10);
    OV2640_RST(1);
    tim6_delay_ms(10);

    OV2640_SCCB_SDA(0);  // SCCB init
    OV2640_SCCB_delay();
    OV2640_SCCB_SCL(1);
    OV2640_SCCB_delay();
    OV2640_SCCB_SDA(1);
    OV2640_SCCB_delay();

    OV2640_reg_bank_select(OV2640_REG_BANK_SENSOR);  // sw reset sensor reg bank
    OV2640_write_reg(OV2640_REG_SENSOR_COM7, 0x80);
    tim6_delay_ms(50);

    mid = OV2640_get_mid();  // manufacture id
    if(mid != OV2640_MID)
    {
        return OV2640_ERROR;
    }

    pid = OV2640_get_pid();  // product id
    if(pid != OV2640_PID)
    {
        return OV2640_ERROR;
    }
    OV2640_init_reg();

    printf("g_OV2640_sta.output.width:%d, size: %d\r\n", g_OV2640_sta.output.width, g_OV2640_sta.output.width * sizeof(uint16_t));
#if(OV2640_USING_DCMI == 0)
    g_OV2640_sta.read.line_buf = mymalloc(SRAMIN, g_OV2640_sta.output.width * sizeof(uint16_t));
    printf("g_OV2640_sta.read.line_buf:0x%x\r\n", g_OV2640_sta.read.line_buf);
    if(g_OV2640_sta.read.line_buf == NULL)
    {
        return OV2640_ENOMEM;
    }
#endif
    return OV2640_EOK;
}

uint8_t OV2640_set_output_format(OV2640_output_format_t format)
{
    uint32_t cfg_index;

    switch(format)
    {
        case OV2640_OUTPUT_FORMAT_RGB565: {
            for(cfg_index = 0; cfg_index < (sizeof(OV2640_set_rgb565_cfg) / sizeof(OV2640_set_rgb565_cfg[0])); cfg_index++)
            {
                OV2640_write_reg(OV2640_set_rgb565_cfg[cfg_index][0], OV2640_set_rgb565_cfg[cfg_index][1]);
            }
            break;
        }
        case OV2640_OUTPUT_FORMAT_JPEG: {
            for(cfg_index = 0; cfg_index < (sizeof(OV2640_set_yuv422_cfg) / sizeof(OV2640_set_yuv422_cfg[0])); cfg_index++)
            {
                OV2640_write_reg(OV2640_set_yuv422_cfg[cfg_index][0], OV2640_set_yuv422_cfg[cfg_index][1]);
            }
            for(cfg_index = 0; cfg_index < (sizeof(OV2640_set_jpeg_cfg) / sizeof(OV2640_set_jpeg_cfg[0])); cfg_index++)
            {
                OV2640_write_reg(OV2640_set_jpeg_cfg[cfg_index][0], OV2640_set_jpeg_cfg[cfg_index][1]);
            }
            break;
        }
        default: {
            return OV2640_EINVAL;
        }
    }

    return OV2640_EOK;
}

uint8_t OV2640_set_output_size(uint16_t width, uint16_t height)
{
    uint16_t output_width;
    uint16_t output_height;

    if(((width & (4 - 1)) != 0) || ((height & (4 - 1)) != 0))
    {
        return OV2640_EINVAL;
    }

#if(OV2640_USING_DCMI == 0)
    myfree(SRAMIN, g_OV2640_sta.read.line_buf);
    g_OV2640_sta.read.line_buf = mymalloc(SRAMIN, width * sizeof(uint16_t));
    if(g_OV2640_sta.read.line_buf == NULL)
    {
        g_OV2640_sta.read.line_buf = mymalloc(SRAMIN, g_OV2640_sta.output.width * sizeof(uint16_t));
        return OV2640_ENOMEM;
    } else
#endif
    {
        g_OV2640_sta.output.width  = width;
        g_OV2640_sta.output.height = height;
    }

    output_width  = width >> 2;
    output_height = height >> 2;
    OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
    OV2640_write_reg(OV2640_REG_DSP_RESET, 0x04);  // reset jpeg
    OV2640_write_reg(OV2640_REG_DSP_ZMOW, (uint8_t)(output_width & 0x00FF));
    OV2640_write_reg(OV2640_REG_DSP_ZMOH, (uint8_t)(output_height & 0x00FF));
    OV2640_write_reg(OV2640_REG_DSP_ZMHH, ((uint8_t)(output_width >> 8) & 0x03) | ((uint8_t)(output_height >> 6) & 0x04));
    OV2640_write_reg(OV2640_REG_DSP_RESET, 0x00);  // reset cif, a vedio standard

    return OV2640_EOK;
}

uint8_t OV2640_set_light_mode(OV2640_light_mode_t mode)
{
    switch(mode)
    {
        case OV2640_LIGHT_MODE_AUTO: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0xC7, 0x00);
            break;
        }
        case OV2640_LIGHT_MODE_SUNNY: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0xC7, 0x40);
            OV2640_write_reg(0xCC, 0x5E);
            OV2640_write_reg(0xCD, 0x41);
            OV2640_write_reg(0xCE, 0x54);
            break;
        }
        case OV2640_LIGHT_MODE_CLOUDY: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0xC7, 0x40);
            OV2640_write_reg(0xCC, 0x65);
            OV2640_write_reg(0xCD, 0x41);
            OV2640_write_reg(0xCE, 0x4F);
            break;
        }
        case OV2640_LIGHT_MODE_OFFICE: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0xC7, 0x40);
            OV2640_write_reg(0xCC, 0x52);
            OV2640_write_reg(0xCD, 0x41);
            OV2640_write_reg(0xCE, 0x66);
            break;
        }
        case OV2640_LIGHT_MODE_HOME: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0xC7, 0x40);
            OV2640_write_reg(0xCC, 0x42);
            OV2640_write_reg(0xCD, 0x3F);
            OV2640_write_reg(0xCE, 0x71);
            break;
        }
        default: {
            return OV2640_EINVAL;
        }
    }

    return OV2640_EOK;
}

uint8_t OV2640_set_color_saturation(OV2640_color_saturation_t saturation)
{
    switch(saturation)
    {
        case OV2640_COLOR_SATURATION_0: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x02);
            OV2640_write_reg(0x7C, 0x03);
            OV2640_write_reg(0x7D, 0x68);
            OV2640_write_reg(0x7D, 0x68);
            break;
        }
        case OV2640_COLOR_SATURATION_1: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x02);
            OV2640_write_reg(0x7C, 0x03);
            OV2640_write_reg(0x7D, 0x58);
            OV2640_write_reg(0x7D, 0x58);
            break;
        }
        case OV2640_COLOR_SATURATION_2: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x02);
            OV2640_write_reg(0x7C, 0x03);
            OV2640_write_reg(0x7D, 0x48);
            OV2640_write_reg(0x7D, 0x48);
            break;
        }
        case OV2640_COLOR_SATURATION_3: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x02);
            OV2640_write_reg(0x7C, 0x03);
            OV2640_write_reg(0x7D, 0x38);
            OV2640_write_reg(0x7D, 0x38);
            break;
        }
        case OV2640_COLOR_SATURATION_4: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x02);
            OV2640_write_reg(0x7C, 0x03);
            OV2640_write_reg(0x7D, 0x28);
            OV2640_write_reg(0x7D, 0x28);
            break;
        }
        default: {
            return OV2640_EINVAL;
        }
    }

    return OV2640_EOK;
}

uint8_t OV2640_set_brightness(OV2640_brightness_t brightness)
{
    switch(brightness)
    {
        case OV2640_BRIGHTNESS_0: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x09);
            OV2640_write_reg(0x7D, 0x40);
            OV2640_write_reg(0x7D, 0x00);
            break;
        }
        case OV2640_BRIGHTNESS_1: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x09);
            OV2640_write_reg(0x7D, 0x30);
            OV2640_write_reg(0x7D, 0x00);
            break;
        }
        case OV2640_BRIGHTNESS_2: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x09);
            OV2640_write_reg(0x7D, 0x20);
            OV2640_write_reg(0x7D, 0x00);
            break;
        }
        case OV2640_BRIGHTNESS_3: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x09);
            OV2640_write_reg(0x7D, 0x10);
            OV2640_write_reg(0x7D, 0x00);
            break;
        }
        case OV2640_BRIGHTNESS_4: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x09);
            OV2640_write_reg(0x7D, 0x00);
            OV2640_write_reg(0x7D, 0x00);
            break;
        }
        default: {
            return OV2640_EINVAL;
        }
    }
    return OV2640_EOK;
}

uint8_t OV2640_set_contrast(OV2640_contrast_t contrast)
{
    switch(contrast)
    {
        case OV2640_CONTRAST_0: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x07);
            OV2640_write_reg(0x7D, 0x20);
            OV2640_write_reg(0x7D, 0x28);
            OV2640_write_reg(0x7D, 0x0C);
            OV2640_write_reg(0x7D, 0x06);
            break;
        }
        case OV2640_CONTRAST_1: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x07);
            OV2640_write_reg(0x7D, 0x20);
            OV2640_write_reg(0x7D, 0x24);
            OV2640_write_reg(0x7D, 0x16);
            OV2640_write_reg(0x7D, 0x06);
            break;
        }
        case OV2640_CONTRAST_2: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x07);
            OV2640_write_reg(0x7D, 0x20);
            OV2640_write_reg(0x7D, 0x20);
            OV2640_write_reg(0x7D, 0x20);
            OV2640_write_reg(0x7D, 0x06);
            break;
        }
        case OV2640_CONTRAST_3: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x07);
            OV2640_write_reg(0x7D, 0x20);
            OV2640_write_reg(0x7D, 0x1C);
            OV2640_write_reg(0x7D, 0x2A);
            OV2640_write_reg(0x7D, 0x06);
            break;
        }
        case OV2640_CONTRAST_4: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x04);
            OV2640_write_reg(0x7C, 0x07);
            OV2640_write_reg(0x7D, 0x20);
            OV2640_write_reg(0x7D, 0x18);
            OV2640_write_reg(0x7D, 0x34);
            OV2640_write_reg(0x7D, 0x06);
            break;
        }
        default: {
            return OV2640_EINVAL;
        }
    }
    return OV2640_EOK;
}

uint8_t OV2640_set_special_effect(OV2640_special_effect_t effect)
{
    switch(effect)
    {
        case OV2640_SPECIAL_EFFECT_ANTIQUE: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x18);
            OV2640_write_reg(0x7C, 0x05);
            OV2640_write_reg(0x7D, 0x40);
            OV2640_write_reg(0x7D, 0xA6);
            break;
        }
        case OV2640_SPECIAL_EFFECT_BLUISH: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x18);
            OV2640_write_reg(0x7C, 0x05);
            OV2640_write_reg(0x7D, 0xA0);
            OV2640_write_reg(0x7D, 0x40);
            break;
        }
        case OV2640_SPECIAL_EFFECT_GREENISH: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x18);
            OV2640_write_reg(0x7C, 0x05);
            OV2640_write_reg(0x7D, 0x40);
            OV2640_write_reg(0x7D, 0x40);
            break;
        }
        case OV2640_SPECIAL_EFFECT_REDISH: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x18);
            OV2640_write_reg(0x7C, 0x05);
            OV2640_write_reg(0x7D, 0x40);
            OV2640_write_reg(0x7D, 0xC0);
            break;
        }
        case OV2640_SPECIAL_EFFECT_BW: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x18);
            OV2640_write_reg(0x7C, 0x05);
            OV2640_write_reg(0x7D, 0x80);
            OV2640_write_reg(0x7D, 0x80);
            break;
        }
        case OV2640_SPECIAL_EFFECT_NEGATIVE: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x40);
            OV2640_write_reg(0x7C, 0x05);
            OV2640_write_reg(0x7D, 0x80);
            OV2640_write_reg(0x7D, 0x80);
            break;
        }
        case OV2640_SPECIAL_EFFECT_BW_NEGATIVE: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x58);
            OV2640_write_reg(0x7C, 0x05);
            OV2640_write_reg(0x7D, 0x80);
            OV2640_write_reg(0x7D, 0x80);
            break;
        }
        case OV2640_SPECIAL_EFFECT_NORMAL: {
            OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
            OV2640_write_reg(0x7C, 0x00);
            OV2640_write_reg(0x7D, 0x00);
            OV2640_write_reg(0x7C, 0x05);
            OV2640_write_reg(0x7D, 0x80);
            OV2640_write_reg(0x7D, 0x80);
            break;
        }
        default: {
            return OV2640_EINVAL;
        }
    }

    return OV2640_EOK;
}

/**
 * @description: set ov2640 output speed
 * @param {uint8_t} clk_dev, it is clock divider, <= 63
 * @param {uint8_t} pclk_dev, it is pixel clock divider, <= 127
 * @return bool
 */
uint8_t OV2640_set_output_speed(uint8_t clk_dev, uint8_t pclk_dev)
{
    if(clk_dev > 63)
    {
        return OV2640_EINVAL;
    }

    if((pclk_dev == 0) || (pclk_dev > 127))
    {
        return OV2640_EINVAL;
    }

    OV2640_reg_bank_select(OV2640_REG_BANK_DSP);
    OV2640_write_reg(OV2640_REG_DSP_R_DVP_SP, pclk_dev);
    OV2640_reg_bank_select(OV2640_REG_BANK_SENSOR);
    OV2640_write_reg(OV2640_REG_SENSOR_CLKRC, clk_dev);

    return OV2640_EOK;
}

void demo_set_outspeed_suit_lcd(void)
{
    if(lcddev.width == 240)
    {
        OV2640_set_output_speed(1, 28);
    } else if(lcddev.width == 320)
    {
        OV2640_set_output_speed(3, 15);
    } else
    {
        OV2640_set_output_speed(15, 4);
    }
}

static void demo_reset_lcd(void)
{
    LCD_Scan_Dir(L2R_U2D);
    LCD_Set_Cursor(0, 0);
    LCD_Wr_Ram_Prepare();
}

uint8_t OV2640_get_frame(uint32_t dts_addr, OV2640_get_type_t type, void (*before_transfer)(void))
{
    uint32_t meminc;
    uint32_t memdataalignment;
#if(OV2640_USING_DCMI != 0)
    uint32_t len;
#else
    uint16_t pixel_cnt = 0;
    uint16_t line_cnt  = 0;
    uint16_t dts_offset;
#endif

    switch(type)
    {
        case OV2640_GET_TYPE_DTS_8B_NOINC: {
            meminc           = DMA_MINC_DISABLE;
            memdataalignment = DMA_MDATAALIGN_BYTE;
#if(OV2640_USING_DCMI != 0)
            len = (g_OV2640_sta.output.width * g_OV2640_sta.output.height) / sizeof(uint8_t);
#else
            dts_offset = 0;
#endif
            break;
        }
        case OV2640_GET_TYPE_DTS_8B_INC: {
            meminc           = DMA_MINC_ENABLE;
            memdataalignment = DMA_MDATAALIGN_BYTE;
#if(OV2640_USING_DCMI != 0)
            len = (g_OV2640_sta.output.width * g_OV2640_sta.output.height) / sizeof(uint8_t);
#else
            dts_offset = g_OV2640_sta.output.width << 1;
#endif
            break;
        }
        case OV2640_GET_TYPE_DTS_16B_NOINC: {
            meminc           = DMA_MINC_DISABLE;
            memdataalignment = DMA_MDATAALIGN_HALFWORD;
#if(OV2640_USING_DCMI != 0)
            len = (g_OV2640_sta.output.width * g_OV2640_sta.output.height) / sizeof(uint16_t);
#else
            dts_offset = 0;
#endif
            break;
        }
        case OV2640_GET_TYPE_DTS_16B_INC: {
            meminc           = DMA_MINC_ENABLE;
            memdataalignment = DMA_MDATAALIGN_HALFWORD;
#if(OV2640_USING_DCMI != 0)
            len = (g_OV2640_sta.output.width * g_OV2640_sta.output.height) / sizeof(uint16_t);
#else
            dts_offset = g_OV2640_sta.output.width << 1;
#endif
            break;
        }
        case OV2640_GET_TYPE_DTS_32B_NOINC: {
            meminc           = DMA_MINC_DISABLE;
            memdataalignment = DMA_MDATAALIGN_WORD;
#if(OV2640_USING_DCMI != 0)
            len = (g_OV2640_sta.output.width * g_OV2640_sta.output.height) / sizeof(uint32_t);
#else
            dts_offset = 0;
#endif
            break;
        }
        case OV2640_GET_TYPE_DTS_32B_INC: {
            meminc           = DMA_MINC_ENABLE;
            memdataalignment = DMA_MDATAALIGN_WORD;
#if(OV2640_USING_DCMI != 0)
            len = (g_OV2640_sta.output.width * g_OV2640_sta.output.height) / sizeof(uint32_t);
#else
            dts_offset = g_OV2640_sta.output.width << 1;
#endif
            break;
        }
        default: {
            return OV2640_EINVAL;
        }
    }

#if(OV2640_USING_DCMI != 0)
    if(before_transfer != NULL)
    {
        before_transfer();
    }

    OV2640_dcmi_start(dts_addr, meminc, memdataalignment, len);
#else
    OV2640_dma_init(meminc, memdataalignment);

    if(OV2640_READ_VSYNC() != 0)
    {
        return OV2640_EEMPTY;
    }

    if(before_transfer != NULL)
    {
        before_transfer();
    }

    while(line_cnt < g_OV2640_sta.output.height)
    {
        while(OV2640_READ_HREF() != 0)
        {
            while(OV2640_READ_PCLK() == 0);
            g_OV2640_sta.read.line_buf[pixel_cnt++] = OV2640_get_byte_data();
            while(OV2640_READ_PCLK() != 0);

            while(OV2640_READ_PCLK() == 0);
            g_OV2640_sta.read.line_buf[pixel_cnt++] = OV2640_get_byte_data();
            while(OV2640_READ_PCLK() != 0);
        }

        if(pixel_cnt != 0)
        {
            HAL_DMA_Abort(&g_OV2640_sta.read.dma_handle);
            HAL_DMA_Start(&g_OV2640_sta.read.dma_handle, (uint32_t)g_OV2640_sta.read.line_buf, dts_addr, g_OV2640_sta.output.width);
            // osSemaphoreRelease(dma_semaphoreHandle);
            dts_addr += dts_offset;
            pixel_cnt = 0;
            line_cnt++;
        }
    }
#endif
    return OV2640_EOK;
}

void demorunTask(void *argument)
{
    uint8_t ret;
    my_mem_init(SRAMIN);                                           // Initialize internal SRAM memory pool
    ret = OV2640_CAMERA_Init();                                    // Initialize ATK-MC2640 module
    ret |= OV2640_set_output_format(OV2640_OUTPUT_FORMAT_RGB565);  // Set output image format
    ret |= OV2640_set_output_size(lcddev.width, lcddev.height);    // Set output image resolution
    if(ret != 0)
    {
        printf("ATK-MC2640 Init Failed!\r\n");
        while(1)
        {
            LED0_TOGGLE();       // Toggle LED0
            tim6_delay_ms(200);  // Delay for 200 ms
        }
    }

    demo_set_outspeed_suit_lcd();  // Set output rate
    OV2640_set_light_mode(OV2640_LIGHT_MODE_SUNNY);           // Set light mode
    OV2640_set_color_saturation(OV2640_COLOR_SATURATION_1);   // Set color saturation
    OV2640_set_brightness(OV2640_BRIGHTNESS_1);               // Set brightness
    OV2640_set_contrast(OV2640_CONTRAST_2);                   // Set contrast
    OV2640_set_special_effect(OV2640_SPECIAL_EFFECT_NORMAL);  // Set special effect
    while(1)
    {
        // Get the frame data and display it on the LCD
        OV2640_get_frame((uint32_t)&LCD->_RAM, OV2640_GET_TYPE_DTS_16B_NOINC, demo_reset_lcd);
    }
}