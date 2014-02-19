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

int saida = 1;
long reg_timer0 = 15535;
short ctrl = TRUE;

#INT_EXT
void ext_isr() {
	delay_ms(100);
	clear_interrupt(INT_EXT);
	reg_timer0 += 2500;
	if (reg_timer0 == 60000)
		reg_timer0 = 15535;
	ctrl = TRUE;
}

#INT_TIMER0
void timer_isr() {
	clear_interrupt(INT_TIMER0);
	set_timer0(reg_timer0);
	saida <<= 1;
	if (saida == 8)
		saida = 1;
	output_c(saida);
}

int main(void) {

	output_c(0);

	clear_interrupt(INT_EXT);
	clear_interrupt(INT_TIMER0);
	set_timer0(reg_timer0);
	setup_timer_0(T0_DIV_16 | T0_INTERNAL);
	enable_interrupts(INT_EXT | INT_TIMER0 | GLOBAL);

	printf("\fHello");

	while (TRUE) {
		if (ctrl) {
			ctrl = FALSE;
			printf("%c", 12);
			delay_ms(10);
			printf("t: %.3f", (65535 - reg_timer0) * 0.000002);
		}
	}
	return 0;
}
