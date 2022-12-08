/*
 * EEPROM.c
 *
 * Created: 29/10/2022 20:01
 *  Author: Afifi
 */ 
#include "EEPROM.h"


uint8_t eeprom_read (uint16_t  address){
		
		EEAR = address;
		SET_BIT(EECR,EERE);
		
		while(GET_BIT(EECR, EEWE) == 1){}
		
		return EEDR;
}


void eeprom_write (uint16_t  address, uint8_t data){
		EEAR = address;
		EEDR = data;
		SET_BIT(EECR, EEMWE);
		SET_BIT(EECR, EEWE);
		while(GET_BIT(EECR, EEWE) == 1){}
}