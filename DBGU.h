#ifndef _DBGU_H_
#define _DBGU_H_

void Open_DBGU();
void disable_all_DBGU_interrupts();
void turn_off_and_reset_reciver();
void turn_off_and_reset_transmitter();
void init_PIO_ports();
void configure_throughput();
void configure_operation_mode();
void Open_DBGU_INT();
void turn_on_receiver();
void turn_on_transmitter();

void send_char(char character);
char get_char();
void printf(const char* string);
void dbgu_print_ascii(const char* a);

#endif