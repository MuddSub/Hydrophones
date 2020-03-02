#include "hydrophones_firmware/firmware.hpp"
#include <bitset>

Hydrophones::Hydrophones(){
	return;
}

//translated from wikipedia python ex
char Hydrophones::calcCRC(reg data){
	int array[24];
	for(i = 0; i < 16; ++i)
		array[i] = (data >> i)&1;
	for(i = 16; i < 24; ++i)
		array[i] = 0;

	//x^16 + x^15 + x^12 + x^7 + x^6 + x^4 + x^3 + 1
	int polynomial[17] = {1,1,0,0,1,0,0,0,0,1,1,0,1,1,0,0,1};

	while(true){
		bool oneFound = false;
		for(auto i : array){
			if i != 0:
				oneFound = true;
				break;
		if(!oneFound) break;
		


	}

}



int main(){
	return 0;
}
