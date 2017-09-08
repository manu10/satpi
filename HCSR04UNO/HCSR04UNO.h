#ifndef HCSR04UNO_h
#define HCSR04UNO_h
#include "Arduino.h"
#define DEBUGS
#define imprimir(fd,x) for(indS = 0; indS < strlen_P(x); indS++){miCharS = pgm_read_byte_near(x + indS);fd.print(miCharS);}
#ifdef DEBUGS
#define HCSR04UNO_debug(fd,x) for(indS = 0; indS < strlen_P(x); indS++){miCharS = pgm_read_byte_near(x + indS);fd.print(miCharS);}
#else
#define HCSR04UNO_debug(fd,x)
#endif

#define	TRIGGER 9
#define ECHO 10



class HCSR04UNO{
public:
	int indS;char miCharS;
	void setup();
	float getDist();
};

#endif
