/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build Delay_ms using TIM2 with interrupt for stm32f103c8t6
**
** ###################################################################
*/
#include "stm32f10x.h"                  // Device header

#define DELAY_1SECOND 1000
#define TRUE 		  1
#define VALUE_INIT_0  0
#define CLOCK_PRESCALER_72MHZ 7200
#define CLOCK_PERIOD_MS 10

/* Variable using count cycle TIM2 */
volatile int msTick = VALUE_INIT_0;

/* Interrupt for TIM2 Fucntion */
void TIM2_IRQHandler(void);

/* Delay_ms Function */
void Delay_ms(int p_Time_ms);

int main()
{
	/* Enable RCC for GPIO port C*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/* Enable RCC for TIM2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* Init GPIO PC13 */
	GPIO_InitTypeDef initGPIO;
	initGPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	initGPIO.GPIO_Pin = GPIO_Pin_13;
	initGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &initGPIO);
	
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
	
	while(TRUE)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		Delay_ms(500); 
		
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		Delay_ms(500); 	
	}
	
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
/* Delay_ms Function */
void Delay_ms(int p_Time_ms)
{
	volatile int startTick = msTick;
	/* (msTick - startTick) is the value count of timer */
	while ( (msTick - startTick) < p_Time_ms ){};
}

