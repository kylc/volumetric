#ifndef USART_H_
#define USART_H_

void usart_init(void);
void usart_send(char c);
void usart_send_str(char *c);
char usart_recv(void);

#endif
