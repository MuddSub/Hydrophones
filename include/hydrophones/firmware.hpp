#ifndef HPHONES_FWARE
#define HPHONES_FWARE

#include <wiringPi.h>
#include <vector>

class Hydrophones{

typedef unsigned short word;

static const int channel = 0;
static const int addr15 = 0;

//max words we can write at once
static const int maxWrite = 4;

public:
	Hydrophones();

	void spiWrite(word addr, word data);
	void spiWrite(word addr, std::vector<word> data);
	word spiRead(word addr);

	void setBit(word& data, int pos, bool value);

	void setBits(word& data, word mask, bool value);

private:
	bool spiErr;

};




#endif
