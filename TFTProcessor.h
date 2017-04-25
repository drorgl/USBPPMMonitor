#ifndef _TFTPROCESSOR_h
#define _TFTPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Cmd.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI93XX.h>

#define TFT_DC A2
#define TFT_CS A0
#define TFT_RST A1

#define TFT_MOSI 16
#define TFT_CLK 15
#define TFT_MISO 14




class TFTProcessor {
private:
	Cmd *cmdSerial;
	
public:
	void setup(Cmd *cmdSerial_);
	void loop();
};

#endif

