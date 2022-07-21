#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include <stdbool.h>

void initLED();
void turn_on_left_LED();
void turn_off_left_LED();
void turn_on_right_LED();
void turn_off_right_LED();

void initBUTTONS();
void init_button_interrupts(void* button_interrupt_handler);
void disable_button_interrupts();
void enable_button_interrupts();
void clear_button_interrupts();
void enable_button_glitch_filter();

bool was_left_button_pressed(unsigned interrupt_status);
bool was_right_button_pressed(unsigned interrupt_status);

#endif