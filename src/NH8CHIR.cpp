#include "Arduino.h"
#include "NH8CHIR.h"
#include "Wire.h"

bool ads_vref_int_enabled = 0;  // default voltage reference is external

// command address for the channels, allows 0-7 channel mapping in the correct order
unsigned char channels[8] = {0x00, 0x40, 0x10, 0x50, 0x20, 0x60, 0x30, 0x70}; 

NH8CHIR::NH8CHIR(unsigned char _address){
  ads_address = _address;   // Set ADC i2c address to the one passed to the function
}

void NH8CHIR::init(){
  Wire.begin();   // Initialize I2C Bus
}

void NH8CHIR::init(boolean _vref){
  Wire.begin();   // Initialize I2C Bus
  ads_vref_int_enabled = _vref;  // Set vref trigger to specified value (Internal or external)
}

unsigned int NH8CHIR::read(unsigned char channel, bool mode)
{
  unsigned char command = 0;		// Initialize command variable
  unsigned int reading = 0;			// Initialize reading variable
  
  command = channels[channel];      // put required channel address in command variable
  
  if (mode){
    command = command ^ 0x80; 		// Enable Single-ended mode (toggle MSB, SD bit in datasheet)
  }
  if (ads_vref_int_enabled){ 
    command = command ^ 0x08; 	    // Enable internal voltage reference if ads_vref_int_enabled = 1
  }

  Wire.beginTransmission(ads_address); 	// Send a start or repeated start command with a slave address and the R/W bit set to '0' for writing.
  Wire.write(command);      			// Then send a command byte for the register to be read.
  Wire.endTransmission();				// Send stop command
  
  Wire.requestFrom(ads_address, 2);		// Request 2 bytes from the ADC

  if(2 <= Wire.available())    		// if two bytes were received
  {
    reading = Wire.read();     		// receive high byte
    reading = reading << 8;    		// shift high byte to be high 8 bits
    reading |= Wire.read();    		// receive low byte into lower 8 bits
  }
  return reading;					// return the full 12 bits reading from the ADC channel
}
