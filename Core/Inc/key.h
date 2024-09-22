/*** 
 * @Date: 2024-09-03 15:24:35
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-03 15:41:16
 * @FilePath: \cameraLcd\Core\Inc\key.h
 */
#ifndef __KEY_H
#define __KEY_H

#include "main.h"

#define KEY0                                HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)
#define KEY1                                HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3)
#define KEY2                                HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2)
#define WK_UP                               HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)
#define KEY0_PRES                           1
#define KEY1_PRES                           2
#define KEY2_PRES                           3
#define WKUP_PRES                           4
uint8_t                                     KEY_Scan(uint8_t mode);

#endif  // __KEY_H