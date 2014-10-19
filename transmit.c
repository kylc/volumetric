#include <transmit.h>

#include <usart.h>

void transmit_init(void) {
}

void transmit_read_frame(uint8_t *id, uint8_t data[HOLO_COLS][HOLO_ANGS][3]) {
  *id = usart_recv();

  for(int col = 0; col < HOLO_COLS; col++) {
    for(int ang = 0; ang < HOLO_ANGS; ang++) {
      for(int chan = 0; chan < 3; chan++) {
        data[col][ang][chan] = usart_recv();
      }
    }
  }
}
