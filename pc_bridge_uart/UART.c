#include "UART.h"


void UART_init(unsigned long baud)
{
	//SET TRANSMIT BIT
	SET_BIT(DDRD,1);///SET UART TRANSMIT PIN as output
	
	//Set Baud Rate
	unsigned short UBRR;
	UBRR = (F_CPU / (16*baud)) - 1;
	UBRRH = (uint8_t)(UBRR >> 8);
	UBRRL = (uint8_t) UBRR;
	
	//Enable Sender and Receiver
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	
	//Enable Interrupts for both receiver and sender
	#if ENABLE_INTERRUPT == 1
		UCSRB |= (1<<TXCIE) | (1<<RXCIE);
		sei();
	#endif
}
void UART_Transmit_Char( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}
unsigned char UART_Receive_Char( void )
{
	uint8_t rd;//received data
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	
	/*get received data from buffer*/
	rd = UDR;
	
	/* check if the received data contains the start of a command*/
	#if ENABLE_INTERRUPT == 0
	if (rd == '@')
		UART_Receive_Command();
	#endif
	
	/* Get and return received data from buffer */
	return rd;
}




/*
void UART_Receive_Command(){//@ HAS BEEN RECEIVED
	uint8_t operation, val;
	volatile uint8_t *address ; //AVOID USING WILD POINTERS!!
	
	//Receive Command Data
	operation = UART_Receive_Char();
	UART_Receive_Char(); //ignore space
	address   =  (uint8_t*) UART_Receive_Char();   
	
	if(UART_Receive_Char() == ';')//Start Processing Command
	{
		switch (operation){
			case RESET:
				//Clear Buffer
				break;
			case READ:
				UART_Transmit_Char(_MEM(address));
				break;
			case WRITE:
				UART_Receive_Char(); //ignore space
				val = UART_Receive_Char();
				_MEM(address) = val;
				break;
			default:	//Wrong Command Number
			return;
		}
	}

}
*/
/*Doesn't work properly*/
/*
void UART_Transmit_Number(uint8_t number){
	char *buffer;
	sprintf(buffer,"%d",number);

	for(int i=0; i<3 || buffer[i]!='\0'; i++)
		UART_Transmit_Char(buffer[i]);
}
*/
uint8_t UART_IsTxComplete(void)
	{
		return GET_BIT(UCSRA,TXC);
	}
	
#if ENABLE_INTERRUPT == 1
	static volatile uint8_t  rx_buffer[4];
	static volatile uint16_t rx_len=4;
	static volatile uint16_t rx_cnt=4;
	static volatile uint8_t *r ;
	ISR(USART_RXC_vect)
	{
		cli();
		uint8_t rx_data, readFrom = STOP;
		
		/* Read rx_data. */
		rx_data = UDR;
		if(rx_data == '@'){
			rx_cnt=0;
			readFrom = RAM;
		}
		else if(rx_data == '<'){
			rx_cnt=0;
			readFrom = ROM;
		}
		else if((rx_cnt < rx_len) && (rx_data != ' '))/* Ignore spaces */
			rx_buffer[rx_cnt++] = rx_data;
			
		else if(rx_data == ';' && rx_cnt==rx_len)
		{
			SET_BIT(PORTA,1);
			_delay_ms(200);
			CLR_BIT(PORTA,1);
			_delay_ms(200);
			switch (rx_buffer[0]){
				case RESET:
						rx_cnt = 0;
						readFrom  = STOP;
						break;
				
				case READ:
					SET_BIT(PORTA,2);
					_delay_ms(200);
					CLR_BIT(PORTA,2);
					_delay_ms(200);
					if(readFrom==RAM)
						*r = _MEM((uint16_t)rx_buffer[1]);
					else if(readFrom==ROM){						
						*r = eeprom_read((uint16_t)rx_buffer[1]);
					}
					UART_Transmit_Char(*r);
					break;
				
				case WRITE:
					SET_BIT(PORTA,2);
					_delay_ms(200);
					CLR_BIT(PORTA,2);
					_delay_ms(200);
					if(readFrom==RAM)
						_MEM((uint16_t)rx_buffer[1]) = rx_buffer[3];
					else if(readFrom==ROM)
						eeprom_write((uint16_t)rx_buffer[1],  rx_buffer[3]);
						SET_BIT(PORTA,1);
						_delay_ms(200);
						CLR_BIT(PORTA,1);
						_delay_ms(200);
					break;
				
				default:  //Wrong Command Number
					UART_Transmit_Char('E');
					break;
			}
			
			/*Indication that Data has been received*/
			SET_BIT(PORTA,0);
			_delay_ms(200);
			CLR_BIT(PORTA,0);
			_delay_ms(200);
			SET_BIT(PORTA,0);
			_delay_ms(200);
			CLR_BIT(PORTA,0);
		}
		sei();
	}
	
uint8_t UART_IsRxComplete(void)
{
	return (rx_cnt >= rx_len);
}
	
	
#else
	uint8_t UART_IsRxComplete(void)
	{
		return GET_BIT(UCSRA,RXC);
	}
#endif