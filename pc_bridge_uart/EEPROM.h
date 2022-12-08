/*
 * EEPROM.h
 *
 * Created: 29/10/2022 8:42:33 PM
 *  Author: Afifi
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "utilites.h"
#define  EEARR *( (uint16_t *) 0x1E)
//typedef uint8_t unsigned char;
uint8_t eeprom_read (uint16_t  address);
void eeprom_write (uint16_t  address, uint8_t data);


#endif /* EEPROM_H_ */