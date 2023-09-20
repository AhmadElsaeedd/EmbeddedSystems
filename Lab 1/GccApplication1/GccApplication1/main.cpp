/*
 * GccApplication1.cpp
 *
 * Created: 9/20/2023 5:08:18 PM
 * Author : Ahmad ElSaeed
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void updateDisplay(uint8_t state) {
	// Update the 7-segment display segments (D0, D1, D2)
	// Here only 3 bits are used to control 3 segments
	PORTD = (PORTD & 0xF8) | (state & 0x07);
}

int main(void)
{
	// Initialize Port B for button input
	DDRB &= ~(1<<DDB3);
	DDRB &= ~(1 << DDB4);
	PORTB |= (1 << PORTB3);
	PORTB |= (1 << PORTB4);

	// Initialize Port D for 7-segment display output
	//DDRD = 0xFF;
	DDRD = 0b00000111;
	
	uint8_t placeA = 0;
	uint8_t placeB = 0;
	uint8_t placeC = 0;
	uint8_t state = 0;

	while (1)
	{
		// Check button states (active low due to pull-up resistors)
		if ((PINB & (1 << PORTB3))) {
			// Transition A fires: Move token to placeA
			placeA = 1;
		}
		if ((PINB & (1 << PORTB4))) {
			// Transition B fires: Move token to placeB
			placeB = 1;
		}

		// Update the state of the 7-segment display based on places
		state = 0;
		if (placeA) {
			// Turn on segment A (mapped to D0)
			state |= 0x01;
		}
		if (placeB) {
			// Turn on segment B (mapped to D1)
			state |= 0x02;
		}
		
		if(placeA && placeB){
			// Both buttons pressed: First turn on D0 and D1
			state |= 0x01 | 0x02;
			updateDisplay(state);
			_delay_ms(10000);  // Wait 10 seconds

			// Now turn off D0 and D1 and turn on D2
			state = 0x04;
		}
		
		updateDisplay(state);

		// Clear places for next iteration
		placeA = 0;
		placeB = 0;
		placeC = 0;

		_delay_ms(2000);  // Debounce delay
	}

	return 0;
}