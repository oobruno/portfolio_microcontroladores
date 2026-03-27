/*
 * main.c
 *
 * Created: 3/27/2026 3:54:14 PM
 *  Author: BruNo
 */ 
#define F_CPU 16000000

#include <xc.h>
#include "util/delay.h"


int main(void){
	DDRB = (1<<DDB0); //PINO B0 SAIDA
	UBRR0 = 103; //TAXA DE baud rate 9600
	UCSR0A = (0<<U2X0); //
	UCSR0B = (1<<RXEN0)|(0<<UCSZ02); // habilita receptor
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00) // MODO ASSINCRONO
	| (1<<UPM01)|(0<<UPM00) //HAB PARIDADE PAR
	| (0<<USBS0) // 1 BIT DE STOP
	| (1<<UCSZ01)|(1<<UCSZ00); //FRAMES DE 8 BITS
		
    while(1){
		while((UCSR0A & (1<<RXC0)) == 0); //ESPERAR 1 BYTE(MENSAGEM) CHEGAR	
		uint8_t tReceivedByte = UDR0;
		if(tReceivedByte == 200){
			PORTB |= (1<<PORTB0);	
    } else {
		PORTB = 0;
	}
}
	}