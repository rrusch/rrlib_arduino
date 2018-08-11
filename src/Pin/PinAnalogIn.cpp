/**
 * Arduino library for analog input pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */

#include "PinAnalogIn.h"


PinAnalogIn::PinAnalogIn(uint8_t pin)
	: Pin(pin, Pin::MODE_ANALOG_IN)
{
};


