/**
 * Arduino library for I/O Pins.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */

#include "Pin.h"


Pin::Pin(uint8_t pin, int mode)
{
	this->pin=NOT_A_PIN;
	this->mode=Pin::MODE_UNDEF;
	this->interval=50;
	this->lastRunTime=0;
	this->rawValue=Pin::VALUE_UNDEF;
	this->rawPreviousValue=Pin::VALUE_UNDEF;
	this->calcValue=Pin::VALUE_UNDEF;
	this->calcPreviousValue=Pin::VALUE_UNDEF;
	this->name=0;
	
	this->calc=Pin::CALC_NONE;
	this->bufferSize=-1;
	this->bufferPointer=-1;
	this->buffer=0;
	
	this->onChangeDelta=0;
	
	cb_onHigh=0;
	cb_onLow=0;
	cb_onPosEdge=0;
	cb_onNegEdge=0;
	cb_onChange=0;
	
	
	this->setPin(pin);
	this->setMode(mode);
	this->setup();
};


void Pin::setup()
{
};


void Pin::update()
{
	if( (this->interval == 0) || ((millis() - this->lastRunTime) > this->interval) )
	{
		this->lastRunTime=millis();
		
		this->rawPreviousValue=this->rawValue;
		this->rawValue=this->readValue();
		this->writeBuffer(this->rawValue);
		
		this->calcPreviousValue=this->calcValue;
		this->calcValue=this->doCalc();
		
		// No value, no event
		if( this->calcValue == Pin::VALUE_UNDEF ) return;
		
		if( (this->cb_onHigh != 0) && (this->isHigh()) ) cb_onHigh(*this);
		if( (this->cb_onLow != 0) && (this->isLow()) ) cb_onLow(*this);
		
		
		// Only one value, no edge
		if( this->calcPreviousValue == Pin::VALUE_UNDEF ) return;
		if( (this->cb_onPosEdge != 0) && this->isPosEdge() ) cb_onPosEdge(*this);
		if( (this->cb_onNegEdge != 0) && this->isNegEdge() ) cb_onNegEdge(*this);
		if( (this->cb_onChange != 0) && this->isChanged() ) cb_onChange(*this);
		
	}
	
};


int Pin::getValue()
{
	return this->calcValue;
}


bool Pin::isHigh()
{
	return this->calcValue == Pin::VALUE_HIGH;
}


bool Pin::isLow()
{
	return this->calcValue == Pin::VALUE_LOW;
}


bool Pin::isPosEdge()
{
	return (this->calcPreviousValue == Pin::VALUE_LOW) && (this->calcValue == Pin::VALUE_HIGH);
}


bool Pin::isNegEdge()
{
	return (this->calcPreviousValue == Pin::VALUE_HIGH) && (this->calcValue == Pin::VALUE_LOW);
}


bool Pin::isChanged()
{
	return (this->calcPreviousValue != this->calcValue) 
			&& (abs(this->calcPreviousValue - this->calcValue) >= this->onChangeDelta);
}


void Pin::setPin(uint8_t pin)
{
	this->pin=pin;
};


void Pin::setMode(int mode)
{
	switch(mode)
	{
		case Pin::MODE_DIGITAL_OUT:
			pinMode(this->pin, OUTPUT);
			digitalWrite(this->pin, LOW);
			break;

		case Pin::MODE_DIGITAL_IN:
			pinMode(this->pin, INPUT);
			break;

		case Pin::MODE_DIGITAL_IN_PULLDOWN:
			pinMode(this->pin, INPUT);
			digitalWrite(this->pin, LOW);
			break;

		case Pin::MODE_DIGITAL_IN_PULLUP:
			pinMode(this->pin, INPUT_PULLUP);
			digitalWrite(this->pin, HIGH);
			break;

		case Pin::MODE_PWM_OUT:
			pinMode(this->pin, OUTPUT);
			digitalWrite(this->pin, LOW);
			break;

		case Pin::MODE_ANALOG_IN:
			pinMode(this->pin, INPUT);
			break;

		case Pin::MODE_ANALOG_IN_PULLDOWN:
			pinMode(this->pin, INPUT);
			digitalWrite(this->pin, LOW);
			break;

		case Pin::MODE_ANALOG_IN_PULLUP:
			pinMode(this->pin, INPUT_PULLUP);
			digitalWrite(this->pin, HIGH);
			break;

		default:
			mode=Pin::MODE_UNDEF;
			break;
	}

	this->mode=mode;
};


void Pin::setInterval(unsigned long interval)
{
	this->interval=interval;
};


void Pin::setName(const char name[])
{
	this->name=new char[strlen(name)+1];
	strcpy(this->name, name);
}


const char* Pin::getName()
{
	return this->name;
}


void Pin::calcAvg(int values)
{
	this->initBuffer(values);
	this->calc=Pin::CALC_AVG;
}


void Pin::calcDiv4()
{
	this->initBuffer(0);
	this->calc=Pin::CALC_DIV4;
}


int Pin::readValue()
{
	switch(this->mode)
	{
		case Pin::MODE_DIGITAL_OUT:
		case Pin::MODE_DIGITAL_IN:
		case Pin::MODE_DIGITAL_IN_PULLDOWN:
		case Pin::MODE_DIGITAL_IN_PULLUP:
			return (digitalRead(this->pin) == HIGH) ? Pin::VALUE_HIGH : Pin::VALUE_LOW;
			break;
			
		case Pin::MODE_ANALOG_IN:
			return analogRead(this->pin);
			break;
			
		case Pin::MODE_PWM_OUT:
		default:
			break;
	}
	
	return Pin::VALUE_UNDEF;
}


void Pin::writeValue(int value)
{
	switch(this->mode)
	{
		case Pin::MODE_DIGITAL_OUT:
			digitalWrite(this->pin, (value==Pin::VALUE_HIGH) ? HIGH : LOW);
			break;
			
		case Pin::MODE_PWM_OUT:
			analogWrite(this->pin, value);
			break;
			
		case Pin::MODE_DIGITAL_IN:
		case Pin::MODE_DIGITAL_IN_PULLDOWN:
		case Pin::MODE_DIGITAL_IN_PULLUP:
		case Pin::MODE_ANALOG_IN:
		default:
			break;
	}
}


void Pin::initBuffer(int size)
{
//	this->dumpBuffer();
	
	if(this->bufferSize > 0)
	{
		delete this->buffer;
		this->buffer=0;
		this->bufferSize=0;
		this->bufferPointer=0;
	}
	
	this->buffer=new int[size];
	this->bufferSize=size;
	this->bufferPointer=0;
	for(int i=0; i < this->bufferSize; i++) this->buffer[i]=Pin::VALUE_UNDEF;
	
}


void Pin::writeBuffer(int value)
{
//	this->dumpBuffer();
	
	if(this->bufferSize <= 0) return;
	if(this->buffer == 0) return;
	this->buffer[this->bufferPointer]=value;
	this->bufferPointer++;
	if(this->bufferPointer >= this->bufferSize) this->bufferPointer=0;
}


void Pin::dumpBuffer()
{
	if(this->bufferSize <= 0) return;
	if(this->buffer == 0) return;
	
//	for(int i=0; i < this->bufferSize; i++)
//	{
//		Console.print(this->buffer[i]);
//		Console.print(" | ");
//	}
//	Console.println("");
//	Console.print("bufferPointer=");
//	Console.println(this->bufferPointer);
}


int Pin::doCalc()
{
//	if(this->bufferSize <= 0) return this->rawValue;
//	if(this->buffer == 0) return this->rawValue;
	
	int calcValue=Pin::VALUE_UNDEF;
	if( this->calc == Pin::CALC_AVG )
	{
		int avg=-1;
		for(int i=0; i < this->bufferSize; i++)
		{
			if(this->buffer[i] == Pin::VALUE_UNDEF) continue;
			if(avg < 0) avg=this->buffer[i];
			else avg=(avg + this->buffer[i]) / 2;
		}
		calcValue=avg;
	} else if( this->calc == Pin::CALC_DIV4 )
	{
		calcValue=(this->rawValue / 4) * 4;
	} else calcValue=this->rawValue;
	
	
	return calcValue;
}

