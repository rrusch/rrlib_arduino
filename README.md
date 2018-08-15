# rrlib_arduino
Common functions for arduino projects.
This library contains the following components.


## Scheduler
A central component to emulate some kind of "multitasking" without
the need for the EVIL delay().
Features:
* Run functions once or recurring
* Run functions based on loop count or milli seconds
* Modify events in run-time
* Workaround for the millis() overflow


## Pin
The Pin component makes using pins easy. Features:
* Easy to use classes for Digital in/out, Analog in and PWM Out
* Register callback functions for value change, status and edges
* Make calculations based on raw analog input value
* Set a name for a pin

