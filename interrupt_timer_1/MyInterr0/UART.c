#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void UART_INIT(void) {
	UCSR0A |= _BV(U2X0);   // 2배속 모드
	
	UBRR0H = 0x00;         // 통신속도(보율) 설정
	UBRR0L = 207;
	
	UCSR0C |= 0x06;
	
	UCSR0B |= _BV(RXEN0);   // 송수신 가능
	UCSR0B |= _BV(TXEN0);
}

unsigned char UART_receive(void) {
	while ( !(UCSR0A & (1<<RXC0)) );   // 데이터 수신 대기
	return UDR0;
}

void UART_transmit(unsigned char data) {
	while ( !(UCSR0A & (1<<UDRE0)) );   // 송신 가능 대기
	UDR0 = data;                  // 데이터 전송
}

void UART_printString(char *str) {
	for (int i = 0; str[i]; i++)
	UART_transmit(str[i]);
}

void UART_printNumber(uint32_t num) {
	int i;
	char buf[10];
	
	for (i=0;num > 0; ++i) {
		buf[i] = num % 10 + '0';
		num /= 10;
	}
	
	for (int j = i - 1; j >=0; --j)
	UART_transmit(buf[j]);
}