#include <avr/io.h>
#include <avr/interrupt.h>

volatile int pattern_index = 0;
volatile int pattern_counter = 0;

const uint8_t pattern[] = {0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x0e, 0x1c, 0x38, 0x70};

volatile uint8_t patternIndex = 0;
volatile int count = 0;

ISR(TIMER1_COMPA_vect) {
	count++;
	TCNT1 = 0;
}

int main() {
	DDRD = 0xff;
	PORTD = 0x00;

	TCCR1B = (1 << CS12) | (1 << CS10);
	OCR1A = 128;

	TIMSK1 |= (1 << OCIE1A);

	sei();
	
	while(1)
	{
		if(count == 64)
		{
			count = 0;
			patternIndex = (patternIndex) % sizeof(pattern);
			PORTD = pattern[patternIndex++];
		}
	}
	
	return 0;
}
