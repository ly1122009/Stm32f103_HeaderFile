/*
** ###################################################################
**     Processor:           STM32F103C8T6
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 25/01/2024 - 19:58:27
**
**     Abstract:
**         Build STK.h for stm32f103c8t6
**
** ###################################################################
*/
/* Prevention from multiple including the same memory map */
#ifndef STK_H_  /* Check if memory map has not been already included */
#define STK_H_ 

/* ----------------------------------------------------------------------------
   -- Define register
   ---------------------------------------------------------------------------- */
/* Systick (STK) */
typedef struct {
  volatile unsigned int STK_CTRL;
  volatile unsigned int STK_LOAD;
  volatile unsigned int STK_VAL;
  volatile unsigned int STK_CALIB;
} STK_Type;
#define STK_BASE_ADDRESS 0xE000E010
#define STK		((STK_Type*)STK_BASE_ADDRESS)

/* ----------------------------------------------------------------------------
   -- Fucntion for STK
   ---------------------------------------------------------------------------- */
/* Systick */
unsigned int STK_CheckFlag(void);    /* Using check flag STK */
void STK_ClearFlag(void);    /* Using clear flag STK */
void STK_InitSystick(volatile unsigned int p_SourceClock);      /* Using init systick */
void STK_EnableSystick(void);    /* Using enable STK */
void STK_DisableSystick(void);    /* Using disable STK */

void STK_Delay_ms(volatile unsigned int p_ms);

#endif  /* #if !defined(SYSTICK_H_) */

