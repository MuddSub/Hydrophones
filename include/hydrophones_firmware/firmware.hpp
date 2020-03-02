#ifndef HPHONES_FWARE
#define HPHONES_FWARE

#include <wiringPi.h>

class Hydrophones{

typedef unsigned short reg;

public:
	Hydrophones();
	
	char calcCRC(reg data);

};





#endif
