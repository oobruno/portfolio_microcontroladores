/*
 * main.c
 *
 * Created: 3/27/2026 1:53:46 PM
 *  Author: Aluno
 */ 
#define F_CPU 16000000

#include <xc.h>
#include "util/delay.h"

uint8_t gMessage[3] = {200,100,50};
	
void UART_sendMessage(uint8_t * pData, int pSize){
	uint8_t * tMsgPtr = pData;
	uint8_t tChecksum = 0;
	int i;
	for(i=0;i<pSize;i++){
		while((UCSR0A & (1 <<UDRE0)) == 0);
		uint8_t tMessageByte = *tMsgPtr;
		tChecksum += tMessageByte;
		UDR0 = tMessageByte;
		tMsgPtr++;
	}
	while((UCSR0A & (1<<UDRE0)) ==0);
	UDR0 = tChecksum;
}
// código completo para envio de mensagem!.

int main(void){
	UBRR0 = 103; //TAXA DE baud rate 9600
	UCSR0A = (0<<U2X0); //
	UCSR0B = (1<<TXEN0)|(0<<UCSZ02); // habilita transmissor
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00) // MODO ASSINCRONO
			| (1<<UPM01)|(0<<UPM00) //HAB PARIDADE PAR
			| (0<<USBS0) // 1 BIT DE STOP
			| (1<<UCSZ01)|(1<<UCSZ00); //FRAMES DE 8 BITS
			
    while(1){
		UART_sendMessage(gMessage, 3);
	_delay_ms(10);
    }
}