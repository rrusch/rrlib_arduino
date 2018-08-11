/**
 * Arduino library for digital input pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 * @version 0.0.0-dev
 */


#ifndef RRUSCH_PINDIGITALIN_H
#define RRUSCH_PINDIGITALIN_H

#include <Arduino.h>
//#include <Console.h>
#include "Pin.h"


class PinDigitalIn: public Pin
{
	public:
	PinDigitalIn(uint8_t pin, int mode=PinDigitalIn::MODE_DEFAULT);
	
	
	const static int MODE_DEFAULT=Pin::MODE_DIGITAL_IN;
	const static int MODE_PULLDOWN=Pin::MODE_DIGITAL_IN_PULLDOWN;
	const static int MODE_PULLUP=Pin::MODE_DIGITAL_IN_PULLUP;
	
};



#endif /* RRUSCH_PINDIGITALIN_H */
