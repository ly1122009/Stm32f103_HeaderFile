/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build GPIO_Module.h
**
** ###################################################################
*/

#ifndef _GPIO_MODULE_H_
#define _GPIO_MODULE_H_

#include "stm32f10x.h"                  // Device header

void GPIO_InitPC13_Input();

void GPIO_InitPB9_Output();

void GPIO_Configuration(void);

#endif