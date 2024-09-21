/*
 * blink.c
 *
 * Created: 2024-03-27 오전 10:26:10
 * Author : com
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0x20;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0x00;
		_delay_ms(100); //끄기
		PORTB = 0x20;
		_delay_ms(100); //켜기
		
		PORTB = 0x00;
		_delay_ms(1000); //끄기
		PORTB = 0x20;
		_delay_ms(1000); //켜기
	}
	
	return 1;
}

