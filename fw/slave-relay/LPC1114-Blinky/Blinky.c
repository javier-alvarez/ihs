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

#define LED       (1<<8)      /* LED D1 connect to PIO1_8 */

/* Import external functions from Serial.c file                               */
extern void SER_init (void);
extern void SER_init (void);    
extern int sendchar (int c);

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

void delay(int a)
{
	int b,c;
	 for (b=0;b<a;b++)
	 	 for (c=0;c<2000;c++)
	     __NOP();
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {                               /* Main Program               */
  char state = 0;
	
  SystemInit(); // SystemCoreClock/100);          /* Generate IRQ each ~10 ms   */

  LED_init();                                   /* LED Initialization         */
  SER_init();                                   /* UART#1 Initialization      */

  while (1)
	{                                   /* Loop forever               */
	  delay(1000);
    state++;
			
		if (state & 0x1)
		{
			LED_On();
		  sendchar('A');
		  sendchar('\n');
		  sendchar('\r');			
		}
		else
		{
			LED_Off();			
		}
   }
}
