/*
 * main.c
 *
 *  Created on: 03/02/2014
 *      Author: cuki
 */
#include<18F452.h>

#fuses H4

#use delay(crystal=8MHz, clock=32MHz)
#use rs232(xmit=PIN_C6, baud=9600, parity=N, bits=8, stop=1)

#define bto PIN_B0
#define tempo0 3035

int tempo = 500, cont = 1, estado_timer0 = 0;
short print = TRUE, on_off = TRUE, trigger;

#INT_EXT
void ext_isr() {
	delay_ms(100);
	clear_interrupt(INT_EXT);
	switch (estado_timer0++) {
	case 0:
		setup_timer_0(T0_INTERNAL | T0_DIV_64);
		break;
	case 1:
		setup_timer_0(T0_INTERNAL | T0_DIV_32);
		break;
	case 2:
		setup_timer_0(T0_INTERNAL | T0_DIV_16);
		break;
	case 3:
		setup_timer_0(T0_INTERNAL | T0_DIV_8);
		estado_timer0 = 0;
		break;
	default:
		estado_timer0 = 0;
	}
}

#INT_EXT2
void ext2_isr() {
	clear_interrupt(INT_EXT2);
	delay_ms(100);
	on_off = !on_off;
	trigger = TRUE;
}

#INT_TIMER0
void isr_timer0() {
	clear_interrupt(INT_TIMER0);
	cont <<= 1;
	if (cont == 0b1000)
		cont = 1;
	output_c(cont);
}

int main(void) {

	output_c(0);

	setup_timer_0(T0_INTERNAL | T0_DIV_128);
	set_timer0(tempo0);
	clear_interrupt(INT_TIMER0);

	enable_interrupts(INT_EXT_H2L);
	enable_interrupts(INT_EXT2_H2L);
	enable_interrupts(INT_TIMER0);
	enable_interrupts(GLOBAL);

	while (TRUE) {
		if (on_off) {
			if (trigger) {
				trigger = FALSE;
				setup_timer_0(T0_INTERNAL | T0_DIV_128);
				set_timer0(tempo0);
				clear_interrupt(INT_TIMER0);
				enable_interrupts(INT_TIMER0);
				estado_timer0 = 0;
			}
		} else {
			if (trigger) {
				trigger = FALSE;
				clear_interrupt(INT_TIMER0);
				disable_interrupts(INT_TIMER0);
				setup_timer_0(T0_OFF);
				printf("\fDesligado");
				output_c(0);
			}
		}
	}
	return 0;
}
