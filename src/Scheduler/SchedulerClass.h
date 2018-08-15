/**
 * Arduino library rrlib_arduino Scheduler component.
 * The component uses https://github.com/maniacbug/StandardCplusplus.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */

#ifndef RRUSCH_SCHEDULER_H
#define RRUSCH_SCHEDULER_H

#include <StandardCplusplus.h>
#include <stdint.h>
#include <vector>
#include <Arduino.h>

namespace rrlib
{


typedef void (*SchedulerEventHandler)();


class SchedulerClass
{
public:
	SchedulerClass();
	~SchedulerClass();
	
	void setup();
	void loop();
	
	void begin();
	void end();
	
	uint64_t getLoopCount();
	uint32_t getLoopDuration();
	
	typedef uint8_t EventId;
	EventId getActiveEventId();
	
	enum class SchedulerEventTimeUnit {
		DISABLE,
		LOOP_ONCE,
		LOOP_ONCE_INACTIVE,
		LOOP_RECURRING,
		LOOP_RECURRING_INACTIVE,
		MS_ONCE,
		MS_ONCE_INACTIVE,
		MS_RECURRING,
		MS_RECURRING_INACTIVE,
	};
	struct SchedulerEventListEntry {
		EventId eventId;
		SchedulerEventHandler handler;
		SchedulerEventTimeUnit timeUnit;
		uint64_t countdownTimeValue;
		uint64_t origTimeValue;
	};
	SchedulerEventListEntry* getActiveEventListEntry(EventId eventId = 0);
	
	EventId onLoop(SchedulerEventHandler handler, uint64_t loops) { return addEvent(handler, rrlib::SchedulerClass::SchedulerEventTimeUnit::LOOP_ONCE, loops); };
	EventId onEveryLoop(SchedulerEventHandler handler, uint64_t loops = 1) { return addEvent(handler, rrlib::SchedulerClass::SchedulerEventTimeUnit::LOOP_RECURRING, loops); };
	EventId onMillis(SchedulerEventHandler handler, uint64_t millis) { return addEvent(handler, rrlib::SchedulerClass::SchedulerEventTimeUnit::MS_ONCE, millis); };
	EventId onEveryMillis(SchedulerEventHandler handler, uint64_t millis) { return addEvent(handler, rrlib::SchedulerClass::SchedulerEventTimeUnit::MS_RECURRING, millis); };
	
	
private:
	uint64_t loopCount;
	uint32_t lastLoopMillis;
	uint32_t loopDuration;
	EventId lastUsedEventId;
	EventId activeEventId;
	
	enum class SchedulerStatus {
		DISABLE,
		ENABLE
	} schedulerStatus;
	
	typedef std::vector<SchedulerEventListEntry> SchedulerEventList;
	SchedulerEventList schedulerEventList;
	
	
	EventId addEvent(SchedulerEventHandler handler, SchedulerEventTimeUnit timeUnit, uint64_t origTimeValue);
	
};

extern SchedulerClass Scheduler;

};

#endif /* RRUSCH_SCHEDULER_H */
