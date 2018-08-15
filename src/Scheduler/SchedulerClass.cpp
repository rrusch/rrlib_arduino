/**
 * Arduino library rrlib_arduino Scheduler component.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */

#include "SchedulerClass.h"


rrlib::SchedulerClass rrlib::Scheduler;


rrlib::SchedulerClass::SchedulerClass() :
	loopCount(0),
	lastLoopMillis(0),
	loopDuration(0),
	lastUsedEventId(1),
	activeEventId(0),
	schedulerStatus(SchedulerStatus::DISABLE),
	schedulerEventList()
{
	setup();
};


rrlib::SchedulerClass::~SchedulerClass()
{
	end();
};


/**
 * Start the scheduler and allow the execution of events.
 */
void rrlib::SchedulerClass::begin()
{
	schedulerStatus=SchedulerStatus::ENABLE;
};


/**
 * Stop the scheduler and prevent further events.
 */
void rrlib::SchedulerClass::end()
{
	schedulerStatus=SchedulerStatus::DISABLE;
};


void rrlib::SchedulerClass::setup()
{
};


void rrlib::SchedulerClass::loop()
{
	loopCount++;
	uint32_t thisLoopMillis=millis();
	if(loopCount == 1) lastLoopMillis=thisLoopMillis;
	if(thisLoopMillis < lastLoopMillis)
	{
		// we had an overflow of the millis() function (~every 70 days)
		loopDuration=thisLoopMillis + (UINT32_MAX - lastLoopMillis);
	} else
	{
		loopDuration=thisLoopMillis - lastLoopMillis;
	}
	lastLoopMillis=thisLoopMillis;
	
	
	for(rrlib::SchedulerClass::SchedulerEventList::iterator it = this->schedulerEventList.begin();
			it != this->schedulerEventList.end();
			++it)
	{
		activeEventId=it->eventId;
		switch(it->timeUnit)
		{
			case SchedulerEventTimeUnit::LOOP_ONCE:
				if( it->countdownTimeValue > 1 )
				{
					it->countdownTimeValue--;
				} else
				{
					if(schedulerStatus == SchedulerStatus::ENABLE) it->handler();
					it->timeUnit=SchedulerEventTimeUnit::LOOP_ONCE_INACTIVE;
				}
				break;
				
				
			case SchedulerEventTimeUnit::LOOP_RECURRING:
				if( it->countdownTimeValue > 1 )
				{
					it->countdownTimeValue--;
				} else
				{
					if(schedulerStatus == SchedulerStatus::ENABLE) it->handler();
					it->countdownTimeValue=it->origTimeValue;
				}
				break;
				
				
			case SchedulerEventTimeUnit::MS_ONCE:
				if( it->countdownTimeValue > loopDuration )
				{
					it->countdownTimeValue-=loopDuration;
				} else
				{
					it->countdownTimeValue=0;
					if(schedulerStatus == SchedulerStatus::ENABLE) it->handler();
					it->timeUnit=SchedulerEventTimeUnit::MS_ONCE_INACTIVE;
				}
				break;
				
				
			case SchedulerEventTimeUnit::MS_RECURRING:
				if( it->countdownTimeValue > loopDuration )
				{
					it->countdownTimeValue-=loopDuration;
				} else
				{
					it->countdownTimeValue=0;
					if(schedulerStatus == SchedulerStatus::ENABLE) it->handler();
					it->countdownTimeValue=it->origTimeValue;
				}
				break;
				
				
			default:
				break;
		}
	}
	
	activeEventId=0;
};


uint64_t rrlib::SchedulerClass::getLoopCount()
{
	return loopCount;
};


uint32_t rrlib::SchedulerClass::getLoopDuration()
{
	return loopDuration;
};


rrlib::SchedulerClass::EventId rrlib::SchedulerClass::getActiveEventId()
{
	return activeEventId;
};

rrlib::SchedulerClass::SchedulerEventListEntry* rrlib::SchedulerClass::getActiveEventListEntry(
		EventId eventId)
{
	if(eventId == 0) eventId=getActiveEventId();
	for(rrlib::SchedulerClass::SchedulerEventList::iterator it = this->schedulerEventList.begin();
			it != this->schedulerEventList.end();
			++it)
	{
		if(it->eventId == eventId) return it;
	}
	return nullptr;
}

rrlib::SchedulerClass::EventId rrlib::SchedulerClass::addEvent(SchedulerEventHandler handler,
		SchedulerEventTimeUnit timeUnit, uint64_t origTimeValue)
{
	SchedulerEventListEntry e;
	e.eventId=lastUsedEventId++;
	e.handler=handler;
	e.timeUnit=timeUnit;
	e.countdownTimeValue=origTimeValue;
	e.origTimeValue=origTimeValue;
	this->schedulerEventList.push_back(e);
	return e.eventId;
}

