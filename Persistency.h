// Persistency.h

#ifndef _PERSISTENCY_h
#define _PERSISTENCY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <EEPROM.h>

template <typename T>
class Persistency {
public:
	Persistency() {
	}
	void save(uint8_t version, uint8_t offset, T *obj) {
		auto len = sizeof(T);
		eeprom_update_byte(0, version);
		eeprom_update_block(obj, 1 + offset, len);
	}

	void load(uint8_t version, uint8_t offset, T *obj) {
		auto eever = eeprom_read_byte(0);
		if (eever != version) {
			return;
		}
		auto len = sizeof(T);
		eeprom_read_block(1 + offset, obj, len);
	}
};


#endif

