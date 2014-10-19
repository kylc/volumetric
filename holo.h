#ifndef HOLODATA_H_
#define HOLODATA_H_

#include <stdint.h>
#include <string.h>

#define HOLO_COLS 8
#define HOLO_ANGS 36

extern uint8_t holodata[HOLO_COLS][HOLO_ANGS][3];

void holo_clear(void);
void holo_set(uint8_t r, uint8_t t, uint8_t z, uint8_t rgb);
uint8_t holo_get(uint8_t r, uint8_t t, uint8_t z);
void holo_generate_test(void);

#endif // HOLODATA_H_
