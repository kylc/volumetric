#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include <stdbool.h>

void usart_init(void);
void usart_send(char c);
void usart_send_str(char *c);
bool usart_available(void);
char usart_recv(void);
void usart_recv_block(uint8_t *data, int n);

#endif
