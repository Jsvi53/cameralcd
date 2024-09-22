#include <stdio.h>

#include "delay.h"
#include "supersonic.h"

int supersonic_run(void)
{
    uint32_t CSB_value = 0;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    tim6_delay_us(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == 0);
    int t = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
    tim6.start();
    while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == 1);
    CSB_value = tim6.stop();
    return (CSB_value * 340 / 1000 / 2);
}