#include <screen.h>

#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include <spi.h>

uint8_t screen[SCREEN_COLS][SCREEN_BYTES_PER_COL];

void screen_clear(void) {
  memset(screen, 0, sizeof(screen[0][0]) * SCREEN_COLS * SCREEN_BYTES_PER_COL);
}

void screen_set(uint8_t row, uint8_t col, bool r, bool g, bool b) {
  // TODO: This is terrible
  if(r) {
    screen[col][0] |= 1 << row;
  } else {
    screen[col][0] &= ~(1 << row);
  }

  if(g) {
    screen[col][1] |= 1 << row;
  } else {
    screen[col][1] &= ~(1 << row);
  }

  if(b) {
    screen[col][2] |= 1 << row;
  } else {
    screen[col][2] &= ~(1 << row);
  }
}

void screen_update_col(void) {
  PORTB |= (1 << SCREEN_LATCH_PIN);
  _delay_ms(1);
  PORTB &= ~(1 << SCREEN_LATCH_PIN);
}

void screen_update(void) {
  for(int col = 0; col < 8; col++) {
    for(int chan = 0; chan < 3; chan++) {
      spi_send(screen[col][chan]);
    }

    PORTE = col;

    screen_update_col();
  }

  // Now turn off the last column
  for(int chan = 0; chan < 3; chan++) {
    spi_send(0x00);
  }

  PORTE = 7;

  screen_update_col();
}

