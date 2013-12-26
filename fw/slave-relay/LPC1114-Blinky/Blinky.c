/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher for MCB1000
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2010 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC11xx.h"                            /* LPC11xx definitions        */

#define LED       (1<<8)                        /* LED connected to PIO1_8    */

/* Import external functions from Serial.c file                               */
extern void SER_init (void);
extern void SER_init (void);    
extern int sendchar (int c);
extern volatile unsigned char  clock_1s;

/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void LED_init(void) {

  LPC_SYSCON->SYSAHBCLKCTRL |= (1UL <<  6);     /* enable clock for GPIO      */

  /* configure GPIO as output */						 
  LPC_GPIO1->DIR  |=  LED;
  LPC_GPIO1->DATA = 0;											 
}

void LED_On (void) {

	LPC_GPIO1->DATA |= LED;
}

void LED_Off (void) {

	LPC_GPIO1->DATA &= ~LED;
}


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {                               /* Main Program               */
  char state = 0;
	
	SysTick_Config(SystemCoreClock/100);          /* Generate IRQ each ~10 ms   */
	
  LED_init();                                   /* LED Initialization         */
  SER_init();                                   /* UART#1 Initialization      */

  while (1)
	{                                             /* Loop forever               */		
		if (clock_1s)
		{
			clock_1s = 0;
			state++;
			
			if (state & 0x01)
			{
			  LED_On();
		    sendchar('A');
		    sendchar('\n');
		    sendchar('\r');			
		  }
			else
				LED_Off();

		}	
  }
}
