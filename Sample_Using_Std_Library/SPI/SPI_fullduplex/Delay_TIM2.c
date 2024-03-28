/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build Delay_TIM2.c using TIM2 with interrupt for stm32f103c8t6
**
** ###################################################################
*/
#include "Delay_TIM2.h"
#include "stm32f10x.h"                  // Device header
/**
	* This function correctly work in 72Mhz 
  * @brief  Init TIM2 using interrupt for stm32f103c8t6
  */
void TIM2_init_IT(void)
{
	/* Enable RCC for TIM2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* Init TIM2 */
	TIM_TimeBaseInitTypeDef initTimer;
	initTimer.TIM_CounterMode = TIM_CounterMode_Up;
	initTimer.TIM_Prescaler = CLOCK_PRESCALER_72MHZ;
	initTimer.TIM_Period = CLOCK_PERIOD_MS;
	TIM_TimeBaseInit(TIM2, &initTimer); 
	
	/* Init NVIC for TIM2 */
	NVIC_InitTypeDef initNVIC_Timer;
	initNVIC_Timer.NVIC_IRQChannel = TIM2_IRQn;
	initNVIC_Timer.NVIC_IRQChannelCmd = ENABLE;
	initNVIC_Timer.NVIC_IRQChannelPreemptionPriority = 0;
	initNVIC_Timer.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&initNVIC_Timer);
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
	
	/* Enable TIM2 */
	TIM_Cmd(TIM2, ENABLE);
}

/* Delay_ms Function */
void Delay_ms(int p_Time_ms)
{
		volatile int startTick = msTick;
	/* (msTick - startTick) is the value count of timer */
	while ( (msTick - startTick) < p_Time_ms ){}
}

/* Interrupt for TIM2 Fucntion */
void TIM2_IRQHandler(void)
{
	/* Check interrupt flag TIM2, if it's RESET value -> Clear it */
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		msTick++;
	}
}
