/***
 * @Date: 2024-08-31 19:44:09
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-14 13:45:44
 * @FilePath: \cameraLcd\Core\Inc\delay.h
 */
#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>
#define USING_HAL_TIM_INIT(x)  ((x) ? 0 : 1)

typedef struct {
    uint32_t allcnt;
    void (*start)(void);
    uint16_t (*stop)(void);
} CustomTIM;

extern CustomTIM            tim6;

void                        tim6_delay_init(void);
void                        tim6_delay_us(uint32_t us);
void                        tim6_delay_ms(uint16_t ms);
void                        tim6_start(void);
uint16_t                    tim6_stop(void);
#endif  // __DELAY2_H