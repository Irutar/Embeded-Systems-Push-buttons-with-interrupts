#include "buttons.h"
#include <stdbool.h>
#include <AT91SAM9263.h>

#define PIO_PERB (volatile unsigned int*) 0xFFFFF400
#define PIO_PERC (volatile unsigned int*) 0xFFFFF600
#define PIO_OERB (volatile unsigned int*) 0xFFFFF410
#define PIO_OERC (volatile unsigned int*) 0xFFFFF610
#define PIO_CODRB (volatile unsigned int*) 0xFFFFF434
#define PIO_CODRC (volatile unsigned int*) 0xFFFFF634
#define PIO_SODRB (volatile unsigned int*) 0xFFFFF430
#define PIO_SODRC (volatile unsigned int*) 0xFFFFF630
#define PIO_ODSRC (volatile unsigned int*) 0xFFFFF638
#define PIO_ODRC (volatile unsigned int*) 0xFFFFF614
#define PIO_PDSR (volatile unsigned int*) 0xFFFFF63C
#define PCM_PCER (volatile unsigned int*) 0xFFFFFC10
#define PIO_PUER (volatile unsigned int*) 0xFFFFF664

#define USERLED1 (volatile unsigned int) 1UL<<8
#define USERLED2 (volatile unsigned int) 1UL<<29
#define USERCLIC1 (volatile unsigned int) 1UL<<4
#define USERCLIC2 (volatile unsigned int) 1UL<<5
#define PCM_CDE (volatile unsigned int) 1UL<<4


#define PIOCDE_INTERRUPT_MASK 1UL << AT91C_ID_PIOCDE

void initLED()
{
  *(PIO_PERB) = USERLED1;
  *(PIO_OERB) = USERLED1;
  *(PIO_SODRB) = USERLED1;

  *(PIO_PERC) = USERLED2;
  *(PIO_OERC) = USERLED2;
  *(PIO_SODRC) = USERLED2;
}


void turn_on_left_LED()
{
 *(PIO_CODRB) = USERLED1;
}


void turn_off_left_LED()
{
 *(PIO_SODRB) = USERLED1;
}


void turn_on_right_LED()
{
  *(PIO_CODRC) = USERLED2;
}


void turn_off_right_LED()
{
  *(PIO_SODRC) = USERLED2;
}




void initBUTTONS()
{
  *(PIO_PERC) = USERCLIC1 | USERCLIC2;
  *(PIO_ODRC) = USERCLIC1 | USERCLIC2;
  *(PCM_PCER) = PCM_CDE;
  *(PIO_PUER) = USERCLIC1 | USERCLIC2;
}


void init_button_interrupts(void* button_interrupt_handler)
{
  disable_button_interrupts();

  AT91C_BASE_AIC->AIC_SMR[AT91C_ID_PIOCDE] = AT91C_AIC_SRCTYPE_EXT_POSITIVE_EDGE | AT91C_AIC_PRIOR_HIGHEST;
  AT91C_BASE_AIC->AIC_SVR[AT91C_ID_PIOCDE] = (unsigned int)button_interrupt_handler;

  clear_button_interrupts();

  enable_button_glitch_filter();
  enable_button_interrupts();
}


void disable_button_interrupts()
{
  AT91C_BASE_AIC->AIC_IDCR = PIOCDE_INTERRUPT_MASK;
  AT91C_BASE_PIOC->PIO_IDR = USERCLIC1 | USERCLIC2;
}


void enable_button_interrupts()
{
  AT91C_BASE_AIC->AIC_IECR = PIOCDE_INTERRUPT_MASK;
  AT91C_BASE_PIOC->PIO_IER = USERCLIC1 | USERCLIC2;
}


void clear_button_interrupts()
{
  AT91C_BASE_AIC->AIC_ICCR = PIOCDE_INTERRUPT_MASK;
  AT91C_BASE_PIOC->PIO_ISR; //clears interrupt status as a side effect of reading
}

void enable_button_glitch_filter()
{
   AT91C_BASE_PIOC->PIO_IFER = USERCLIC1 | USERCLIC2;
}


bool was_left_button_pressed(unsigned interrupt_status)
{
  return interrupt_status & USERCLIC2;
}


bool was_right_button_pressed(unsigned interrupt_status)
{
  return interrupt_status & USERCLIC1;
}
