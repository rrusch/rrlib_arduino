/**
 * Arduino library for I/O Pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 * @version 0.0.0-dev
 */


#ifndef RRUSCH_PIN_H
#define RRUSCH_PIN_H

#include <Arduino.h>
//#include <Console.h>


class Pin;
typedef void (*pinEventHandler)(Pin&);


class Pin
{

public:
	Pin(uint8_t pin, int mode);
	void setup();
	void update();
	
	
	void setPin(uint8_t pin);
	void setMode(int mode);
	void setInterval(unsigned long interval);
	void setName(const char name[]);
	const char* getName();
	
	void calcAvg(int values);
	void calcDiv4();
	void dumpBuffer();
	
	int readValue();
	void writeValue(int value);
	
	int getValue();
	bool isHigh();
	bool isLow();
	bool isPosEdge();
	bool isNegEdge();
	bool isChanged();
	
	void onHigh(pinEventHandler handler) { cb_onHigh=handler; };
	void onLow(pinEventHandler handler) { cb_onLow=handler; };
	void onPosEdge(pinEventHandler handler) { cb_onPosEdge=handler; };
	void onNegEdge(pinEventHandler handler) { cb_onNegEdge=handler; };
	void onChange(pinEventHandler handler, int delta=1) { cb_onChange=handler; onChangeDelta=delta; };
	
	const static int MODE_UNDEF=0;
	const static int MODE_DIGITAL_OUT=1;
	const static int MODE_DIGITAL_IN=2;
	const static int MODE_DIGITAL_IN_PULLDOWN=3;
	const static int MODE_DIGITAL_IN_PULLUP=4;
	const static int MODE_PWM_OUT=5;
	const static int MODE_ANALOG_IN=6;
	const static int MODE_ANALOG_IN_PULLDOWN=7;
	const static int MODE_ANALOG_IN_PULLUP=8;
	
	const static int VALUE_UNDEF=-1;
	const static int VALUE_LOW=0;
	const static int VALUE_HIGH=1023;
	
	const static int CALC_NONE=0;
	const static int CALC_AVG=1;
	const static int CALC_DIV4=2;
	
private:
	uint8_t pin;
	int mode;
	unsigned long interval;
	unsigned long lastRunTime;
	int rawValue;
	int rawPreviousValue;
	int calcValue;
	int calcPreviousValue;
	char *name;
	
	int calc;
	int bufferSize;
	int bufferPointer;
	int *buffer;
	void initBuffer(int size);
	void writeBuffer(int value);
	int doCalc();
	
	pinEventHandler cb_onHigh;
	pinEventHandler cb_onLow;
	pinEventHandler cb_onPosEdge;
	pinEventHandler cb_onNegEdge;
	pinEventHandler cb_onChange;
	int onChangeDelta;
	
};



#endif /* RRUSCH_PIN_H */
