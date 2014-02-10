/*
 * main.c
 *
 *  Created on: 03/02/2014
 *      Author: cuki
 */
#include<18F45K20.h>

#fuses H4

#use delay(crystal=15MHz, clock=60MHz)
#use rs232(xmit=PIN_C6, baud=9600)

int cont = 1;
int cont2 = 0;
long tempo = 35000;
long tempoAux = 0;
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

	setup_ccp1(CCP_PWM);
	setup_timer_2(T2_DIV_BY_1, 250, 1);
	set_pwm1_duty(127);

	while (TRUE) {
		cont <<= 1;
		if (cont == 8)
			cont = 1;
		output_d(cont);
		if (tempo != 20000) {
			if (!input(PIN_B1) && ctrl) {
				ctrl = FALSE;
				if (tempo > 30000)
					tempo -= 1000;
				else
					tempo -= 100;
			} else if (!ctrl)
				ctrl = TRUE;
		}
		if (tempoAux != tempo) {
			tempoAux = tempo;
			printf("\f%lu", tempo);
		}
		delay_us(tempo);
	}

	return 0;
}

