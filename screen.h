#ifndef SCREEN_H_
#define SCREEN_H_

#include <stdbool.h>
#include <stdint.h>

#define SCREEN_COLS          8
#define SCREEN_BYTES_PER_COL 3

#define SCREEN_LATCH_PIN 7

extern uint8_t screen[SCREEN_COLS][SCREEN_BYTES_PER_COL];

void screen_clear(void);
void screen_set(uint8_t row, uint8_t col, uint8_t rgb);
void screen_update_col(void);
void screen_update(void);

#endif
