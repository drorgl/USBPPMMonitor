#include "TFTProcessor.h"

TFT_ILI93XX tft = TFT_ILI93XX(A3, TFT_DC);// , TFT_DC);// , TFT_RST);

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
	String cy = argv[2];
	String radius = argv[3];
	String thickness = argv[4];
	String start = argv[5];
	String end = argv[6];
	String color = argv[7];

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
	String y = argv[2];
	String radius = argv[3];
	String color = argv[4];

	tft.drawCircle(x.toInt(), y.toInt(), radius.toInt(), color.toInt());
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

void drawRect(int argc, char **argv) {
	if (argc < 6) {
		Serial.println("drawRect x, y, w, h, color");
		return;
	}

	String x = argv[1];
	String y = argv[2];
	String w = argv[3];
	String h = argv[4];
	String color = argv[5];

	tft.drawRect(x.toInt(), y.toInt(), w.toInt(), h.toInt(), color.toInt());
}

void drawRoundRect(int argc, char **argv) {
	if (argc < 7) {
		Serial.println("drawRoundRect x, y, w, h,radius, color");
		return;
	}

	String x = argv[1];
	String y = argv[2];
	String w = argv[3];
	String h = argv[4];
	String radius = argv[5];
	String color = argv[6];

	tft.drawRoundRect(x.toInt(), y.toInt(), w.toInt(), h.toInt(),radius.toInt(), color.toInt());
}


void fillRect(int argc, char **argv) {
	if (argc < 6) {
		Serial.println("fillRect x, y, w, h, color1, [color2]");
		return;
	}

	String x = argv[1];
	String y = argv[2];
	String w = argv[3];
	String h = argv[4];
	String color1 = argv[5];

	if (argc > 6) {
		String color2 = argv[6];
		tft.fillRect(x.toInt(), y.toInt(), w.toInt(), h.toInt(), color1.toInt(), color2.toInt());
	}
	else {
		tft.fillRect(x.toInt(), y.toInt(), w.toInt(), h.toInt(), color1.toInt());
	}
}


void fillRoundRect(int argc, char **argv) {
	if (argc < 7) {
		Serial.println("fillRoundRect x, y, w, h, radius, color");
		return;
	}

	String x = argv[1];
	String y = argv[2];
	String w = argv[3];
	String h = argv[4];
	String radius = argv[5];
	String color = argv[6];

	tft.fillRoundRect(x.toInt(), y.toInt(), w.toInt(), h.toInt(), radius.toInt(), color.toInt());
}


void TFTProcessor::setup(Cmd *cmdSerial_) {
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
	cmdSerial->Add("drawRect", drawRect);
	cmdSerial->Add("drawRoundRect", drawRoundRect);
	cmdSerial->Add("fillRect", fillRect);
	cmdSerial->Add("fillRoundRect", fillRoundRect);

}


void TFTProcessor::loop() {

}