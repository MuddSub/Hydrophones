#include "hydrophones_firmware/firmware.hpp"
#include <bitset>
#include <time.h>
#include <chrono>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>


Hydrophones::Hydrophones(){


	stopAquisition();


	//Create directories for storing stuff
	std::string path = ros::package::getPath("hydrophones");
	int t = (int)ros::Time::now().toSec();
	std::string fullPath = path + "/samples";
	if (mkdir(path + (std::string)t, 0777) == -1)
		std::cerr << "Error :  " << strerror(errno) << std::endl;
	else
		std::cout << "Directory created";

	rawFilePath = path + (std::string)t+"/raw";
	processedFilePath = path + (std::string)t+"/processed";

	if (mkdir(processedFilePath, 0777) == -1)
        std::cerr << "Error :  " << strerror(errno) << std::endl;
  else
    std::cout << "Directory created";

	if (mkdir(rawFilePath, 0777) == -1)
    std::cerr << "Error :  " << strerror(errno) << std::endl;
  else
  	std::cout << "Directory created";



	//Disable CRC
	std::vector<word> data = {0xFD00, 0x0001, 0x3307};
	spiWrite(CRC_EN, data);



	//PLL CONFIG
	regSetRange(PLL_CTRL, 11, 15, 6); //pll_integer_div=6
	regSetRange(PLL_CTRL, 4, 7, 1);   //pll_input_prescale=1
	regSetBit(PLL_CTRL, 0, 1);      //enable pll


	regSetBit(CLK_CTRL, 0, 0);       //use pll clock

	//TODO: timeout
	while(!spiRead(PLL_LOCK))
		continue;


	//Power Enable
	regSetBit(POWER_ENABLE, 0, 0);   //Disable clock generator
	regSetBit(POWER_ENABLE, 1, 0);   //Disable Serial Output

	//Decimator set to 300kHz
	regSetRange(DECIM_RATE, 0, 2, 7);

	//High Pass Filter
	regSetRange(HIGH_PASS, 1, 5, 0b10010);  //HP shift value 18
	regSetBit(HIGH_PASS, 0, 1);

	//Configure output
	regSetBit(OUTPUT_MODE, 0, 1);   //parallel mode
	regSetBit(PARALLEL_MODE, 2, 1); //byte mode

	//Pullups/downs enabled
	regSetBit(SPI_CLK_PIN, 2, 1);
	regSetBit(MISO_PIN, 2, 1);
	regSetBit(MOSI_PIN, 2, 1);
	regSetBit(MISO_PIN, 2, 1);
	regSetBit(SCLK_ADC_PIN, 2, 1);
	regSetBit(CS_PIN, 2, 1);
	regSetBit(SS_PIN, 2, 1);
	regSetBit(FAULT_PIN, 2, 1);

	regSetBit(ADC_DOUT0_PIN, 2, 1);
	regSetBit(ADC_DOUT1_PIN, 2, 1);
	regSetBit(ADC_DOUT2_PIN, 2, 1);
	regSetBit(ADC_DOUT3_PIN, 2, 1);
	regSetBit(ADC_DOUT4_PIN, 2, 1);
	regSetBit(ADC_DOUT5_PIN, 2, 1);
	regSetBit(ADDR15_PIN, 2, 1);
	regSetBit(FS_ADC_PIN, 2, 1);


	//TODO: how does peak detect work?

	//ADC Settings
	regSetBit(ADC_SETTING1, 1, 1);
	regSetRange(ADC_SETTING2, 0, 4, 0b10011);
	regSetRange(ADC_SETTING3, 2, 3, 0);


	//Enable it
	regSetBit(MASTER_ENABLE, 0, 1);

	//check for error
	while(spiRead(ASIL_FLAG)){
		ROS_ERROR("ADAR7251 Error Code %d", spiRead(ASIL_ERROR));
		regSetBit(ASIL_CLEAR, 0, 1);
	}

	return;
}


Hydrophones::word Hydrophones::spiRead(word addr){
	unsigned char buffer[3];
	buffer[0] = addr15<<1; //set bit 1 to 1 or 0 accordingly, bit 0 is always 0
	buffer[1] = addr >> 8;     //shift to get only MSB
	buffer[2] = (addr & 0xFF); //mask MSB with zeros
	#if __aarch64__
	int err = wiringPiSPIDataRW(channel, buffer, 3);
	#endif
	word result = buffer[0];
	result |= (buffer[1] << 8);
	return result;
}

void Hydrophones::spiWrite(word addr, std::vector<word> data){
	unsigned char buffer[maxWrite*2 + 1];
	int len = 2*data.size() + 3;
	buffer[0] = 0x1 | (addr15 << 1); //Set address, then to write mode
	buffer[1] = addr >> 8;     //shift to get only MSB
	buffer[2] = (addr & 0xFF); //mask MSB with zeros
	for(int i = 0; i < data.size(); ++i){
		buffer[i+3] = data[i] >> 8;     //shift to get only MSB
		buffer[i+4] = (data[i] & 0xFF); //mask MSB with zeros
	}
	#if __aarch64__
	int err = wiringPiSPIDataRW(channel, buffer, len);
	#endif
}

void Hydrophones::spiWrite(word addr, word data){
	std::vector<word> v;
	v.push_back(data);
	spiWrite(addr, v);
}

void Hydrophones::setBit(word& data, int pos, bool value){
	word mask = (1 << pos);
	if(value == 1){
		data |= mask;
		return;
	}
	//invert the mask
	mask = ~mask;
	data &= mask;
}

void Hydrophones::setBits(word& data, word mask, bool value){
	if(value == 1){
		data |= mask;
		return;
	}
	mask = ~mask;
	data &= mask;
}

Hydrophones::word Hydrophones::regSetBit(word addr, int pos, bool value){
	word data = spiRead(addr);
	setBit(data, pos, value);
	spiWrite(addr,data);
	return data;
}

Hydrophones::word Hydrophones::regSetBits(word addr, word mask, bool value){
	word data = spiRead(addr);
	setBits(data, mask, value);
	spiWrite(addr,data);
	return data;
}

Hydrophones::word Hydrophones::regSetRange(word addr, int startPos, int endPos, word value){
	word data = spiRead(addr);

	//mask for setting zeros to ones
	word mask = value << startPos;

	data |= mask;

	//mask for setting ones to zeros needs padding of 1s on both sides of the value mask
	mask |= 0xFFFF << endPos | 0xFFFF >> (16-startPos);
	data &= mask;

	spiWrite(addr, data);

	return data;
}

void Hydrophones::sample(float secs){

	rawSamples = std::vector<raspiReg>();
	samplesProcessed = false;

	clock_t numTicks = secs * CLOCKS_PER_SEC;

	bool prevSclk = true;
	clock_t t = clock();
	startAquisition();
	while(!dataReady()) continue;
	//If needed: approximate clock cycles per loop, and just loop that many times
	bool sclk;
	do{
		sclk = clockState();
		if(!sclk && prevSclk){
			volatile raspiReg value = *RPI_GPILEV0;
			rawSamples.push_back(value);
		}
		prevSclk = sclk;
	}while(clock() - t < numTicks)

	sampling = false;

	//write to txt
	std::string path = rawFilePath + "/" + (std::string)sampleCounter;
	std::ofstream file;
	file.open(path);
	rawSampleFiles.push_back(path);
	for(auto i : rawSamples)
		file << i << std::endl;

	++sampleCounter;
}

void Hydrophones::processSamples(std::vector<raspiReg> rawSamples){
	//We need an even number of readings, since each measurement is two readings

	int len = rawSamples.size();

	if(rawSamples.size() % 2 == 1){
		--len;
		rawSamples.pop_back();
	}

	for(int i = 0; i < len/2; ++i){
		raspiReg highReg = rawSamples.at(2*i);
		raspiReg lowReg = rawSamples.at(2*i+1);

		uint8_t msb = getByteFromReg(highReg);
		uint8_t lsb = getByteFromReg(lowReg);

		//assemble the bits
		word sample = (msb << 8) | lsb;
		samples.push_back(sample);
	}

	//write to txt
	std::string path = processedFilePath + "/" + (std::string)sampleCounter;
	std::ofstream file;
	file.open(path);
	processedSampleFiles.push_back(path);
	for(auto i : samples)
		file << i << std::endl;
}

uint8_t Hydrophones::getByteFromReg(raspiReg reg){
	uint8_t result = 0;
	for(int i = 0; i < 8; ++i){
		int pos = dataPins[i];

		//wipe out all the bits but the one we care about
		raspiReg mask = (1 << pos);
		uint8_t bit= (mask & pos) >> pos;
		result |= (bit << i);
	}
	return result;
}

int main(){
	Hydrophones system;


	return 0;
}
