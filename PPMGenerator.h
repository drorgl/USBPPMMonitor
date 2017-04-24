// PPMGenerator.h

#ifndef _PPMGENERATOR_h
#define _PPMGENERATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Cmd.h>

class PPMGenerator
{
private:
	Cmd *cmdSerial;
protected:
	byte _pin;


public:
	void init(Cmd *cmdSerial_, byte pin);

	void set_value(byte channel, int value);

	//TODO: add failsafe, reduce throttle to 700 if no change was received in the last 100ms
	//void poll();
};


#endif

