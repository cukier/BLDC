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
long tempo = 65000;
short ctrl = FALSE;
short trigger = FALSE;

#INT_EXT
void isr_ext() {
	clear_interrupt(INT_EXT);
	tempo -= 1000;
	if (!tempo)
		tempo = 65000;
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
		if (!input(PIN_B1) && ctrl) {
			ctrl = FALSE;
			tempo -= 100;
		} else if (!ctrl)
			ctrl = TRUE;
		delay_us(tempo);
	}
	return 0;
}

