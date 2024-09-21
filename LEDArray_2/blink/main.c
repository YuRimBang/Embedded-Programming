#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;

	while(1)
	{
		for(int i = 7; i >= 0; i--)
		{
			int a = i, b = (i - 1) % 8, c = (i - 2) % 8;
			
			if(b < 0){b=b+8;}
			if(c < 0){c=c+8;}
			
			char p1 = 0x01 << a;
			char p2 = 0x01 << b;
			char p3 = 0x01 << c;
			
			PORTD = p1 | p2 | p3;
			_delay_ms(1000);
		}
	}

	return 1;
}

