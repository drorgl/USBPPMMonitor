#ifndef _PPMGENERATOR_h
#define _PPMGENERATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Cmd.h>

#define CHANNELS 8

struct PPM_INFO {
	uint16_t ppm_fail_safe_time;
	uint16_t ppm_channel_failsafe[CHANNELS];

};

class PPMGenerator
{
private:
	Cmd *cmdSerial;
protected:
	byte _pin;
	
	void set_failsafe_state();
public:
	PPM_INFO *_config;
	static unsigned long last_command;
	bool save_config;

	void init(Cmd *cmdSerial_, byte pin, PPM_INFO *config);

	void set_value(byte channel, int value);


	//TODO: add failsafe, reduce throttle to 700 if no change was received in the last 100ms
	void poll();
};


#endif

