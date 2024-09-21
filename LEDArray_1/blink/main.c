#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;

	char patterns[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	while(1)
	{
		for(int i = 0; i < 8; i++)
		{
			 int a = i, b = (i + 1) % 8, c = (i + 2) % 8;
			
			char p1 = patterns[a];
			char p2 = patterns[b];
			char p3 = patterns[c];
			
			 PORTD = p1 | p2 | p3; 
			 _delay_ms(1000);
		}
	}

	return 1;
}

