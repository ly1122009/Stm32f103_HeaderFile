/* Blink led using TIM*/

#include "stm32f10x.h"                  // Device header



void Delay1Ms(void);
void Delay_Ms(int p_Delay);

void Delay1Ms(void){
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < 1000 );
}

void Delay_Ms(int p_Delay)
{
	while(p_Delay)
	{
		Delay1Ms();
		--p_Delay;
	}
}



int main()
{
	/* Enable RCC for GPIO port C*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/* Enable RCC for TIM2 */
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* Init GPIO PC13 */
	GPIO_InitTypeDef gpioInit;
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpioInit);
	
	/* Init TIM2 */
	TIM_TimeBaseInitTypeDef timerInit;
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 72 - 1;
	
	TIM_TimeBaseInit(TIM2, &timerInit);
		
	TIM_Cmd(TIM2, ENABLE);
	
	while(1)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(1000);
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			Delay_Ms(1000);
		}
	
}
