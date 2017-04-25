## Arduino USB PPM and Monitor Hardware Interface

This project is intended as an interface between a Serial Port USB and TFT320x240 and PPM for easily connecting companion computers to APM.

It enables a client to draw and write on an attached LCD screen and change PPM values, its designed to be fast and reliable and with a failsafe on the PPM output so if the USB was disconnected or the software did not send a timely update to any PPM channel, it will switch to a preset failsafe.
Ofcurse if the module lost power, the APM should enter failsafe as well.

**THIS PROJECT IS EXPERIMENTAL AND UNTESTED AND INTENDED ONLY FOR EDUCATIONAL PURPOSES** 

This project uses the following dependencies:
- ArduinoRCLib by Daniel van den Ouden http://sourceforge.net/p/arduinorclib/
- TFT_ILI93XX by Max MC Costa, forked here https://github.com/drorgl/TFT_ILI93XX
- CmdArduino by Akiba, forked and rebuilt by me here https://github.com/drorgl/CmdArduino

