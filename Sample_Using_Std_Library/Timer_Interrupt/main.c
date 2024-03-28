/* timer su dung interrupt */


#include "stm32f10x.h"                  // Device header

volatile int StateLed = 0;

void TIM2_IRQHandler(void);
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		if (StateLed == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			StateLed = 1;
		}
		else if (StateLed == 1)
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			StateLed = 0;
		}
		else
		{
		}
	}
	else
	{
	}
	
	
}

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
	initTimer.TIM_Prescaler = 7200;  /* Clock 72 Mhz */
	initTimer.TIM_Period = 10000;	/* Delay 1s */
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
	
	while(1)
	{
		
	}
	
}
