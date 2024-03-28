/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build RCC program for stm32f103c8t6
**
** ###################################################################
*/
#include "stm32f10x.h"                  // Device header

#define TRUE 1

/* Delay to test systems Clock */
void delay(void);

int main()
{
	/* Init RCC */
	RCC_DeInit();  /* Reset the RCC return init state */
	
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET); // Wait HSE enable
	
	/* Config PLL */
	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);  // Using 36Mhz clock
	
	/* Enable PLL */
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);  // Wait PLL enable
	
	/* Choose PLL is source clock */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
	
	/* Config AHB */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);  /* AHB_Divide = 1, Clock 36Mhz */
	
	/* Config APB1 */
	RCC_PCLK1Config(RCC_HCLK_Div1);  /* APB1_Divide = 1, Clock 36Mhz */
	
	/* Congfig APB2 */
	RCC_PCLK2Config(RCC_HCLK_Div1);  /* ABP2_Divide = 1, Clock 36Mhz */
	
	/* Enable RCC for GPIO port C */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/* Init GPIO PC13 */
	GPIO_InitTypeDef initGPIO_PC13;
	initGPIO_PC13.GPIO_Mode = GPIO_Mode_Out_PP;
	initGPIO_PC13.GPIO_Pin = GPIO_Pin_13;
	initGPIO_PC13.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &initGPIO_PC13);
	
	while(TRUE)
	{
		/* Blink led */
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay();
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay();
	}	
	
}
/* Delay to test systems Clock */
void delay(void)
{
	volatile int i;
	for (i = 0; i < 500000; i++);
}

