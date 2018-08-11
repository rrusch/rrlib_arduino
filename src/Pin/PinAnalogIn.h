/**
 * Arduino library for analog input pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 * @version 0.0.0-dev
 */


#ifndef RRUSCH_PINANALOGIN_H
#define RRUSCH_PINANALOGIN_H

#include <Arduino.h>
//#include <Console.h>
#include "Pin.h"


class PinAnalogIn: public Pin
{
	public:
	PinAnalogIn(uint8_t pin);
};



#endif /* RRUSCH_PINANALOGIN_H */
