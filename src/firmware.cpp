#include "hydrophones_firmware/firmware.hpp"
#include <bitset>

Hydrophones::Hydrophones(){
	return;
}


word Hydrophones::spiRead(word addr){
	unsigned char* buffer[3];
	buffer[0] = addr15*2; //set bit 1 to 1 or 0 accordingly, bit 0 is always 0
	buffer[1] = addr >> 8;     //shift to get only MSB
	buffer[2] = (addr & 0xFF); //mask MSB with zeros
	int err = wiringPiSPIDataRW(channel, buffer, 3);
	word result = buffer[0];
	result |= (buffer[1] << 8);
	return result;
}

void Hydrophones::spiWrite(word addr, std::vector<word> data){
	unsigned char* buffer[maxWrite*2 + 1];
	int len = 2*data.size() + 3;
	buffer[0] = 0x1;
	buffer[1] = addr >> 8;     //shift to get only MSB
	buffer[2] = (addr & 0xFF); //mask MSB with zeros
	for(int i = 0; i < data.size(); ++i){
		buffer[i+3] = data[i] >> 8;     //shift to get only MSB
		buffer[i+4] = (data[i] & 0xFF); //mask MSB with zeros
	}
	int err = wiringPiSPIDataRW(channel, buffer, len);
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


int main(){
	return 0;
}
