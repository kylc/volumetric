#include <stdlib.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/delay.h>

#include <screen.h>
#include <spi.h>
#include <usart.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

static uint16_t position_deg;

ISR(PCINT0_vect) {
  // Per-degree interrupt
  if(PINB & _BV(0)) {
    position_deg = position_deg + 10;
    if(position_deg >= 360) {
      position_deg = 0;
    }
  }

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

  // TODO: PCINT0
  DDRB |= 1 << 0;
}

int main() {
  // 16MHz
  clock_prescale_set(clock_div_1);

  setup();
  spi_setup();
  screen_clear();
  usart_init();

  // PCINT0 on PB0
  PCICR |= _BV(PCIE0);
  PCMSK0 |= _BV(PCINT0) | _BV(PCINT4);

  sei();

  while(true) {
    // TODO: Simulate encoder '1 degree tick'
    PORTB ^= _BV(0);

    screen_clear();
    
    /* usart_send_str("Test\r\n"); */
    for(int c = 0; c < 8; c++) {
      float sin_pos = sinf(position_deg / 180.0 * 3.14 + 3.14 / 8 * c);
      uint8_t sin_r = roundf((sin_pos * 4.0) + 4.0);
      screen_set(sin_r, c, 1, 0, 0);

      float cos_pos = cosf(position_deg / 180.0 * 3.14 + 3.14 / 8 * c);
      uint8_t cos_r = roundf((pos2 * 4.0) + 4.0);
      screen_set(cos_r, c, 0, 0, 1);
    }

    /* for(int i = 0; i < 8; i++) { */
    /*   for(int j = 0; j < 8; j++) { */
    /*     screen_set(i, i, true); */
    /*     screen_set(7 - j, j, true); */
    /*   } */
    /* } */

    screen_update();
  }

  return 0;
}

