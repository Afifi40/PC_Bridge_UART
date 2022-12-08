/*
 * UART.h
 *
 * Created: 10/23/2022 2:13:31 PM
 *  Author: Afifi
 */ 


#ifndef UART_H_
#define UART_H_

#include "utilites.h"
#include "EEPROM.h" //NOT ADVICABLE, TRY MOVING ISR to main instead
/*GUI Commands*/
typedef enum {
	RESET=0, 
	READ=1, 
	WRITE=2
}commands;

typedef enum {
	STOP=0,
	RAM=1,
	ROM=2
}memory;

/*Configurable Macros*/
#define ENABLE_INTERRUPT 1


/*Macros*/
#define _MEM(address) (*(volatile uint8_t *)(address))



/* Functions */
void UART_init(unsigned long baud);
void UART_Transmit_Char(unsigned char data );
unsigned char UART_Receive_Char();
void UART_Receive_Command();
void UART_Transmit_Number(uint8_t number);
void reset_UART();
//void UART_IsDataAvaiable(void);
uint8_t UART_IsTxComplete(void);
uint8_t UART_IsRxComplete(void);



#endif /* UART_H_ */