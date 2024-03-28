#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_adc.h"
#include "string.h"
#include<stdio.h> 

#define HAL_GPIO_WritePin(PORT,PIN,STATE) GPIO_WriteBit(PORT, PIN, STATE)
#define RED_LED_H() GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET)
#define RED_LED_L() GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET)
	
  
  #define SPI_SLAVE                    SPI2
  #define SPI_SLAVE_CLK                RCC_APB1Periph_SPI2
  #define SPI_SLAVE_GPIO               GPIOB
  #define SPI_SLAVE_GPIO_CLK           RCC_APB2Periph_GPIOB 
  #define SPI_SLAVE_PIN_SCK            GPIO_Pin_13
  #define SPI_SLAVE_PIN_MISO           GPIO_Pin_14
  #define SPI_SLAVE_PIN_MOSI           GPIO_Pin_15 
  #define SPI_SLAVE_IRQn               SPI2_IRQn

#define GPIO_PIN_RESET Bit_RESET
#define GPIO_PIN_SET Bit_SET

void TimingDelay_Decrement(void);
void HAL_Delay(__IO uint32_t nTime);

#endif
