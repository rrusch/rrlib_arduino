/**
 * Arduino library for digital output pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 * @version 0.0.0-dev
 */


#ifndef RRUSCH_PINDIGITALOUT_H
#define RRUSCH_PINDIGITALOUT_H

#include <Arduino.h>
//#include <Console.h>
#include "Pin.h"


class PinDigitalOut: public Pin
{
	public:
	PinDigitalOut(uint8_t pin);
};



#endif /* RRUSCH_PINDIGITALOUT_H */
