/*
 * @Date: 2024-09-03 15:24:41
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-04 18:59:39
 * @FilePath: \cameraLcd\Core\Src\key.c
 */
#include "key.h"
#include "delay.h"
#include <stdio.h>

uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;  // loose key flag
    uint8_t        keyval = 0;
    if(mode)
    {
        key_up = 1;
    }
    
    if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
    {
        tim6_delay_ms(10);
        key_up = 0;
        if(KEY0 == 0)
        {
            keyval = KEY0_PRES;
        }
        if(KEY1 == 0)
        {
            keyval = KEY1_PRES;
        }
        if(KEY2 == 0)
        {
            keyval = KEY2_PRES;
        }
        if(WK_UP == 1)
        {
            keyval = WKUP_PRES;
        }
    } else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0)  // NO KEY PRESS
    {
        key_up = 1;
    }
    // printf("KEY0 = %d, KEY1 = %d, KEY2 = %d, WKUP = %d, key_up = %d, keyval = %d\r\n", KEY0, KEY1, KEY2, WK_UP, key_up, keyval);
    return keyval;
}
