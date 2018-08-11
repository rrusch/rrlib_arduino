/**
 * Arduino library for digital output pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */

#include "PinDigitalOut.h"


PinDigitalOut::PinDigitalOut(uint8_t pin)
	: Pin(pin, Pin::MODE_DIGITAL_OUT)
{
};


