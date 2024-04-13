#ifndef NH8CHIR_H
#define NH8CHIR_H

#include "Arduino.h"
#include <Wire.h>

#define EXT 0 // External VREF
#define INT 1 // Internal VREF

#define SD 1 // Single ended mode
#define DF 0 // Differential mode


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
