#include "uart.h" 
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

void USART1_Init()
{
	// Initialization struct
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// Step 1: USART1 initialization
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1, ENABLE);
	
	// Step 2: GPIO initialization for Tx and Rx pin
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// Tx pin initialization as push-pull alternate function
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	// Rx pin initialization as input floating
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// Transmit a character over USART1 A9/TX
void USART1_PutChar(uint16_t Data) {
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
   // USART1->DR = (Data & 0xFF);
	  //USART1->DR = (Data & (uint16_t)0x01FF);
   
	  // while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE)){}
	   // Send a char using USART2
	   USART_SendData(USART1, Data);
     
}
 
// Receive a character over USART1 A10/RX
int get_char_usart1(){
 
    // this while loop makes the call blocking
    // will wait until byte received
    // while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    // return USART1->DR & 0xFF;
 
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET){
        return USART1->DR & 0xFF;
    } else {
        return -1;
    }
}
 
// Transmit a string over USART1 A9/TX                  
void USART1_PutString(char *s)
{
	// Send a string
	while (*s)
	{
		USART1_PutChar(*s);
		s++;
	}
	
}
//

void num(int x)
{
	static uint8_t n = 0;
	static uint8_t m = 0;
	if(x>9)
	{
		n=x/10;
		USART1_PutChar((n+48));	
		m=x%10;
		USART1_PutChar((m+48));
			m=0;n=0;
	}	
	else
	{
		USART1_PutChar((x+48));
	}
	USART1_PutString("\r\n");	
}
