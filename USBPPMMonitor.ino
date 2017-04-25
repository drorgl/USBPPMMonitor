
#include "Persistency.h"
#include "PPMGenerator.h"
#include "TFTProcessor.h"



struct MODULE_CONFIG {
	PPM_INFO ppm_info;
};

#define PERSISTENCY_VERSION 1
MODULE_CONFIG module_config;
Persistency<MODULE_CONFIG> persistency;


const char Banner[] = "** USB PPM Monitor v1.00 **";
const char Prompt[] = ">";
const char BadCommand[] = "Command not recognized";

Cmd cmdSerial(&Serial, 50, false, (char*)&Banner, (char*)&Prompt, (char*)&BadCommand);

#define PPM_PIN 9

TFTProcessor tftprocessor;
PPMGenerator ppmgenerator;


void setChFailSafe(int argc, char **argv) {
	if (argc < 3) {
		Serial.println("setChFailSafe channel value");
		return;
	}

	String ch = argv[1];
	String val = argv[2];

	module_config.ppm_info.ppm_channel_failsafe[ch.toInt()] = val.toInt();
	ppmgenerator.save_config = true;
}

void setFailSafeTime(int argc, char **argv) {
	if (argc < 2) {
		Serial.println("setFailSafeTime ms");
		return;
	}

	String timems = argv[1];

	module_config.ppm_info.ppm_fail_safe_time = timems.toInt();
	ppmgenerator.save_config = true;
}

void setup()
{	
	cmdSerial.Add("setChFailSafe", setChFailSafe);
	cmdSerial.Add("setFailSafeTime", setFailSafeTime);

	persistency.load(PERSISTENCY_VERSION, 0, &module_config);
	Serial.begin(115200);

	pinMode(TFT_CS, OUTPUT);
	digitalWrite(TFT_CS, LOW);


	pinMode(TFT_RST, OUTPUT);

	digitalWrite(TFT_RST, LOW);

	digitalWrite(TFT_RST, HIGH);

	tftprocessor.setup(&cmdSerial);
	ppmgenerator.init(&cmdSerial, PPM_PIN, &module_config.ppm_info);
}


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240



void loop()
{
	cmdSerial.Poll();
	ppmgenerator.poll();

	if (ppmgenerator.save_config == true) {
		ppmgenerator.save_config = false;
		persistency.save(PERSISTENCY_VERSION, 0, &module_config);
	}
}
