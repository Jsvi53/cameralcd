/*
 * @Date: 2024-08-30 16:39:33
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-15 19:53:42
 * @FilePath: \cameraLcd\Core\Src\delay.c
 * @Description: based on tim6
 */
#include "delay.h"
#include "stm32f103xe.h"

static uint32_t g_fac_us = 0;  // us delay multiplied factor
CustomTIM       tim6     = {0};

void tim6_delay_init(void)
{
    if(USING_HAL_TIM_INIT(1))
    {
        RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;  // start the time rcc for the following operation of tim6
        TIM6->PSC = 72 - 1;
        TIM6->ARR = 0xFFFF;
        TIM6->CR1 |= TIM_CR1_OPM;  // One shot mode, enable but not start now
    }
    tim6.start = &tim6_start;
    tim6.stop  = &tim6_stop;
}

void tim6_delay_us(uint32_t us)
{
    while(us > 0xFFFF)
    {
        TIM6->ARR = 0xFFFF;
        TIM6->CNT = 0;
        TIM6->CR1 |= TIM_CR1_CEN;
        while(!(TIM6->SR & TIM_SR_UIF));
        TIM6->SR &= ~TIM_SR_UIF;
        us -= 0xFFFF;
    }
    if(us > 0)
    {
        TIM6->ARR = us;
        TIM6->CNT = 0;
        TIM6->CR1 |= TIM_CR1_CEN;
        while(!(TIM6->SR & TIM_SR_UIF));
        TIM6->SR &= ~TIM_SR_UIF;
    }
}

void tim6_delay_ms(uint16_t nms)
{
    tim6_delay_us((uint32_t)(nms * 1000));
}

void tim6_start(void)
{
    tim6.allcnt = 0;
    TIM6->CR1 &= ~TIM_CR1_CEN;  // disable TIM6
    TIM6->ARR = 0xFFFF;
    TIM6->CNT = 0;
    TIM6->SR &= ~TIM_SR_UIF;     // clear event update flag
    TIM6->DIER |= TIM_DIER_UIE;  // enable interrupt
    TIM6->CR1 |= TIM_CR1_CEN;
}

uint16_t tim6_stop(void)
{
    TIM6->CR1 &= ~TIM_CR1_CEN;
    return tim6.allcnt * (65535 + 1) + TIM6->CNT;
}

void TIM6_DAC_IRQHandler(void)
{
    if(TIM6->SR & TIM_SR_UIF)
    {
        TIM6->SR &= ~TIM_SR_UIF;
        tim6.allcnt++;
    }
}
