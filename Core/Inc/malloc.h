/*** 
 * @Date: 2024-09-06 22:32:30
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-07 17:14:04
 * @FilePath: \cameraLcd\Core\Inc\malloc.h
 */
#ifndef __MALLOC_H
#define __MALLOC_H
#include "main.h"

#define OV2640_SCCB_GPIO_PULLUP             1   // gpio pull up
#define SRAMIN                              0   // internal sram
#define SRAMEX                              1   // external sram
#define SRAMBANK                            2   // bank sram
#define MT_TYPE                             uint16_t    // memory table type

#define MEM1_BLOCK_SIZE                     32      // block size 32 byte
#define MEM1_MAX_SIZE                       40 * 1024   // max size 40k
#define MEM1_ALLOC_TABLE_SIZE               MEM1_MAX_SIZE / MEM1_BLOCK_SIZE // alloc table size

#define MEM2_BLOCK_SIZE                     32
#define MEM2_MAX_SIZE                       963 * 1024
#define MEM2_ALLOC_TABLE_SIZE               MEM2_MAX_SIZE / MEM2_BLOCK_SIZE

#ifndef NULL
#define NULL                                0
#endif


// light mode
typedef enum
{
    OV2640_LIGHT_MODE_AUTO = 0x00,          // Auto
    OV2640_LIGHT_MODE_SUNNY,                // Sunny
    OV2640_LIGHT_MODE_CLOUDY,               // Cloudy
    OV2640_LIGHT_MODE_OFFICE,               // Office
    OV2640_LIGHT_MODE_HOME,                 // Home
} OV2640_light_mode_t;

// OV2640 module color saturation enumeration
typedef enum
{
    OV2640_COLOR_SATURATION_0 = 0x00,       // +2
    OV2640_COLOR_SATURATION_1,              // +1
    OV2640_COLOR_SATURATION_2,              // 0
    OV2640_COLOR_SATURATION_3,              // -1
    OV2640_COLOR_SATURATION_4,              // -2
} OV2640_color_saturation_t;

// OV2640 module brightness enumeration
typedef enum
{
    OV2640_BRIGHTNESS_0 = 0x00,             // +2
    OV2640_BRIGHTNESS_1,                    // +1
    OV2640_BRIGHTNESS_2,                    // 0
    OV2640_BRIGHTNESS_3,                    // -1
    OV2640_BRIGHTNESS_4,                    // -2
} OV2640_brightness_t;

// OV2640 module contrast enumeration
typedef enum
{
    OV2640_CONTRAST_0 = 0x00,               // +2
    OV2640_CONTRAST_1,                      // +1
    OV2640_CONTRAST_2,                      // 0
    OV2640_CONTRAST_3,                      // -1
    OV2640_CONTRAST_4,                      // -2
} OV2640_contrast_t;

// OV2640 module special effect enumeration
typedef enum
{
    OV2640_SPECIAL_EFFECT_ANTIQUE = 0x00,   // Antique
    OV2640_SPECIAL_EFFECT_BLUISH,           // Bluish
    OV2640_SPECIAL_EFFECT_GREENISH,         // Greenish
    OV2640_SPECIAL_EFFECT_REDISH,           // Redish
    OV2640_SPECIAL_EFFECT_BW,               // B&W
    OV2640_SPECIAL_EFFECT_NEGATIVE,         // Negative
    OV2640_SPECIAL_EFFECT_BW_NEGATIVE,      // B&W Negative
    OV2640_SPECIAL_EFFECT_NORMAL,           // Normal
} OV2640_special_effect_t;

// OV2640 output image format enumeration
typedef enum
{
    OV2640_OUTPUT_FORMAT_RGB565 = 0x00,     // RGB565
    OV2640_OUTPUT_FORMAT_JPEG,              // JPEG
} OV2640_output_format_t;

// OV2640 frame data retrieval method enumeration
typedef enum
{
    OV2640_GET_TYPE_DTS_8B_NOINC = 0x00,    // Image data written to destination address byte by byte, address fixed
    OV2640_GET_TYPE_DTS_8B_INC,             // Image data written to destination address byte by byte, address auto-incremented
    OV2640_GET_TYPE_DTS_16B_NOINC,          // Image data written to destination address half-word by half-word, address fixed
    OV2640_GET_TYPE_DTS_16B_INC,            // Image data written to destination address half-word by half-word, address auto-incremented
    OV2640_GET_TYPE_DTS_32B_NOINC,          // Image data written to destination address word by word, address fixed
    OV2640_GET_TYPE_DTS_32B_INC,            // Image data written to destination address word by word, address auto-incremented
} OV2640_get_type_t;


struct _m_mallco_dev
{
    void                                   (*init)(uint8_t);          // Initialization
    uint16_t                               (*perused)(uint8_t);       // Memory usage rate
    uint8_t                               *membase[SRAMBANK];         // Memory pool managing SRAMBANK regions
    MT_TYPE                               *memmap[SRAMBANK];          // Memory management status table
    uint8_t                                memrdy[SRAMBANK];          // Memory management readiness
};

extern struct _m_mallco_dev                mallco_dev;

void                                       my_mem_init(uint8_t memx);                     // Memory management initialization function (internal/external call)
uint16_t                                   my_mem_perused(uint8_t memx);                    // Get memory usage rate (internal/external call)
void                                       my_mem_set(void *s, uint8_t c, uint32_t count);  // Memory set function
void                                       my_mem_copy(void *des, void *src, uint32_t n);   // Memory copy function
void                                       myfree(uint8_t memx, void *ptr);        // Free memory (external call)
void                                      *mymalloc(uint8_t memx, uint32_t size);  // Allocate memory (external call)
void                                      *myrealloc(uint8_t memx, void *ptr, uint32_t size);                           // Reallocate memory (external call)
#endif // __MALLOC_H