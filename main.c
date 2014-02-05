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

int a = FALSE, b = FALSE, c = FALSE;
int cont = 0;
long tempo = 300;

#INT_EXT
void isr_ext() {
	clear_interrupt(INT_EXT);
	tempo -= 10;
	if (tempo == 10)
		tempo = 300;
}

int main(void) {

	clear_interrupt(INT_EXT);
	enable_interrupts(INT_EXT);
	enable_interrupts(GLOBAL);

	while (TRUE) {
		if (cont == 5)
			cont = 0;

		a = (cont & 0b100) >> 2;
		b = (cont & 0b10) >> 1;
		c = cont & 1;

		output_bit(PIN_D0, (!(b & c)) & !a);
		output_bit(PIN_D1, b | (!c & a));
		output_bit(PIN_D2, (!a & c) | b);

		cont++;
		delay_ms(tempo);
	}

	return 0;
}

//int cont = 1;
//int cont2 = 0;
//long tempo = 300;
//short ctrl = FALSE;
//short trigger = FALSE;
//
//#INT_EXT
//void isr_ext() {
//	clear_interrupt(INT_EXT);
//	ctrl = TRUE;
//	cont <<= 1;
//	if (cont == 8 | !cont)
//		cont = 1;
//}
//
//int main(void) {
//
//	clear_interrupt(INT_EXT);
//	enable_interrupts(INT_EXT);
//	enable_interrupts(GLOBAL);
//
//	while (TRUE) {
//		if (ctrl) {
//			ctrl = FALSE;
//			output_d(cont);
//		}
//	}
//	return 0;
//}

//int cont = 1;
//int cont2 = 0;
//long tempo = 300;
//short ctrl = FALSE;
//short trigger = FALSE;
//
//#INT_EXT
//void isr_ext() {
//	clear_interrupt(INT_EXT);
//	tempo -= 10;
//	if (!tempo)
//		tempo = 300;
//}
//
//int main(void) {
//
//	clear_interrupt(INT_EXT);
//	enable_interrupts(INT_EXT);
//	enable_interrupts(GLOBAL);
//
//	while (TRUE) {
//		cont <<= 1;
//		if (cont == 8)
//			cont = 1;
//		output_d(cont);
//		delay_ms(tempo);
//	}
//	return 0;
//}

