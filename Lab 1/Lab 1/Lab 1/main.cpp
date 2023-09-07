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
	//set PortB3 to input
	DDRB &= ~(1<<DDB3);
	//set PortB4 to input
	DDRB &= ~(1 << DDB4);
	//set all of PortD to output to control the 7-segment
	DDRD = 0xFF;
	
	//enabling the pull-up resistor to PB3 and PB4
	//this is done because we're connecting a button to those pins
	PORTB |= (1 << PORTB3);
	PORTB |= (1 << PORTB4);
    
	//Define the array that maps that contains the numbers
	//A = 8th bit
	//B = 7th bit
	//C = 6th bit
	//D = 5th bit
	//E = 4th bit
	//F = 5th bit
	//G = 6th bit
	uint8_t seven_segment_digits[10]={
	0b11111100,//0
	0b01100000,//1
	0b11011001,//2
	0b11110001,//3
	0b01001100,//4
	};
    while (1) 
    {
	
    }
}

