#ifndef TRANSMIT_H_
#define TRANSMIT_H_

#include <holo.h>

// struct frame_t {
//   uint8_t board_id;
//   uint8_t data[HOLO_COLS][HOLO_ANGS][3];
// };

void transmit_init(void);
void transmit_read_frame(uint8_t *id, uint8_t data[HOLO_COLS][HOLO_ANGS][3]);

#endif
