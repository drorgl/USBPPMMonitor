
#include "Persistency.h"
#include "PPMGenerator.h"
#include "TFTProcessor.h"
//#include <SPI.h>
//#include <Adafruit_GFX.h>
//#include <TFT_ILI93XX.h>
//#define USE_SPI_LIBRARY
//#include <SPI.h>

//#include <Adafruit_ILI9340.h>
//#include <SparkFunMLX90614.h>
//#include <Servo.h>

// For the Adafruit shield, these are the default.
//#define TFT_DC A2
//#define TFT_CS A0
//#define TFT_RST A1
////
//#define TFT_MOSI 16
//#define TFT_CLK 15
//#define TFT_MISO 14
//
//
////Adafruit_ILI9340 tft = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
//TFT_ILI93XX tft = TFT_ILI93XX(A3, TFT_DC);// , TFT_DC);// , TFT_RST);

struct MODULE_CONFIG {
	uint16_t ppm_fail_safe_time;
	uint16_t ppm_channel_failsafe[8];
};

Persistency<MODULE_CONFIG> persistency;


const char Banner[] = "** CMD **";
const char Prompt[] = ">";
const char BadCommand[] = "Command not recognized";

Cmd cmdSerial(&Serial, 50, false, (char*)&Banner, (char*)&Prompt, (char*)&BadCommand);

#define PPM_PIN 9

TFTProcessor tftprocessor;
PPMGenerator ppmgenerator;
void setup()
{
	Serial.begin(115200);

	pinMode(TFT_CS, OUTPUT);
	digitalWrite(TFT_CS, LOW);


	pinMode(TFT_RST, OUTPUT);

	digitalWrite(TFT_RST, LOW);

	digitalWrite(TFT_RST, HIGH);

	//tft.begin();
	//tft.setBitrate(24000000);
	//SPISettings()
	//SPI.setClockDivider(0);
	//SPI.beginTransaction()

	//delay(100);
	//tft.fillScreen(ILI9340_BLACK);
	//tft.setRotation(3);


	//// read diagnostics (optional but can help debug problems)
	//uint8_t x = tft.readcommand8(ILI9340_RDMODE);
	//Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
	//x = tft.readcommand8(ILI9340_RDMADCTL);
	//Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
	//x = tft.readcommand8(ILI9340_RDPIXFMT);
	//Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
	//x = tft.readcommand8(ILI9340_RDIMGFMT);
	//Serial.print("Image Format: 0x"); Serial.println(x, HEX);
	//x = tft.readcommand8(ILI9340_RDSELFDIAG);
	//Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);
	tftprocessor.setup(&cmdSerial);
	ppmgenerator.init(&cmdSerial, PPM_PIN);
}


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240



void loop()
{
	cmdSerial.Poll();

//	unsigned long start = micros();
	/*tft.fillScreen(BLACK);
	tft.fillScreen(RED);
	tft.fillScreen(GREEN);
	tft.fillScreen(BLUE);*/
	//return micros() - start;
}
