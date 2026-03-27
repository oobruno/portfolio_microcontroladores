/*
 * main.c
 *
 * Created: 3/27/2026 3:54:14 PM
 *  Author: BruNo
 */ 
#define F_CPU 16000000

#include <xc.h>
#include "util/delay.h"

uint8_t gReceivedBuffer [4];
void UART_receivedMessage(uint8_t * pBuffer, int pSize){
	uint8_t tReceivedByte = UDR0;
	uint8_t * tBufferPtr = pBuffer;
	for(int i=0;i<pSize;i++){
		while((UCSR0A & (1<<RXC0)) == 0)//ESPERA MSG CHEGAR

		*tBufferPtr = tReceivedByte;
		tBufferPtr++;
	}
}
void UART_parsedMessage(uint8_t *pMessage){
	//calcula checksum
	uint8_t tChecksum = 0;
	for(int i=0;i<3;i++){
		tChecksum += pMessage[i];
	}
	if(pMessage[3] == tChecksum){
		//checksum correto
		PORTB |= (1<<PORTB0);
	} else {
		//erro de checksum
		PORTB = (1<<PORTB2);
	}

}
int main(void){
	DDRB = (1<<DDB0)|(1<<DDB2); //PINO B0 SAIDA
	UBRR0 = 103; //TAXA DE baud rate 9600
	UCSR0A = (0<<U2X0); //
	UCSR0B = (1<<RXEN0)|(0<<UCSZ02); // habilita receptor
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00) // MODO ASSINCRONO
	| (1<<UPM01)|(0<<UPM00) //HAB PARIDADE PAR
	| (0<<USBS0) // 1 BIT DE STOP
	| (1<<UCSZ01)|(1<<UCSZ00); //FRAMES DE 8 BITS
		
    while(1){
		PORTB = 0;
		UART_parsedMessage(gReceivedBuffer);
		UART_receivedMessage(gReceivedBuffer, 4);
		_delay_ms(10);
	}
}