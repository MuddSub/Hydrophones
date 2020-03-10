#ifndef HPHONES_FWARE
#define HPHONES_FWARE

#include <wiringPi.h>
#include <vector>
#include "hydrophones/regmap.hpp"

class Hydrophones{

typedef unsigned short word;

static const int channel = 0;
static const int addr15 = 0;

//max words we can write at once
static const int maxWrite = 4;

public:
	Hydrophones();

	//read/write to register map
	void spiWrite(word addr, word data);
	void spiWrite(word addr, std::vector<word> data);
	word spiRead(word addr);

	//read the given address, changes specified bits, then re-writes
	word regSetBit(word addr, int pos, bool value);
	word regSetBits(word addr, word mask, bool value);
	word regSetRange(word addr, int startPos, int endPos, word value);


private:
	bool spiErr;

	//given a word, set the given bit to the given value
	void setBit(word& data, int pos, bool value);
	//given a word and a mask, set the bits corresponding to 1s in the mask to value
	void setBits(word& data, word mask, bool value);

};




#endif
