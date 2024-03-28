/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build main.h 
**
** ###################################################################
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm32f10x.h"                  // Device header
//#include "Delay_TIM2.h"
//#include "GPIO_Module.h"
//#include "SPI_Module.h"

volatile static uint8_t Flag_end = 0;

typedef struct
{
	uint8_t Master_Send;
	uint8_t Slave_Receive;
	uint8_t Slave_Send;
	uint8_t Master_Receive;
} t_framedata;

volatile static t_framedata t_frame_1;





#endif