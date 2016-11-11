#include "pins.h"
#include "led.h"
#include "uart.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initialize() 
{
	//Set up PORTB
	DDRB = 0x3D; 	//set bits 0, 2,3,4, and 5 on PORTB as output, clear all others
	PORTB |= ~0x3D;	//enable pull-up resisors for pins 1, 6-7
	PORTB &= ~0x3D;	//clears bits 0,2,3,4,5

	//Set up PORTC
	DDRC &= ~0x3F; 	//set bits 0-5 on PORTC as input
	PORTC &= ~0x38; //disable pull-up resistors for bits 3-5
	PORTC |= 0x07;	//enable pull-up resistors for bits 0-2

	//Set up PORTD
	DDRD = 0xFC;	//set bits 2-7 on PORTD as output, clear 0,1 
	PORTD |= 0x0F;	//enable pull-up resistors at pins 0,1,2,3
	PORTD &= ~0xF0;	//clear bits 4-7

	init_UART(UBRR_UART);

	//Task scheduler timer (Used for LED flashing and thermal monitoring)
	TCCR0A |= (1 << WGM01); // Configure timer 0 for CTC mode
	OCR0A = 255; // for LED; delay of ~114 ms after additional delay from the counter in the ISR
	TIMSK0 |= (1 << OCIE0A);  // for LED; Enable CTC interrupt (TIMER0_COMPA_vect)
	TCCR0B |= ((1 << CS02) | (1 << CS00)); // Start timer 0 at Fcpu/1024
	//The value of this timer is stored in TCNT0

	sei();	//global enable interrupts
}

int main() {

	initialize();
	set_flash_green();

	//startup_f1(); //Just during testing

	while(1){

	}

	return 0;
}

//Schedules the following processes: thermal monitoring, UART send, UART receive, led flashing
ISR(TIMER0_COMPA_vect)
{
	static uint8_t cycle_count = 1;

	

	cycle_count++;
}
