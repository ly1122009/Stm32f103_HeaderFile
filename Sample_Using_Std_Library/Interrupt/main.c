/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build interrupt program for stm32f103c8t6
**
** ###################################################################
*/
#include "stm32f10x.h"                  // Device header

#define LED_ON 1
#define LED_OFF 0
#define TRUE 1

/* Using show Led state */
volatile int ledState = LED_OFF;

/* Interrupt Fucntion: Blink led by using button PA4 */
void EXTI4_IRQHandler(void);

int main()
{
	/* Enable RCC for Port A & C */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		
	/* Enable RCC for AFIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/* Init GPIO for PC13 */
	GPIO_InitTypeDef initGPIO_13;
	initGPIO_13.GPIO_Mode = GPIO_Mode_Out_PP;
	initGPIO_13.GPIO_Pin = GPIO_Pin_13;
	initGPIO_13.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &initGPIO_13); 
	
	/* Init GPIO input for PA4 */
	GPIO_InitTypeDef initGPIO_4;
	initGPIO_4.GPIO_Mode = GPIO_Mode_IPU;  
	initGPIO_4.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &initGPIO_4);									//GPIO input pull-up
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);	// Using EXTI mode in PA4
	
	/* Init EXTI for PA4 */
	EXTI_InitTypeDef initEXTI_4;
	initEXTI_4.EXTI_Line = EXTI_Line4;
	initEXTI_4.EXTI_Mode = EXTI_Mode_Interrupt;
	initEXTI_4.EXTI_Trigger = EXTI_Trigger_Rising;
	initEXTI_4.EXTI_LineCmd = ENABLE;
	EXTI_Init(&initEXTI_4);
	
	/* Init NVIC for EXTI of PA4*/
	NVIC_InitTypeDef initNVIC_4;
	initNVIC_4.NVIC_IRQChannel = EXTI4_IRQn;
	initNVIC_4.NVIC_IRQChannelPreemptionPriority = 0;
	initNVIC_4.NVIC_IRQChannelSubPriority = 0;
	initNVIC_4.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&initNVIC_4);

	while(TRUE)
	{
	}
	
}

/* Interrupt Fucntion: Blink led by using button PA4 */
void EXTI4_IRQHandler(void)
{
	/* Check and clear flag interrupt EXTI4 */
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		if (ledState == LED_OFF)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			ledState = LED_ON;
		}
		else if (ledState == LED_ON)
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			ledState = LED_OFF;
		}
		else
		{
		}
	}
}
