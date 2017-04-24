// 
// 
// 

#include "PPMGenerator.h"


#include "PPM/outputchannel.h"
#include "PPM/PPMOut.h"
#include "PPM/Timer1.h"


#define CHANNELS 8

rc::PPMOut g_PPMOut(CHANNELS);


void setCh(int argc, char **argv) {
	if (argc < 3) {
		Serial.println("setCh channel value");
		return;
	}

	String ch = argv[1];
	String val = argv[2];

	rc::setOutputChannel(static_cast<rc::OutputChannel>(ch.toInt()), val.toInt());
	g_PPMOut.update();
}

void PPMGenerator::init(Cmd *cmdSerial_, byte pin) {
	cmdSerial = cmdSerial_;
	cmdSerial->Add("setCh", setCh);
	//ppm_encoder_init(pin);
	//setup_ppm(pin);

	// Initialize timer1, this is required for all features that use Timer1
	// (PPMIn/PPMOut/ServoIn/ServoOut)
	rc::Timer1::init();

	for (uint8_t i = 0; i < CHANNELS; ++i)
	{

		// fill input buffer, convert raw values to microseconds
		// we'll need to cast our iterator to an OutputChannel, but ugly but safe
		rc::setOutputChannel(static_cast<rc::OutputChannel>(i), 1500);
	}

	rc::setOutputChannel(static_cast<rc::OutputChannel>(3), 700);

	// initialize PPMOut with some settings
	g_PPMOut.setPulseLength(448);   // pulse length in microseconds
	g_PPMOut.setPauseLength(10448); // length of pause after last channel in microseconds
									// note: this is also called the end of frame, or start of frame, and is usually around 10ms

									// start PPMOut, use pin 9 (pins 9 and 10 are preferred)
	g_PPMOut.start(pin);
}

void PPMGenerator::set_value(byte channel, int value) {
	//ppm_write_channel(channel, value);
	//ppm[channel] = value;
	rc::setOutputChannel(static_cast<rc::OutputChannel>(channel), value);
	g_PPMOut.update();
}
