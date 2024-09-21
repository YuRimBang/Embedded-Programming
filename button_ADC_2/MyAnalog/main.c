/*
 * MyAnalog.c
 *
 * Created: 2024-05-07 오후 2:12:33
 * Author : com
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"

void ADC_INIT(unsigned char channel)
{
	ADMUX |= 0x40;
	
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADATE);
	
	ADMUX |= ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1 << ADSC);
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)));
	
	return ADC;
}

void int_to_string(int n, char *buffer)
{
	sprintf(buffer, "%04d", n); buffer[4] = '\0';
}

void PORT_INIT()
{
	DDRD = 0xFF;
}

int main(void)
{
	int value;
	uint8_t on_off;
	
	ADC_INIT(0);
	PORT_INIT();

    while (1) 
    {
		value = read_ADC() >> 7;

		on_off = 0;

		if (value == 0) 
		{
			on_off |= (0x01 << 0);
		}
		else if (value == 7) 
		{
			on_off |= (0x01 << 7);
		}

		PORTD = on_off;
    }
}

