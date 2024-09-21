#define F_CPU 16000000L
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "Text_LCD.h"
#include "avr/interrupt.h"

#define PRESCALER 1024
#define PULSE_MIN 900
#define PULSE_MAX 4700
volatile int count = 0;
volatile int button_count = 0;
volatile int last_button_press_time = 0;
int isOpen = 0;

void INIT_TIMER1(void) {
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR1B |= (1 << CS11);
	ICR1 = 40000;
	TCCR1A |= (1 << COM1A1);
	DDRB |= (1 << PB1);
}

ISR(TIMER0_COMPA_vect) {
	count++;
	if (isOpen && count >= 640) { // 문이 열린 후 5초 후 닫힘
		isOpen = 0;
		count = 0;
		LCD_clear();
		LCD_write_string("waiting...");
		OCR1A = PULSE_MIN;
	}
	if (isOpen && button_count > 0) {
		button_count++;
		if (button_count >= 192) { // 버튼을 누른 후 3초 후 닫힘
			isOpen = 0;
			button_count = 0;
			LCD_clear();
			LCD_write_string("waiting...");
			OCR1A = PULSE_MIN;
		}
	}
	TCNT0 = 0;
}

void Timer_init(void) {
	TCCR0B |= (1 << CS02) | (1 << CS00);   // 분주비 1024로 설정
	OCR0A = 128;
	TIMSK0 |= (1 << OCIE0A);
}

uint8_t measure_distance(void) {
	PORTC |= (1 << PC0);      // 트리거 핀 HIGH
	_delay_us(10);            // 10 마이크로초 대기
	PORTC &= ~(1 << PC0);     // 트리거 핀 LOW

	TCNT0 = 0;
	while (!(PINC & 0x02)) {
		if (TCNT0 > 250) return 255;
	}

	TCNT0 = 0;
	while (PINC & 0x02) {
		if (TCNT0 > 250) {
			TCNT0 = 0;
			break;
		}
	}

	double pulse_width = TCNT0 * PRESCALER * 1000000.0 / F_CPU;
	return pulse_width / 58;  // 센티미터 단위 거리 반환
}

void INIT_PORT(void) {
	DDRB &= ~(1 << PB3);  // 버튼 핀 입력으로 설정 (PB3)
	PORTB |= (1 << PB3);  // 풀업 저항 활성화
}

void INIT_PCINT0(void) {
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT3);
	sei();  // 전역 인터럽트 허용
}

ISR(PCINT0_vect) {
	if (isOpen) {
		button_count = 0;
		} else {
		isOpen = 1;
		count = 0;
		LCD_clear();
		LCD_write_string("Welcome!!");
		OCR1A = PULSE_MAX;
	}
}

int main(void) {
	INIT_TIMER1();
	uint8_t distance;
	
	DDRC |= 0x01;      // 트리거 핀 출력 설정
	DDRC &= 0xFD;      // 에코 핀 입력으로 설정
	
	Timer_init();      // 타이머 초기화
	sei();             // 전역 인터럽트 허용
	
	INIT_PORT();       // 버튼 포트 초기화
	INIT_PCINT0();     // 버튼 인터럽트 PCINT0 사용
	
	bool start = true;

	while (1) {
		if (start) {
			LCD_init();         // LCD 초기화
			LCD_write_string("Starting...");
			_delay_ms(2000);
			start = false;
			} else {
			distance = measure_distance();
			LCD_clear();
			
			if (distance < 15 && distance > 5) {
				isOpen = 1;
				count = 0; // 모터 On
				LCD_write_string("Welcome!!");
				OCR1A = PULSE_MAX;
				} else {
				if (!isOpen) {
					LCD_write_string("waiting...");
					OCR1A = PULSE_MIN;
				}
			}
		}
		_delay_ms(1000); // LCD 출력 Delay
	}
}
