/**
 * Arduino library for PWM output pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */

#include "PinPwmOut.h"


PinPwmOut::PinPwmOut(uint8_t pin)
	: Pin(pin, Pin::MODE_PWM_OUT)
{
};


