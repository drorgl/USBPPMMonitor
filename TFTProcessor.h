// TFTProcessor.h

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
//
#define TFT_MOSI 16
#define TFT_CLK 15
#define TFT_MISO 14


//Adafruit_ILI9340 tft = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
TFT_ILI93XX tft = TFT_ILI93XX(A3, TFT_DC);// , TFT_DC);// , TFT_RST);

//TFT_ILI93XX tft;

void setRotation(int argc, char **argv) {
	if (argc < 2) {
		Serial.println("setOrientation 0/1/2/3");
		return;
	}

	String inString = argv[1];

	tft.setRotation(inString.toInt());
}

void clearScreen(int argc, char **argv) {
	tft.clearScreen();
}

void drawArc(int argc, char **argv) {
	if (argc < 8) {
		Serial.println("drawArc cx, cy, radius, thickness, start, end, color");
		return;
	}

	String cx = argv[1];
	String cy= argv[2];
	String radius= argv[3];
	String thickness= argv[4];
	String start = argv[5];
	String end = argv[6];
	String color= argv[7];

	tft.drawArc(cx.toInt(), cy.toInt(), radius.toInt(), thickness.toInt(), start.toFloat(), end.toFloat(), color.toInt());
}

void fillScreen(int argc, char **argv) {
	if (argc < 2) {
		Serial.println("fillScreen color");
		return;
	}

	String color = argv[1];

	tft.fillScreen(color.toInt());
}


void drawCircle(int argc, char **argv) {
	if (argc < 5) {
		Serial.println("drawCircle x, y, radius, color");
		return;
	}

	String x = argv[1];
	String y= argv[2];
	String radius= argv[3];
	String color = argv[4];

	tft.drawCircle(x.toInt(),y.toInt(), radius.toInt(), color.toInt());
}

void drawFastHLine(int argc, char **argv) {
	if (argc < 5) {
		Serial.println("drawFastHLine x, y, w, color");
		return;
	}

	String x = argv[1];
	String y = argv[2];
	String w = argv[3];
	String color = argv[4];

	tft.drawFastHLine(x.toInt(), y.toInt(), w.toInt(), color.toInt());
}

void drawFastVLine(int argc, char **argv) {
	if (argc < 5) {
		Serial.println("drawFastVLine x, y, h, color");
		return;
	}

	String x = argv[1];
	String y = argv[2];
	String h = argv[3];
	String color = argv[4];

	tft.drawFastVLine(x.toInt(), y.toInt(), h.toInt(), color.toInt());
}


void setCursor(int argc, char **argv) {
	if (argc < 3) {
		Serial.println("setCursor x, y");
		return;
	}

	String x = argv[1];
	String y = argv[2];

	tft.setCursor(x.toInt(), y.toInt());
}

void setTextColor(int argc, char **argv) {
	if (argc < 3) {
		Serial.println("setTextColor frgrnd, bckgnd");
		return;
	}

	String frgrnd = argv[1];
	String bckgnd = argv[2];

	tft.setTextColor(frgrnd.toInt(), bckgnd.toInt());
}

void setTextScale(int argc, char **argv) {
	if (argc < 3) {
		Serial.println("setTextScale sx, sy");
		return;
	}

	String sx = argv[1];
	String sy = argv[2];

	tft.setTextScale(sx.toInt(), sy.toInt());
}

void println(int argc, char **argv) {
	if (argc < 2) {
		Serial.println("println string");
		return;
	}

	String str;
	for (auto i = 1; i < argc; i++) {
		str += argv[i];
		str += " ";
	}

	tft.println(str);
}


class TFTProcessor {
private:
	Cmd *cmdSerial;
	

	
public:
	void setup(Cmd *cmdSerial_) {
		cmdSerial = cmdSerial_;

		tft.begin();

		cmdSerial->Add("setRotation", setRotation);
		cmdSerial->Add("clearScreen", clearScreen);
		cmdSerial->Add("drawArc", drawArc);
		cmdSerial->Add("fillScreen", fillScreen);
		cmdSerial->Add("drawCircle", drawCircle);
		cmdSerial->Add("drawFastHLine", drawFastHLine);
		cmdSerial->Add("drawFastVLine", drawFastVLine);
		cmdSerial->Add("setCursor", setCursor);
		cmdSerial->Add("setTextColor", setTextColor);
		cmdSerial->Add("setTextScale", setTextScale);
		cmdSerial->Add("println", println);



	}

	void loop() {

	}
};

#endif

