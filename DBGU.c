#include "DBGU.h"
#include <AT91SAM9263.h>

#define BAUDRATE 115200
#define MCK 100 * 1000000
#define BAUDRATE_GENERATOR_DIVIDER 16
#define GDBU_BAUD_RATE_GENERATOR_CD_FOR(BAUDRATE) MCK / (BAUDRATE_GENERATOR_DIVIDER * BAUDRATE)


void Open_DBGU()
{
  disable_all_DBGU_interrupts();
  turn_off_and_reset_reciver();
  turn_off_and_reset_transmitter();
  init_PIO_ports();
  configure_throughput();
  configure_operation_mode();
  turn_on_receiver();
  turn_on_transmitter();
  Open_DBGU_INT();
}


void disable_all_DBGU_interrupts()
{
  AT91C_BASE_DBGU->DBGU_IDR = AT91C_US_RXRDY | AT91C_US_TXRDY | AT91C_US_ENDRX | AT91C_US_ENDTX | AT91C_US_OVRE | AT91C_US_FRAME |
			      AT91C_US_PARE | AT91C_US_TXEMPTY | AT91C_US_TXBUFE | AT91C_US_RXBUFF | AT91C_US_COMM_TX | AT91C_US_COMM_RX;
}


void turn_off_and_reset_reciver()
{
  AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXDIS | AT91C_US_RSTRX;
}


void turn_off_and_reset_transmitter()
{
  AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXDIS | AT91C_US_RSTTX;
}


void init_PIO_ports()
{
  AT91C_BASE_PIOC->PIO_ASR = AT91C_PC30_DRXD;
  AT91C_BASE_PIOC->PIO_PDR = AT91C_PC30_DRXD;
  AT91C_BASE_PIOC->PIO_ASR = AT91C_PC31_DTXD;
  AT91C_BASE_PIOC->PIO_PDR = AT91C_PC31_DTXD;
}


void configure_throughput()
{
  AT91C_BASE_DBGU->DBGU_BRGR = GDBU_BAUD_RATE_GENERATOR_CD_FOR(BAUDRATE);
}


void configure_operation_mode()
{
  AT91C_BASE_DBGU->DBGU_MR = AT91C_US_CHMODE_NORMAL | AT91C_US_PAR_NONE;
}


void turn_on_receiver()
{
  AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXEN;
}


void turn_on_transmitter()
{
 AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN;
}


void Open_DBGU_INT()
{

}


void send_char(char character)
{
  while(!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY))
    ;
  AT91C_BASE_DBGU->DBGU_THR = (unsigned char)character;
}

char get_char()
{
  while(!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY))
    ;
  return (unsigned char)AT91C_BASE_DBGU->DBGU_RHR;
}

void printf(const char* string)
{
    while(*string)
      send_char(*(string++));
}


void dbgu_print_ascii(const char* a)
{
  printf(a);
}