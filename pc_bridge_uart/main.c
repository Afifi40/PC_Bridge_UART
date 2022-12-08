/*
 * main.c
 *
 * Created: 19/10/2022 18:42
 * Edited:	29/10/2022 14:16
 * Author : Afifi 
 */ 


#include "utilites.h"
#include "UART.h"
#include "ADC.h"
#include "Timer.h"

void hardware_init(uint8_t);
void lab2();
void lab3();
int main(void)
{
	//lab2(); //Needs to be Tested
	lab3(); //Work in progress
	
	while(1){
		
	}


    
}

void hardware_init(uint8_t lab_number){
	switch(lab_number){
		case 2:
			DDRA = 255;
			UART_init(9600);
			ADC_init();
			PWM0_init();
			sei();
			break;
		case 3:
			DDRA|=0b111;
			UART_init(9600);
			sei();
			break;
	}
}
/*
void lab2(){
	hardware_init(2);
	float dutyCycle = 0;
	char temp[10]={};
	while (1)
	{
		if((PINB & (1<<2)) == 0){
			switch(UART_Receive_Char())
			{
				case '1':// turn off LED.
					PORTA = 1;
					break;
				case '2':// turn on LED
					PORTA = 0;
					break;
				case '+':// Raise Motor Speed
					if(dutyCycle != 1)
						dutyCycle+=0.1;
					break;
				case '-':// Lessen Motor Speed
					if(dutyCycle != 0)
						dutyCycle-=0.1;
					break;
				default:
					break;
			}
		}
			
		if(!GET_BIT(PINB,0))
			UART_Transmit_Char('A');
		
		if(!GET_BIT(PINB,1))
			UART_Transmit_Char('Z');
		
		uint8_t x = 13;//ADC_Read(1) *.4883 - 50;
		sprintf(temp,"#%d$",x);
		for(int i=0; i<10 || temp[i]!='\0' ; i++){
			UART_Transmit_Char(temp[i]);
		}
		PWM0_Set_DutyCycle(dutyCycle);
		_delay_ms(100);
	}
}
*/
void lab3(){
	SET_BIT(PORTA,2);
	hardware_init(3);
	while(1){
	}
	
}