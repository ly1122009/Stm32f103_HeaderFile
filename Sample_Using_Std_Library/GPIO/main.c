/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build a GPIO program for stm32f103c8t6
**
** ###################################################################
*/
#include "stm32f10x.h"                  // Device header

void delay(void);
void delay(void)
{
	volatile int i;
	for (i = 0; i < 500000; i++);
}

int main()
{
	/* Enable RCC for port C */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/* Init GPIO output PC13 */
	GPIO_InitTypeDef gpioInit;
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpioInit);
	
	while(1)
	{
		/* Blink led */
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay();
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay();
	}
}
