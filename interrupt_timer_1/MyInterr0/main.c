#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h"

volatile int cnt = 0;

ISR(PCINT2_vect)
{
	if ((PIND & (1 << PD3)) == 0 || (PIND & (1 << PD4)) == 0 || (PIND & (1 << PD6)) == 0 || (PIND & (1 << PD7)) == 0)
	{
		cnt++;
		
		if (cnt % 3 == 0)
		{
			UART_printString("Current Counter Value: ");
			UART_printNumber(cnt);
			UART_printString("\n");
		}
	}
}

void INIT_PORT(void)
{
	DDRD = 0x00;
	PORTD = 0xFF;
}

void INIT_PCINT2(void)
{
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT22) | (1 << PCINT23);
	sei();
}

int main(void)
{
	UART_INIT();
	INIT_PORT();
	INIT_PCINT2();
	
	while (1)
	{
		
	}
}