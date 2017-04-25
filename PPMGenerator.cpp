#include "PPMGenerator.h"

#include "PPM/outputchannel.h"
#include "PPM/PPMOut.h"
#include "PPM/Timer1.h"


rc::PPMOut g_PPMOut(CHANNELS);

unsigned long PPMGenerator::last_command = 0;


void setCh(int argc, char **argv) {
	if (argc < 3) {
		Serial.println("setCh channel value");
		return;
	}

	String ch = argv[1];
	String val = argv[2];

	rc::setOutputChannel(static_cast<rc::OutputChannel>(ch.toInt()), val.toInt());
	g_PPMOut.update();
	PPMGenerator::last_command = millis();
}


void PPMGenerator::set_failsafe_state() {
	if (_config->ppm_fail_safe_time < 100 || _config->ppm_fail_safe_time > 5000) {
		_config->ppm_fail_safe_time = 500;
	}
	for (uint8_t i = 0; i < CHANNELS; ++i)
	{
		// fill input buffer, convert raw values to microseconds
		// we'll need to cast our iterator to an OutputChannel, but ugly but safe

		if (_config->ppm_channel_failsafe[i] < 500 || _config->ppm_channel_failsafe[i] > 3000) {
			_config->ppm_channel_failsafe[i] = 1500;
		}

		rc::setOutputChannel(static_cast<rc::OutputChannel>(i), _config->ppm_channel_failsafe[i]);
	}

	//set throttle failsafe
	if (_config->ppm_channel_failsafe[3] < 500 || _config->ppm_channel_failsafe[3] > 3000) {
		_config->ppm_channel_failsafe[3] = 700;
	}

	rc::setOutputChannel(static_cast<rc::OutputChannel>(3), _config->ppm_channel_failsafe[3]);
	g_PPMOut.update();
}

void PPMGenerator::init(Cmd *cmdSerial_, byte pin, PPM_INFO *config) {
	PPMGenerator::last_command = 0;
	_config = config;
	save_config = false;

	
	
	cmdSerial = cmdSerial_;
	cmdSerial->Add("setCh", setCh);
	rc::Timer1::init();

	// initialize PPMOut with some settings
	g_PPMOut.setPulseLength(448);   // pulse length in microseconds
	g_PPMOut.setPauseLength(10448); // length of pause after last channel in microseconds
									// note: this is also called the end of frame, or start of frame, and is usually around 10ms

									// start PPMOut, use pin 9 (pins 9 and 10 are preferred)
	g_PPMOut.start(pin);

	set_failsafe_state();
}

void PPMGenerator::set_value(byte channel, int value) {
	rc::setOutputChannel(static_cast<rc::OutputChannel>(channel), value);
	g_PPMOut.update();
}


void PPMGenerator::poll() {
	if (PPMGenerator::last_command + _config->ppm_fail_safe_time < millis()) {
		set_failsafe_state();
	}
}