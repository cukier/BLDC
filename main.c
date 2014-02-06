/*
 * main.c
 *
 *  Created on: 03/02/2014
 *      Author: cuki
 */
#include<18F45K20.h>

#fuses HS

#use delay(clock=15MHz)
#use rs232(xmit=PIN_C6, baud=9600)

int cont = 1;
int cont2 = 0;
long tempo = 300;
short ctrl = FALSE;
short trigger = FALSE;

#INT_EXT
void isr_ext() {
	clear_interrupt(INT_EXT);
	tempo -= 10;
	if (!tempo)
		tempo = 300;
}

int main(void) {

	clear_interrupt(INT_EXT);
	enable_interrupts(INT_EXT);
	enable_interrupts(GLOBAL);

	while (TRUE) {
		cont <<= 1;
		if (cont == 8)
			cont = 1;
		output_d(cont);
		delay_ms(tempo);
	}
	return 0;
}

