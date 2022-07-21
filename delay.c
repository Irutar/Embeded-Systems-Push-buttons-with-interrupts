#include "delay.h"
#include <AT91SAM9263.h>

#define PIT_REFERENCE_1_MS 6250UL

void init_PIT()
{
  AT91C_BASE_PITC->PITC_PIMR = PIT_REFERENCE_1_MS; //This disables the interrupts and the timer as a side-effect
  AT91C_BASE_PITC->PITC_PIVR; //This clears the status register and counter as a side-effect
}

void delay_using_PIT()
{
  AT91C_BASE_PITC->PITC_PIMR |= AT91C_PITC_PITEN;
  while(AT91C_BASE_PITC->PITC_PISR == (AT91C_BASE_PITC->PITC_PISR & (~AT91C_PITC_PITS)))
    ;
  AT91C_BASE_PITC->PITC_PIMR &= (~AT91C_PITC_PITEN);
  AT91C_BASE_PITC->PITC_PIVR;
}

void delay_ms(unsigned long delay)
{
  volatile unsigned long i = 0;
  for (; i< delay; ++i)
    delay_using_PIT();
}