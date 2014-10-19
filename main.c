#include <stdlib.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/delay.h>

#include <screen.h>
#include <holo.h>
#include <spi.h>
#include <usart.h>
#include <transmit.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

static uint16_t position_deg = 0;
static uint8_t t = 0;

ISR(INT0_vect) {
  // Per-degree interrupt
  position_deg = position_deg + 1;
  t = (t+1) % 8;
  if(position_deg >= 360) {
    position_deg = 0;
  }
  //t = position_deg / HOLO_ANGS;
}

ISR(PCINT0_vect) {
  // Zero interrupt
  if(PINB & _BV(4)) {
    position_deg = 0;
  }
}

void setup(void) {
  DDRB = _BV(SPI_MISO_PIN) | _BV(SPI_MOSI_PIN) | _BV(SPI_SCLK_PIN) | _BV(SCREEN_LATCH_PIN);
  DDRC = 0xFF;
  DDRD = 0x08;
  DDRE = 0x07;

  // TODO: INT0
  DDRD &= ~(1 << 0);
  PORTD |= (1 << 0);

  // INT0 simulated trigger
  DDRD |= _BV(PIND1);
}

int main(void) {
  // 8MHz
  clock_prescale_set(clock_div_1);

  setup();
  spi_setup();
  usart_init();
  screen_clear();
  holo_clear();

  PCICR |= _BV(PCIE0);
  PCMSK0 |= _BV(PCINT4);

  // INT0 on PD0 on falling edge
  EICRA |= (1 << ISC01) | (0 << ISC00);
  EIMSK |= _BV(INT0);

  sei();

  holo_generate_test();
  while(true) {
    // TODO: Simulate encoder '1 degree tick'
    PORTD ^= _BV(PIND1);

    screen_clear();

    if(usart_available()) {
      uint8_t board_id;

      transmit_read_frame(&board_id, holodata);
    }

    /* for(int c = 0; c < 8; c++) { */
    /*   float sin_pos = sinf(position_deg / 180.0 * 3.14 + 3.14 / 8 * c); */
    /*   uint8_t sin_r = round((sin_pos * 4.0) + 4.0); */
    /*   screen_set(c, sin_r, 0b100); */
    /*  */
    /*   float cos_pos = cos(position_deg / 180.0 * 3.14 + 3.14 / 8 * c); */
    /*   uint8_t cos_r = round((cos_pos * 4.0) + 4.0); */
    /*   screen_set(c, cos_r, 0b001); */
    /* } */

    /* Update screen */
    for (int r=0; r<8; r++) {
        for (int z=0; z<8; z++) {
            screen_set(r, z, holo_get(r,t,z));
        }
    }

    screen_update();
  }

  return 0;
}

