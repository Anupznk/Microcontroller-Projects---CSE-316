/*
 * LED_matrix.c
 *
 * Created: 6/17/2022 6:16:41 PM
 * Author : Anup
 */ 

#include <avr/io.h>
#include <stdio.h>
#define F_CPU 1000000
#include <util/delay.h>
#define F_CPU 1000000


void renderSmiley(int shift){
	// shift = 0 -> no shift
	// shift = 1 -> left shift
	// shift = 2 -> right shift
	// shift = 3 -> left down
	// shift = 4 -> right up

	unsigned char delayMS = 6;
	
	// make your image here and remember to reset it properly
	unsigned char rowSetup [8] = {0, 0b00000010, 0b00000100, 0, 0b00010000, 0b00100000, 0, 0};
	unsigned char colSetup [8] = {0xFF, 0x99, 0x99, 0xFF, 0xBD, 0xC3, 0xFF, 0xFF};
	// int shiftDelayMS = 100;
	unsigned char shiftCou = 0;
	
	unsigned char mask = 0b11111111;
	
	while(1){
		// PORTC te row connection, so, on thakle oi row on hobe
		// PORTD te jegula off, sei col gula jolbe
		
		for(int i = 0; i < 7; i++){
			PORTC = rowSetup[i];
			PORTD = colSetup[i];
			_delay_ms(delayMS);
		}
			
		shiftCou++;
		if(shift == 1){
			mask = mask << 1;
			mask = ~mask;
			for(int i = 0; i < 7; i++){
				colSetup[i] = colSetup[i] << 1;	// here by left shifting, the lsb is becoming 0, thus turning on
				colSetup[i] = colSetup[i] | mask;
			}

			mask = ~mask;
			
			if(shiftCou == 10){
				// reset
				shiftCou = 0;
				mask = 0b11111111;
				colSetup [0] = 0xFF;
				colSetup [1] = 0x99;
				colSetup [2] = 0x99;
				colSetup [3] = 0xFF;
				colSetup [4] = 0xBD;
				colSetup [5] = 0xC3;
				colSetup [6] = 0xFF;
				colSetup [7] = 0xFF;
			}
			_delay_ms(delayMS);
		}
		if(shift == 2){
			
			mask = mask >> 1;
			mask = ~mask;
			for(int i = 0; i < 7; i++){
				colSetup[i] = colSetup[i] >> 1;	// here by left shifting, the msb is becoming 0, thus turning on
				colSetup[i] = colSetup[i] | mask;
			}
			
			mask = ~mask;
			if(shiftCou == 10){
				// reset
				shiftCou = 0;
				mask = 0b11111111;
				colSetup [0] = 0xFF;
				colSetup [1] = 0x99;
				colSetup [2] = 0x99;
				colSetup [3] = 0xFF;
				colSetup [4] = 0xBD;
				colSetup [5] = 0xC3;
				colSetup [6] = 0xFF;
				colSetup [7] = 0xFF;
			}
			_delay_ms(delayMS);
		}
		
		if(shift == 3){
			// shift down image
			for(int i = 0; i < 7; i++){
				rowSetup[i] = rowSetup[i] << 1;
			}
			
			if(shiftCou == 10){
				// reset
				shiftCou = 0;
				rowSetup [0] = 0;
				rowSetup [1] = 0b00000010;
				rowSetup [2] = 0b00000100;
				rowSetup [3] = 0;
				rowSetup [4] = 0b00010000;
				rowSetup [5] = 0b00100000;
				rowSetup [6] = 0;
				rowSetup [7] = 0;
			}
			_delay_ms(delayMS);
		}
		
		if(shift == 4){
			// shift up image
			for(int i = 0; i < 7; i++){
				rowSetup[i] = rowSetup[i] >> 1;
			}
			
			if(shiftCou == 10){
				// reset
				shiftCou = 0;
				rowSetup [0] = 0;
				rowSetup [1] = 0b00000010;
				rowSetup [2] = 0b00000100;
				rowSetup [3] = 0;
				rowSetup [4] = 0b00010000;
				rowSetup [5] = 0b00100000;
				rowSetup [6] = 0;
				rowSetup [7] = 0;
			}
			_delay_ms(delayMS);
		}
	}
}

int main(void)
{
    DDRD = 0xFF;
	DDRC = 0xFF;
	renderSmiley(4);
    while (1) 
    {
		
    }
}

