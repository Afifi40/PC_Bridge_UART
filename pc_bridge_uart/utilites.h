#ifndef UTILITIES_H_
#define UTILITIES_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define SET_BIT(REG, BITNO)	REG |= (1<<BITNO)
#define CLR_BIT(REG, BITNO) REG &= ~(1<<BITNO)
#define TOG_BIT(REG, BITNO) REG ^= (1<<BITNO)
#define GET_BIT(REG, BITNO) (REG & (1<<BITNO) >> BITNO)

#endif //UTILITIES_H_