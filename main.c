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

long tempo = 500;
int cont = 0;
short ctrl = TRUE;

#INT_EXT
void ext_isr() {
	delay_ms(100);
	clear_interrupt(INT_EXT);
	tempo -= 50;
	if (tempo <= 50)
		tempo = 500;
	ctrl = TRUE;
}

int muda_estado(int entrada) {
	switch (entrada) {
	case 1:
		return A;
	case 2:
		return B;
	case 3:
		return C;
	case 4:
		return D;
	case 5:
		return E;
	case 6:
		return F;
	}
}

int main(void) {

	output_c(0);

	enable_interrupts(INT_EXT_H2L | GLOBAL);

	printf("\fHello");

	while (TRUE) {
		output_c(muda_estado(++cont));
		if (cont == 6)
			cont = 0;
		delay_ms(tempo);
		if (ctrl) {
			ctrl = FALSE;
			printf("\f%lu", tempo);
		}
	}
	return 0;
}
