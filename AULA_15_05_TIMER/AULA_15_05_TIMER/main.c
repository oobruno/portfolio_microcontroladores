/*
 * main.c
 *
 * Created: 5/15/2026 2:50:12 PM
 *  Author: Aluno
 */ 
#define F_CPU 8000000
#include <xc.h>
#include "avr/interrupt.h"

ISR(TIMER0_COMPA_vect){
	PORTB |= (1<<PORTB0); //SETA PB0
}
ISR(TIMER0_COMPB_vect){
	PORTB &= ~(1<<PORTB0); //ZERA PB0
}

int main(void){
	DDRB = (1<<PORTB0); //DEFINE B0 COMO SAIDA
	TIMSK0 = (1<<OCIE0B)|(1<<OCIE0A);//HAB INTERRUPCAO DE A E B DE COMPARACAO DE SAIDA
    TCCR0A = (0<<WGM00)|(1<<WGM01); //MODO CTC
	TCCR0B = (0<<WGM02)|(1<<CS01)|(0<<CS02)|(0<<CS00); //PRESCALER DE 8MGHZ
	OCR0A = 249; //CONTAGEM ATE 250us (ASSUMINDO Q O CLK DO TIMER É DE 1MHZ)
	OCR0B = 99; //TRANSICAO DA ONDA EM 60%
	sei(); //hab interrupçao globais
	
	
	while(1){
		
		 
    }
}