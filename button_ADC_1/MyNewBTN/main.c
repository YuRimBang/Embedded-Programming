/*
 * MyUARTBTN.c
 *
 * Created: 2024-05-09 오후 5:21:00
 * Author : com
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#define bit_is_clear
#include "UART.h"

void INIT_PORT(void)
{
	DDRB = 0x00;
}

unsigned char button_pressed(void)
{
	if(bit_is_clear(PIND, PIND2))
	{
		_delay_ms(10);
		if(bit_is_clear(PIND, PIND2))
		{
			return 1;
		}
		return 0;
	}
}

int main(void) 
{
	UART_INIT();
	INIT_PORT();
	
	char state [6];

	state[4] = '\n';
	state[5] = '\0';
	
	while(1)  {
		button_pressed();
		for (int i=0; i<4; i++) 
		{
			if(PINB & (0x02 << i))
			{
				UART_printString('*');
				state[i] = 'o';
			}
			else
			state[i] = 'x';
			
		}
		UART_printString(state);
		_delay_ms(2000);
	}
}