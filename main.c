/*
 * main.c
 *
 *  Created on: 03/02/2014
 *      Author: cuki
 */
#include<18F452.h>

#fuses H4

#use delay(crystal=8MHz, clock=32MHz)
#use rs232(xmit=PIN_C6, baud=9600)

#define bto PIN_B0
//#define A 17
//#define B 34
//#define C 12

int cont = 100;
short ctrl = FALSE;

enum estadoTypes {
	A, B, C
} estados;

#INT_EXT
void ext_isr() {
	clear_interrupt(INT_EXT);
	cont -= 10;
	if (!cont)
		cont = 100;
	ctrl = TRUE;
}

int main(void) {

	output_d(0);

	clear_interrupt(INT_EXT);
	enable_interrupts(INT_EXT | GLOBAL);

	printf("Hello");

	while (TRUE) {

		delay_ms(cont);
		switch (estados++) {
		case A:
			output_d(17);
			break;
		case B:
			output_d(34);
			break;
		case C:
			output_d(12);
			estados = A;
			break;
		default:
		}
		if (ctrl) {
			ctrl = FALSE;
			printf("\f%d", cont);
		}
	}
	return 0;
}
