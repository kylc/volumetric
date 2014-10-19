#include <usart.h>

#include <avr/io.h>

void usart_init(void) {
  /* UCSR1A = _BV(U2X1); */
  UCSR1B = _BV(RXEN1) | _BV(TXEN1);
  UCSR1C = 3 << UCSZ10; // 8 bit, no parity, 1 stop bit
  UBRR1 = 12; // 38400 baud
}

void usart_send(char c) {
  while(!(UCSR1A & _BV(UDRE1)));
  UDR1 = c;
}

void usart_send_str(char *c) {
  while(*c) {
    usart_send(*c);
    c++;
  }
}

bool usart_available(void) {
  return UCSR1A & _BV(RXC1);
}

char usart_recv(void) {
  while(!(UCSR1A & _BV(RXC1)));
  return UDR1;
}

void usart_recv_block(uint8_t *data, int n) {
  for(int i = 0; i < n; i++) {
    *(data + i) = usart_recv();
  }
}

