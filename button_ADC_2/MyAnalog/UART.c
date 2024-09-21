/*
 * UART.c
 *
 * Created: 2024-04-17 오전 10:23:56
 *  Author: com
 */ 
#include "UART.h"

void UART_INIT(void)
{
	UCSR0A |= _BV(U2X0);  // Line A: setting the U2X0 bit in UCSR0A
	
	UBRR0H = 0x00;         // Line B: setting the high byte of the baud rate register
	UBRR0L = 207;          // Line C: setting the low byte of the baud rate register

	UCSR0C |= 0x06;        // Line D: setting frame format

	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);  // Line E: enabling RX and TX
}

unsigned char UART_receive(void)
{
	while (!(UCSR0A & (1<<RXC0)));  // 데이터 수신을 기다림
	return UDR0;  // 수신된 데이터 반환
}


void UART_transmit(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0)));  // 송신 버퍼가 비어있을 때까지 기다림
	UDR0 = data;  // 데이터를 송신 버퍼에 저장, 데이터 송신
}

void UART_printString(char *str)
{
	for(int i = 0; str[i]; i++)
	UART_transmit(str[i]);
}

void UART_printNumber(uint32_t num)
{
	int i;
	char buf[10];
	
	for(i = 0; num>0; ++i){
		buf[i] = num % 10 +'0';
		num /= 10;
	}
	
	for(int j = i - 1; j >=0; --j)
	UART_transmit(buf[j]);
}