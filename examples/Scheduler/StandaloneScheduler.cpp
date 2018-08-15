/**
 * This is the test program for the Scheduler component.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */


#include <Arduino.h>
#include <Console.h>
#include "../../src/Scheduler.h"



void loop2()
{
	Console.print((unsigned long)rrlib::Scheduler.getLoopCount());
	Console.print(" loop2(): every 5 loops");
	Console.print(" | EventId=");
	Console.print(rrlib::Scheduler.getActiveEventId());
	
	// One could access the SchedulerEventListEntry and 
	// disable the event in run-time
	/*
	rrlib::SchedulerClass::SchedulerEventListEntry* it=rrlib::Scheduler.getActiveEventListEntry();
	Console.print(" | origTimeValue=");
	Console.print((unsigned long)it->origTimeValue);
	it->timeUnit=rrlib::Scheduler.SchedulerEventTimeUnit::DISABLE;
	*/
	
	Console.println("");
}


void loop3()
{
	Console.print((unsigned long)rrlib::Scheduler.getLoopCount());
	Console.print(" loop3(): once after 20 loops");
	Console.print(" | EventId=");
	Console.print(rrlib::Scheduler.getActiveEventId());
	Console.println("");
}


void loop4()
{
	Console.print((unsigned long)rrlib::Scheduler.getLoopCount());
	Console.print(" loop4(): every 10s");
	Console.print(" | EventId=");
	Console.print(rrlib::Scheduler.getActiveEventId());
	Console.println("");
}


void loop5()
{
	Console.print((unsigned long)rrlib::Scheduler.getLoopCount());
	Console.print(" loop5(): once after 13s");
	Console.print(" | EventId=");
	Console.print(rrlib::Scheduler.getActiveEventId());
	Console.println("");
}


//The setup function is called once at startup of the sketch
void setup()
{
	// initialize serial communication:
	Bridge.begin();
	Console.begin();
	
	// run loop2 on every 5 loops
	rrlib::Scheduler.onEveryLoop(loop2, 5);
	
	// run loop3 after 20 loops once
	rrlib::Scheduler.onLoop(loop3, 20);
	
	// run loop4 every 10s
	rrlib::Scheduler.onEveryMillis(loop4, 10000);
	
	// run loop5 after 13s once
	rrlib::Scheduler.onMillis(loop5, 13000);
	
	// start scheduler
	rrlib::Scheduler.begin();
}


bool consoleok=false;


// The loop function is called in an endless loop
void loop()
{
	rrlib::Scheduler.loop();
	Console.print((unsigned long)rrlib::Scheduler.getLoopCount());
	Console.print(" loop() | ");
	Console.print(rrlib::Scheduler.getLoopDuration());
	Console.print("ms");
	Console.print(" | EventId=");
	Console.print(rrlib::Scheduler.getActiveEventId());
	Console.println("");
	
	
	
	
	if( !consoleok && (Console.available() > 0) )
	{
		Console.println("You're connected to the Console!!!!");
		consoleok=true;
	}
	delay(500);
}





