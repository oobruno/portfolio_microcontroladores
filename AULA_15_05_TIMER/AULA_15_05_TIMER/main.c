/*
 * main.c
 *
 * Created: 5/15/2026 2:50:12 PM
 *  Author: Aluno
 */ 
#define F_CPU 8000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util\delay.h"

//ISR(TIMER0_COMPA_vect){
	//PORTB |= (1<<PORTB0); //SETA PB0
//}
//ISR(TIMER0_COMPB_vect){
	//PORTB &= ~(1<<PORTB0); //ZERA PB0
//}
uint8_t gPWMa = 0;
uint8_t gPWMb = 100;
int main(void){
	//DDRB = (1<<PORTB0); //DEFINE B0 COMO SAIDA
	DDRD = (1<<DDD6)|(1<<DDD5); //DEFINE D6 COMO SAIDA
	TIMSK0 = (1<<OCIE0B)|(1<<OCIE0A);//HAB INTERRUPCAO DE A E B DE COMPARACAO DE SAIDA
    TCCR0A = (1<<WGM00)|(1<<WGM01)|(1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0); //MODO FAST PWM COM TOP=0XFF, TOGGLE DO OC0A
	TCCR0B = (1<<WGM02)|(1<<CS01)|(0<<CS02)|(0<<CS00); //PRESCALER DE 8MGHZ
	//OCR0A = 63; //CONTAGEM ATE 63us (ASSUMINDO Q O CLK DO TIMER É DE 1MHZ)
	//OCR0B = 85; //TRANSICAO DA ONDA EM 33%
	//sei(); //hab interrupçao globais
	while(1){
		OCR0A = gPWMa;
		OCR0B = gPWMb;
		_delay_ms(100);
		gPWMa += 2;
		gPWMb--;
		 
    }
}