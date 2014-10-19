#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

#define SPI_SCLK_PIN 1
#define SPI_MOSI_PIN 2
#define SPI_MISO_PIN 3

void spi_setup(void);
void spi_send(uint8_t b);

#endif
