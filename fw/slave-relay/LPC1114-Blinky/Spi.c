
#include "LPC11xx.h"                            /* LPC11xx definitions        */

#define USE_CS                   0
#define SSP_DEBUG                0

/* SPI read and write buffer size */
#define SSP_BUFSIZE              16
#define FIFOSIZE                 8

#define DELAY_COUNT              10
#define MAX_TIMEOUT              0xFF

/* SSP CR1 register */
#define SSPCR1_LBM      (0x1<<0)
#define SSPCR1_SSE      (0x1<<1)
#define SSPCR1_MS       (0x1<<2)
#define SSPCR1_SOD      (0x1<<3)

/* Port0.2 is the SSP select pin */
#define SSP0_SEL        (0x1<<2)
        
/* SSP Status register */
#define SSPSR_TFE       (0x1<<0)
#define SSPSR_TNF       (0x1<<1) 
#define SSPSR_RNE       (0x1<<2)
#define SSPSR_RFF       (0x1<<3) 
#define SSPSR_BSY       (0x1<<4)

/* SSP CR0 register */
#define SSPCR0_DSS      (0x1<<0)
#define SSPCR0_FRF      (0x1<<4)
#define SSPCR0_SPO      (0x1<<6)
#define SSPCR0_SPH      (0x1<<7)
#define SSPCR0_SCR      (0x1<<8)

/* SSP Interrupt Mask Set/Clear register */
#define SSPIMSC_RORIM   (0x1<<0)
#define SSPIMSC_RTIM    (0x1<<1)
#define SSPIMSC_RXIM    (0x1<<2)
#define SSPIMSC_TXIM    (0x1<<3)

/* SSP0 Interrupt Status register */
#define SSPRIS_RORRIS   (0x1<<0)
#define SSPRIS_RTRIS    (0x1<<1)
#define SSPRIS_RXRIS    (0x1<<2)
#define SSPRIS_TXRIS    (0x1<<3)

/*----------------------------------------------------------------------------
  Initialize SPI pins, frequency, etc
 *----------------------------------------------------------------------------*/
void SPI0_init(void) {
	uint8_t i, Dummy;
	
	// GPIO Initializationx
	
	LPC_SYSCON->PRESETCTRL    |= (1<<0);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<11) | (1<<16); // Enable clock for SPI and IOCON
	
  LPC_SYSCON->SSP0CLKDIV     = 0x02;   // Divided by 2
	
  // Configure the SPI pins
	
	LPC_IOCON->PIO0_8  &= ~0x07;    // SSP Reset Value I/O config
  LPC_IOCON->PIO0_8  |=  0x01;    // SSP MISO
	
	LPC_IOCON->PIO0_9  &= ~0x07;    // SSP Reset Value I/O config
  LPC_IOCON->PIO0_9  |=  0x01;    // SSP MOSI

	LPC_IOCON->SCK_LOC  =  0x02;    // CLK and PIO0_6
  LPC_IOCON->PIO0_6  &= ~0x07;    // Reset
  LPC_IOCON->PIO0_6  |=  0x02;    // SCK0
	
  LPC_IOCON->PIO0_2  &= ~0x07;    // Reset
  LPC_IOCON->PIO0_2  |=  0x01;    // SSP SSEL
	
  LPC_GPIO0->DIR     |= (1<<2); // SSEL
  LPC_GPIO0->MASKED_ACCESS[(1<<2)] = (1<<2);  // SSEL0	
	
	/* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
		
	// SPI initialization
	
  /* Set DSS data to 8-bit, Frame format SPI, CPOL = 0, CPHA = 0, and SCR is 15 */
  LPC_SSP0->CR0 = 0x0707;

  /* SSPCPSR clock prescale register, master mode, minimum divisor is 0x02 */
  LPC_SSP0->CPSR = 0x2;
	
	for ( i = 0; i < FIFOSIZE; i++ )
  {
    Dummy = LPC_SSP0->DR;                /* clear the RxFIFO */
  }
	
	/* Enable the SSP Interrupt */
  //NVIC_EnableIRQ(SSP0_IRQn);
	
  /* Master mode */
  LPC_SSP0->CR1 = SSPCR1_SSE;
	
	/* Set SSPINMS registers to enable interrupts */
  /* enable all error related interrupts */
  //LPC_SSP0->IMSC = SSPIMSC_RORIM | SSPIMSC_RTIM;
	
}

void SPI0_send(uint8_t *buf, uint32_t Length )
{
  uint32_t i;
  uint8_t Dummy = Dummy;
    
  for ( i = 0; i < Length; i++ )
  {
		/* Move on only if NOT busy and TX FIFO not full. */
		while ( (LPC_SSP0->SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
		LPC_SSP0->DR = *buf;
		buf++;

		while ( (LPC_SSP0->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
		/* Whenever a byte is written, MISO FIFO counter increments, Clear FIFO 
		on MISO. Otherwise, when SSP0Receive() is called, previous data byte
		is left in the FIFO. */
		Dummy = LPC_SSP0->DR;
  }
  return; 
}

