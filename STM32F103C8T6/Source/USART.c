/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build USART.c for stm32f103c8t6
**
** ###################################################################
*/
#include "USART.h"
#include "GPIO.h"
#include "NVIC.h"


/* MACRO */
/* USART_InitRxTxPORT_USART2 */
#define MODE2 8
#define CNF2  10
#define MODE3 12
#define CNF3  14
#define MODE2_OUT_MAX50 3
#define CNF2_PUSH_PULL 2
#define MODE3_INPUT  3
#define MODE3_FLOATING 1

/* USART_Congfig */
#define CONST_UART 16
#define CONST_CLOCK 1000
#define DIV_MANTISSA 4
#define DIV_FRACTION 0
#define WORDLENGTH 12
#define LENGTH_8BIT 1
#define LENGTH_9BIT 1
#define PARITY      10
#define PARITY_DISABLE 1
#define PARITY_ENABLE 1
#define PARITY_SELECTION 9
#define EVEN_PARITY 1
#define ODD_PARITY 1
#define STOPBIT 12
#define STOPBIT_1 3
#define STOPBIT_05 1
#define STOPBIT_2 2
#define STOPBIT_15 3
#define UART_RECEIVER 2
#define ENABLE_RECEIVER 1
#define UART_TRANSFER 3
#define ENABLE_TRANSFER 1

/* USART_Congfig_IT */
#define RXNEIE 5
#define TXEIE 7 
#define RXNEIE_ENABLE 1
#define TXEIE_ENABLE 1

/* USART_Enable */
/* USART_Disable */
#define UE 13
#define UE_ENABLE 1
#define UE_DISABLE 1

/* USART_Sendchar */
/* USART_SendString */
#define RXNE 5
#define TXE  7 
#define TRANSFER 1
#define TRANSFER_COMPLETED 1
#define DATA_RECEIVED 1
#define DATA_TRANMITTED 1

/* USART_ReceiverChar */
/* USART_ReceiverString */
#define RXNE 5
#define RXNE_RECEIVE 1
#define RECEIVE_COMPLETED 0

/* ----------------------------------------------------------------------------
   -- Fucntion for USART
   ---------------------------------------------------------------------------- */
void USART_InitRxTxPORT_USART2(void)  /* Using init GPIO Tx Rx in USART2 */
{
	volatile unsigned int Reg_Temp = 0;
		/* PA2 = Tx (Output) */
	Reg_Temp &= ~(15u << MODE2);  /* Clear bit 8 -> 11 */
	Reg_Temp |= (MODE2_OUT_MAX50 << MODE2);  /* Output max speed 50 Mhz */
	Reg_Temp |= (CNF2_PUSH_PULL << CNF2); /*  Alternate function output Push-pull */
	
		/* PA3 = Rx (Input) */
	Reg_Temp &= ~(15u << MODE3);  /* Clear bit 12 -> 15 */
	Reg_Temp &= ~(MODE3_INPUT << MODE3);  /* Select input mode */
	Reg_Temp |= (MODE3_FLOATING << CNF3); /* Floating input (reset state) */
	GPIO_A -> GPIO_CRL = Reg_Temp; 
}

void USART_Congfig(USART_Type*USARTx, volatile unsigned int p_BaudRate, volatile unsigned int p_ClockSource, volatile unsigned int p_BitData, volatile unsigned int p_Parity, volatile unsigned int p_StopBit)    /* Using Init and Congfig USART without Interrupt */
{
		/* Congfig Tx pin, Rx pin   */
		USART_InitRxTxPORT_USART2();
	
		/* Declare variable temp */
		volatile float Temp_float = 0;
		volatile unsigned int Temp_Mantissa = 0;
		volatile float Temp_Fraction = 0;
		
		/* Algorithm */
		Temp_float = ((p_ClockSource * CONST_CLOCK) / p_BaudRate) / CONST_UART;
		Temp_Mantissa = (unsigned int)Temp_float;
		Temp_Fraction = (float)(Temp_float - Temp_Mantissa);
			
		/* Congfig Baudrate */
		USARTx -> BRR |= (Temp_Mantissa << DIV_MANTISSA);  /* Set div baud = 52 (Mantissa) */ /* BaudRate = 9600 */
		USARTx -> BRR |= (((unsigned int)(Temp_Fraction)) << DIV_FRACTION);   /* Set Div Fraction */
  	
		/* Congfig Bit data */
		if(p_BitData == USART_Congfig_Bitdata_8)
		{
			USARTx -> CR1 &= ~(LENGTH_8BIT << WORDLENGTH);  /* 1 Start bit, 8 bit data, n stop bit */
		}
		else if (p_BitData == USART_Congfig_Bitdata_9)
		{
			USARTx -> CR1 |= (LENGTH_9BIT << WORDLENGTH);  /* 1 Start bit, 9 bit data, n stop bit */
		}	
		else
		{
		}
			
		/* Congfig Parity */
		if(p_Parity == USART_Congfig_Parity_NoParity)
		{
			USARTx -> CR1 &= ~(PARITY_DISABLE << PARITY);  /* Disable Parity */	
		}
		else if ( p_Parity == USART_Congfig_Parity_Even)
		{
			USARTx -> CR1 &= ~(EVEN_PARITY << PARITY_SELECTION);  /* Even parity */
			USARTx -> CR1 |= (PARITY_ENABLE << PARITY);  /* Enable Parity */			
		}
		else if ( p_Parity == USART_Congfig_Parity_Odd)
		{
			USARTx -> CR1 |= (ODD_PARITY << PARITY_SELECTION);  /* Odd parity */
			USARTx -> CR1 |= (PARITY_ENABLE << PARITY);  /* Enable Parity */
		}
		else
		{}
			
		/* Congfig Stop bit  */
		if(p_StopBit == USART_Congfig_StopBit_1)	
		{
			USARTx -> CR2 &= ~(STOPBIT_1 << STOPBIT);  /* 1 stop bit */
		}
		else if (p_StopBit == USART_Congfig_StopBit_05)
		{
			USARTx -> CR2 |= (STOPBIT_05 << STOPBIT);  /* 0.5 stop bit */
		}
		else if (p_StopBit == USART_Congfig_StopBit_2)
		{
			USARTx -> CR2 |= (STOPBIT_2 << STOPBIT);  /* 2 stop bit */
		}
		else if (p_StopBit == USART_Congfig_StopBit_15 )
		{
			USARTx -> CR2 |= (STOPBIT_15 << STOPBIT);  /* 1.5 stop bit */
		}			
		else
		{
		}
		/* Enable Receiver and Transmitter */
		USARTx -> CR1 |= (ENABLE_RECEIVER << UART_RECEIVER);  /* Enable Receiver*/ 
		USARTx -> CR1 |= (ENABLE_TRANSFER << UART_TRANSFER);	/* Enable Transmitter */
	
}

void USART_Congfig_IT(USART_Type*USARTx,volatile unsigned int p_Use_Interrupt_For ,volatile unsigned int p_BaudRate, volatile unsigned int p_ClockSource, volatile unsigned int p_BitData, volatile unsigned int p_Parity, volatile unsigned int p_StopBit)    /* Using Init and Congfig USART with Interrupt */
{
		/* Congfig NVIC */
	if(USARTx == USART1)
	{
		NVIC_EnableInterrupt(ID_USART1);
	}
	else if (USARTx == USART2)
	{
		NVIC_EnableInterrupt(ID_USART2);
	}
	else if (USARTx == USART3)
	{
		NVIC_EnableInterrupt(ID_USART3);
	}	
	else
	{
	}
	
		/* Congfig Interrupt for USART */
	if(p_Use_Interrupt_For == USART_Congfig_IT_Use_Interrupt_For_Receiver)
	{
		USART2 -> CR1 |= (RXNEIE_ENABLE << RXNEIE);  /* Enable interrupt Receiver */
	}
	else if ( p_Use_Interrupt_For == USART_Congfig_IT_Use_Interrupt_For_Transmitter )
	{
		USART2 -> CR1 |= (TXEIE_ENABLE << TXEIE);  /* Enable interrupt Transmitter */
	}
	else if ( p_Use_Interrupt_For == USART_Congfig_IT_Use_Interrupt_For_Both_Receiver_Transmitter )
	{
		USART2 -> CR1 |= (RXNEIE_ENABLE << RXNEIE);  /* Enable interrupt Receiver */
		USART2 -> CR1 |= (TXEIE_ENABLE << TXEIE);  /* Enable interrupt Transmitter */
	}	
	else
	{
	}	
	
		/* Congfig USART */
	USART_Congfig(USARTx,p_BaudRate,p_ClockSource,p_BitData,p_Parity,p_StopBit);
		
}

void USART_Enable(USART_Type*USARTx){    /* Using Enable USARTx */
	/* Enable USARTx */
	USARTx -> CR1 |= (UE_ENABLE << UE);  /* Enable USART */
}

void USART_Disable(USART_Type*USARTx){  	/* Using Disable USARTx */

	/* Disable USARTx */
	USARTx -> CR1 &= ~(UE_DISABLE << UE);  /* Disable USART */
	
}

unsigned int USART_CheckFlagInterrupt(USART_Type*USARTx, volatile unsigned int p_CheckBitReceiverOrTransmitter){     /* Using check Flag USART interrupt */
	
	/* Check flag interrupt */
	if( p_CheckBitReceiverOrTransmitter == USART_CheckFlagInterrupt_CheckBitReceiverOrTransmitter_Receiver)
	{
		return (USART2 -> SR & (DATA_RECEIVED << RXNE));
	}
	else if (p_CheckBitReceiverOrTransmitter == USART_CheckFlagInterrupt_CheckBitReceiverOrTransmitter_Transmitter)
	{
		return (USART2 -> SR & (DATA_TRANMITTED << TXE));
	}
	else
	{
		return 0;
	}
}

void USART_ClearFlagInterrupt(USART_Type*USARTx, volatile unsigned int Flag_Receiver_Or_Transmitter)    /* Clear Flag USART interrupt */
{
	if( Flag_Receiver_Or_Transmitter == USART_ClearFlagInterrupt_Flag_Receiver )
	{
		USART2 -> SR &= ~(DATA_RECEIVED << RXNE);  /* Clear bit Receiver */
	}
	else if ( Flag_Receiver_Or_Transmitter == USART_ClearFlagInterrupt_Flag_Transmitter )
	{
		USART2 -> SR &= ~(DATA_TRANMITTED << TXE);  /* Clear bit Transmitter */
	}
	else if ( Flag_Receiver_Or_Transmitter == USART_ClearFlagInterrupt_Flag_Both_Transmitter_And_Receiver )
	{
		USART2 -> SR &= ~(DATA_RECEIVED << TXE);  /* Clear bit Transmitter */
		USART2 -> SR &= ~(DATA_TRANMITTED << RXNE);  /* Clear bit Receiver */
	}
	else
	{
	}
}

void USART_Sendchar(USART_Type*USARTx , volatile unsigned char p_Char_Send){     /* Send char datatype by USART */

		while ((USARTx -> SR & (TRANSFER << TXE)) == TRANSFER_COMPLETED);  /* wait Transmit complete */
		(USARTx -> DR) = p_Char_Send;
		for(volatile unsigned int Count_Delay = 0; Count_Delay < 5000; Count_Delay++);
}

void USART_SendString(USART_Type*USARTx , volatile unsigned char p_String_Send[])    /* Send string datatype by USART */
{
	volatile unsigned int count = 0;	
	while(p_String_Send[count] != '\0')
	{
		USART_Sendchar(USARTx,p_String_Send[count]);
		count++;
	}
}

void USART_ReceiverChar(USART_Type*USARTx, volatile unsigned char *p_Char_Receiver)    /* Receive char datatype by USART */
{
	while ((USARTx -> SR & (RXNE_RECEIVE << RXNE)) == RECEIVE_COMPLETED){}  /* wait Receiver complete */
	*p_Char_Receiver = (unsigned char)(USARTx -> DR);
}

void USART_ReceiverString(USART_Type*USARTx, volatile unsigned char p_Char_String[], volatile unsigned int p_Strlen_String)    /* Receive string datatype by USART */
{
		for(volatile unsigned int Count = 0; Count < p_Strlen_String; Count++)
	{
		USART_ReceiverChar(USARTx,&p_Char_String[Count]);
	}
	
}
	
	