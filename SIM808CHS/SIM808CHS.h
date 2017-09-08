	#ifndef SIM808CHS_h
#define SIM808CHS_h
#include "Arduino.h"
#include <SoftwareSerial.h>

#define	SIM800_RX 7
#define SIM800_TX 8



class SIM808CHS{
public:
	SIM808CHS(uint32_t baudrate);
	void setup();
	bool sendData(char * pluv, char * lev);
};

#endif
