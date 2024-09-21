/*
 * UART.h
 *
 * Created: 2024-04-17 오전 10:24:25
 *  Author: com
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void UART_INIT(void);
unsigned char UART_receive(void);
void UART_transmit(unsigned char data);
void UART_printString(char *str);
void UART_printNumber(uint32_t num);

#endif /* UART_H_ */