/*
 * Lab2.cpp
 *
 * Created: 10/8/2023 3:48:00 PM
 * Author : Ahmad ElSaeed
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t count = 0;
uint8_t lastEncoderAState = 0;
uint8_t lastEncoderSWState = 1; // Assuming it starts unpressed because of the pull-up


//7 segment display
uint8_t seven_segment_digits[10] = {
	0b00111111,
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00000111,
	0b01111111,
	0b01101111
};

//setup pins and interrupts
void setup() {
	cli();
	//setup pins for rotary encoder
	DDRB &= ~(1 << DDB2);  //port b2 as input
	DDRB &= ~(1 << DDB3);  //port b3 as input
	DDRB &= ~(1 << DDB4); //port b4 as input

	//enabling pull up resistors
	PORTB |= (1 << PORTB2);
	PORTB |= (1 << PORTB3);
	PORTB |= (1 << PORTB4);

	//set up interrupts for rotary encoder
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT2);
	PCMSK0 |= (1 << PCINT3);
	PCMSK0 |= (1 << PCINT4);

	//initialize 7-segment display pins as output and set low
	DDRD = 0xFF;

	//enable global interrupts
	sei();
}

// Update display function
void updateDisplay() {
	PORTD = seven_segment_digits[count];
}

// Interrupt Service Routine
ISR(PCINT0_vect) {
	uint8_t A = (PINB >> DDB2) & 1;
	uint8_t B = (PINB >> DDB3) & 1;
	uint8_t SW = (PINB >> DDB4) & 1;
	bool rotation_detected = false;
	
	if (lastEncoderAState != A) {
		lastEncoderAState = A;
		if (A != B) {
			count = (count == 9) ? 0 : count + 1;
			} else {
			count = (count == 0) ? 9 : count - 1;
		}
		updateDisplay();
		rotation_detected =true;
	}

	if (lastEncoderSWState != SW && !rotation_detected) {
		if (SW == 0) {
			count = 0;
			updateDisplay();
		}
		lastEncoderSWState = SW;
	}
}

int main() {
	setup();

	// Keep the program running
	while (1) {
	 }
	return 0;
}