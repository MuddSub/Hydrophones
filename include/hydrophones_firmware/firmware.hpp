#ifndef HPHONES_FWARE
#define HPHONES_FWARE

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <vector>
#include "ros/ros.h"
#include "ros/package.h"
#include "hydrophones/regmap.hpp"

class Hydrophones{



typedef uint16_t word;
typedef uint32_t raspiReg;

static const int channel = 0;
static const char addr15 = 0;

//max words we can write at once
static const int maxWrite = 4;

public:
	Hydrophones();



	// ------- SPI Interface: -------
	//read/write to register map
	void spiWrite(word addr, word data);
	void spiWrite(word addr, std::vector<word> data);
	word spiRead(word addr);

	//read the given address, changes specified bits, then re-writes
	word regSetBit(word addr, int pos, bool value);
	word regSetBits(word addr, word mask, bool value);
	word regSetRange(word addr, int startPos, int endPos, word value);


	// ------- Sampling -------
	void sample(float secs);
	void processSamples();

private:
	bool spiErr;

	//given a word, set the given bit to the given value
	void setBit(word& data, int pos, bool value);
	//given a word and a mask, set the bits corresponding to 1s in the mask to value
	void setBits(word& data, word mask, bool value);

	bool aquiring = false;
	inline void startAquisition(){
		digitalWrite(RPI_N_CONV_START_PIN, LOW);
		aquiring = true;
	}
	inline void stopAquisition(){
		digitalWrite(RPI_N_CONV_START_PIN, HIGH);
		aquiring = false;
	}

	inline bool dataReady(){return digitalRead(RPI_DATA_READY_PIN);}
	inline bool clockState(){return digitalRead(RPI_SCLK_ADC_PIN);}

	std::vector<raspiReg> rawSamples;
	std::vector<word> samples;
	bool samplesProcessed = false;
	std::vector<std::string> rawSampleFiles;
	std::vector<std::string> processedSampleFiles;

	std::string rawFilePath;
	std::string processedFilePath;

	unsigned int sampleCounter = 0;

	uint8_t getByteFromReg(raspiReg reg);


	unsigned int dataPins[8] = {DIN_PIN_0, DIN_PIN_1, DIN_PIN_2, DIN_PIN_3,
	                            DIN_PIN_4, DIN_PIN_5, DIN_PIN_6, DIN_PIN_7};

};




#endif
