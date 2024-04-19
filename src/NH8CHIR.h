#ifndef NH8CHIR_H
#define NH8CHIR_H

#include "Arduino.h"
#include <Wire.h>

#define EXT 0
#define INT 1

#define SD 1
#define DF 0


class NH8CHIR 
{  


public:
	NH8CHIR(unsigned char _address);
	void init();
	void init(boolean _vref);
	unsigned int read(unsigned char channel, bool mode);

private:
    int ads_address;
	
};


#endif
