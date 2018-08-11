/**
 * Arduino library for digital input pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */

#include "PinDigitalIn.h"


PinDigitalIn::PinDigitalIn(uint8_t pin, int mode)
	: Pin(pin, mode)
{
};


