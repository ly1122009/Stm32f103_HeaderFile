
#include "stm32f10x.h"                  // Device header


#define DELAY_1SECOND 1000
#define TRUE 		  1
#define VALUE_INIT_0  0
#define CLOCK_PRESCALER_36MHZ 3600
#define CLOCK_PERIOD_MS 10

volatile static uint8_t temp = 0;

/* Variable using count cycle TIM2 */
volatile int msTick = VALUE_INIT_0;

/* Interrupt for TIM2 Fucntion */
void TIM2_IRQHandler(void);

/* Delay_ms Function */
void Delay_ms(int p_Time_ms);

void SPI2_IRQHandler(void);
void SPI2_IRQHandler(void)
{	
	if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) != RESET)
	{
		char c = SPI_I2S_ReceiveData(SPI1);		
	}
}


void RCC_PLLInit_36Mhz(void);
void TIM2_Init_t(void);
void GPIO_Init_PC13(void);
void NVIC_InitSPI(void);
void SPI1_InitPin(void);
void SPI1_Init(void);
void SPI1_send(uint8_t p_data);
uint8_t SPI1_receive(void);

int main()
{
	/* Init RCC */
	//RCC_PLLInit_36Mhz();
	//TIM2_Init_t();
	//GPIO_Init_PC13();
	SPI1_Init();  // Using clock 72Mhz
	
	//SPI_I2S_ReceiveData(SPI1);
	
	temp = SPI1_receive();
	
	while(1)
	{
		
	}
	
}

void NVIC_InitSPI(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

  /* 1 bit for pre-emption priority, 3 bits for subpriority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
	/* Configure and enable SPI_MASTER interrupt -------------------------------*/
  NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

uint8_t SPI1_receive(void)
{
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	
	// Receive data
	return SPI_I2S_ReceiveData(SPI1);

}

void SPI1_send(uint8_t p_data)
{
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
	// Send data
	SPI_I2S_SendData(SPI1, p_data);
}

void SPI1_Init(void)  
{
	// Init SPI1 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	// Config SPI1
	SPI_InitTypeDef init_SPI;
	init_SPI.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	init_SPI.SPI_CPHA = SPI_CPHA_1Edge;
	init_SPI.SPI_CPOL = SPI_CPOL_Low;
	init_SPI.SPI_DataSize = SPI_DataSize_16b;
	init_SPI.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	init_SPI.SPI_FirstBit = SPI_FirstBit_MSB;
	init_SPI.SPI_Mode = SPI_Mode_Slave;
	init_SPI.SPI_NSS = SPI_NSS_Soft;
	init_SPI.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &init_SPI);
	
	// NVIC for SPI1 
	NVIC_InitSPI();
	
	// Enable SPI1 
	SPI_Cmd(SPI1, ENABLE);
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
	
	/* Init SPI1 pin */
	SPI1_InitPin();
	

}

void SPI1_InitPin(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	// Init MOSI (PA7), SCK(PA5)
	GPIO_InitTypeDef init_SPI_pin;
	init_SPI_pin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	init_SPI_pin.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5;
	init_SPI_pin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &init_SPI_pin);
	
	// Init MISO (PA6)
	init_SPI_pin.GPIO_Mode = GPIO_Mode_AF_PP;
	init_SPI_pin.GPIO_Pin = GPIO_Pin_6;
	init_SPI_pin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &init_SPI_pin);
	
	// GPIO pin for SS (PA4)
	init_SPI_pin.GPIO_Mode = GPIO_Mode_IPD;
	init_SPI_pin.GPIO_Pin = GPIO_Pin_4;
	init_SPI_pin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &init_SPI_pin);
	
}

void GPIO_Init_PC13(void)
{
	/* Enable RCC for GPIO port C*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/* Init GPIO PC13 */
	GPIO_InitTypeDef initGPIO;
	initGPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	initGPIO.GPIO_Pin = GPIO_Pin_13;
	initGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &initGPIO);
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

void TIM2_Init_t(void)
{
	/* Enable RCC for TIM2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* Init TIM2 */
	TIM_TimeBaseInitTypeDef initTimer;
	initTimer.TIM_CounterMode = TIM_CounterMode_Up;
	initTimer.TIM_Prescaler = CLOCK_PRESCALER_36MHZ;
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

void RCC_PLLInit_36Mhz(void)
{
		/* Init RCC */
	RCC_DeInit();  /* Reset the RCC return init state */
	
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET); // Wait HSE enable
	
	/* Config PLL */
	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);  // Using 36Mhz clock ( (8 / 2) * 9 ) = 36Mhz
	
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
}


