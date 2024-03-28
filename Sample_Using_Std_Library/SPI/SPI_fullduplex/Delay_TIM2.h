/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build Delay_TIM2.h using TIM2 with interrupt for stm32f103c8t6
**
** ###################################################################
*/

#ifndef _DELAY_TIM2_H_
#define _DELAY_TIM2_H_

#include "stm32f10x.h"                  // Device header

#define DELAY_1SECOND 1000
#define TRUE 		  1
#define VALUE_INIT_0  0
#define CLOCK_PRESCALER_72MHZ 7200
#define CLOCK_PERIOD_MS 10

/* Variable using count cycle TIM2 */
volatile static int msTick = VALUE_INIT_0;

/**
	* This function correctly work in 72Mhz 
  * @brief  Init TIM2 using interrupt for stm32f103c8t6
  */
void TIM2_init_IT(void);

/* Delay_ms Function */
void Delay_ms(int p_Time_ms);
	
/* Interrupt for TIM2 Fucntion */
void TIM2_IRQHandler(void);


#endif
