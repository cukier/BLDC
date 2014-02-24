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
#define A 33
#define B 17
#define C 20
#define D 12
#define E 10
#define F 34

long tempo = 65000;
int cont = 1;
short ctrl = TRUE;
short on_off = TRUE;

#INT_EXT
void ext_isr() {
	delay_ms(100);
	clear_interrupt(INT_EXT);
	tempo -= 1000;
	if (tempo == 1000)
		tempo = 65000;
	ctrl = TRUE;
}

int main(void) {

	output_c(0);

	enable_interrupts(INT_EXT_H2L | GLOBAL);

	printf("\fHello");

	while (TRUE) {
		cont <<= 1;
		if (cont == 0b1000)
			cont = 1;
		output_c(cont);
		delay_us(tempo);
		if (ctrl) {
			ctrl = FALSE;
			printf("%lu\r\n", tempo);
		}
	}
	return 0;
}
