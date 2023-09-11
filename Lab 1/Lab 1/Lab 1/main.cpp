/*
 * Lab 1.cpp
 *
 * Created: 9/7/2023 4:18:28 PM
 * Author : Ahmad ElSaeed
 */ 

#include <avr/io.h>
#include <stdint.h>

int main(void)
{
	//set PortB2 to input
	DDRB &= ~(1<<DDB2);
	//set PortB3 to input
	DDRB &= ~(1 << DDB3);
	//set all of PortD to output to control the 7-segment
	DDRD = 0xFF;
	
	//enabling the pull-up resistor to PB2 and PB3
	//this is done because we're connecting a button to those pins
	PORTB |= (1 << PORTB2);
	PORTB |= (1 << PORTB3);
    
	//Define the array that maps that contains the numbers
	//A = 8th bit
	//B = 7th bit
	//C = 6th bit
	//D = 5th bit
	//E = 4th bit
	//F = 3rd bit
	//G = 2nd bit
	//1st bit is always 0
	uint8_t seven_segment_digits[10]={
	//0b11111111,//test	
	0b11111100,//0
	0b01100000,//1
	0b11011010,//2
	0b11110010,//3
	0b01001100,//4
	0b10110110,//5
	0b10111110,//6
	0b11100000,//7
	0b11111110,//8
	0b11110110,//9
	};
	
	uint8_t current_digit = 0;
    while (1) 
    {
		//increment button is PB3
		//if (!(PINB & (1 << PINB2))) //button is active low because of pull-up
		//{
			//current_digit = (current_digit + 1) % 10; //after 9 is 0
			PORTD = seven_segment_digits[current_digit]; //change the display
		//}
		
		//decrement button is PB4
		//if (!(PINB & (1 << PINB3))){//button is active low because of pull-up
			//if(current_digit == 0) current_digit = 9;
			//else current_digit--;
			
			//PORTD = seven_segment_digits[current_digit]; //change the display
		//}
    }
}

