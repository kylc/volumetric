#include <spi.h>

#include <avr/io.h>

void spi_setup(void) {
  // Enable SPI master mode
  SPCR = (1 << SPE) | (1 << MSTR) | (1 < SPR0);
}

void spi_send(uint8_t b) {
  SPDR = b;

  while(!(SPSR & (1 << SPIF)));
}

