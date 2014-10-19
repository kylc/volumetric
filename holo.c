#include <holo.h>

uint8_t holodata[HOLO_COLS][HOLO_ANGS][3];

void holo_clear(void)
{
  memset(holodata, 0, sizeof(holodata[0][0][0]) * HOLO_COLS * HOLO_ANGS * 3);
}

void holo_set(uint8_t r, uint8_t t, uint8_t z, uint8_t rgb)
{
  int i;
  for (i=0; i<3; i++) {
    holodata[r][t][i] &= ~(1<<z);
    holodata[r][t][i] |= (1 & (rgb>>i)) << z;
  }
}

uint8_t holo_get(uint8_t r, uint8_t t, uint8_t z)
{
  return ((1 & (holodata[r][t][0]>>z)) << 0) +
    ((1 & (holodata[r][t][1]>>z)) << 1) +
    ((1 & (holodata[r][t][2]>>z)) << 2);
}

void holo_generate_test(void)
{
  int r, t, z;

  for (t=0; t<HOLO_ANGS; t++) {
    float sin_pos = sin(((float) t) / HOLO_ANGS * 2 * 3.14159);
    z = round((sin_pos*3.5)+3.5);
    holo_set(0, t, z, 0b100);
    holo_set(2, t, z, 0b101);
    holo_set(4, t, z, 0b001);
    holo_set(6, t, z, 0b011);
  }
}

