#include <AT91SAM9263.h>

#include "DBGU.h"
#include "buttons.h"
#include "delay.h"

#define HALF_SECOND_MS 500

void handle_button_presses()
{
  disable_button_interrupts();
  
  unsigned status = AT91C_BASE_PIOC->PIO_ISR;
  if (was_right_button_pressed(status))
    turn_off_right_LED();
   else if (was_left_button_pressed(status))
     turn_on_right_LED();

  clear_button_interrupts();
  enable_button_interrupts();
}

int main()
{
  Open_DBGU();
  printf("Press the buttons\n\r");
  initLED();
  initBUTTONS();
  init_PIT();
  init_button_interrupts(handle_button_presses);
  
  while (1) {
    turn_on_left_LED();
    delay_ms(HALF_SECOND_MS);
    turn_off_left_LED();
    delay_ms(HALF_SECOND_MS);
  }
  
}
