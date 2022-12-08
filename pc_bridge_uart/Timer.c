/*
 * Timer.c
 *
 * Created: 10/29/2022 2:12:03 PM
 *  Author: ahmed
 */ 
#include "Timer.h"

void PWM0_init(){
		SET_BIT(DDRB,3);
	    TCCR0=0b01110101; //Configure TCCR0 as explained in the article
	    TIMSK=0b00000000;
	    OCR0=255; // Set OCR0 to 255 so that the duty cycle is initially 0 and the motor is not rotating	    	
}
void PWM0_Set_DutyCycle(uint8_t dutyCycle){
		OCR0 = 255 * (1 - dutyCycle);
}
