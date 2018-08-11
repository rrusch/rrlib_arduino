/**
 * Arduino library for PWM output pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 * @version 0.0.0-dev
 */


#ifndef RRUSCH_PINPWMOUT_H
#define RRUSCH_PINPWMOUT_H

#include <Arduino.h>
//#include <Console.h>
#include "Pin.h"


class PinPwmOut: public Pin
{
	public:
	PinPwmOut(uint8_t pin);
};



#endif /* RRUSCH_PINPWMOUT_H */
