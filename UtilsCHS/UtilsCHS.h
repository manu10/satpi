#ifndef UtilsCHS_h
#define UtilsCHS_h
#define DEBUGU
#define TESTBUFF_U
#include "Arduino.h"

#define TIME 5000000
//El ultimo test indico que no se usan mas de 180 Bytes
#define BUFFER_SIZE 200
#define DEBUG 1

class UtilsCHS{
public:
	static char * readBuffer(Stream *printer,char * cond1, char * cond2, signed long timeout, int * result);
};

#endif
