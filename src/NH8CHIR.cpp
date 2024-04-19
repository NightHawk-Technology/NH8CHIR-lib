#include "Arduino.h"
#include "NH8CHIR.h"
#include "Wire.h"

bool ads_vref_int_enabled = 0;
unsigned char channels[8] = {0x00, 0x40, 0x10, 0x50, 0x20, 0x60, 0x30, 0x70}; 

NH8CHIR::NH8CHIR(unsigned char _address){
  ads_address = _address;
}

void NH8CHIR::init(){
  Wire.begin();   // Initialize I2C Bus
}

void NH8CHIR::init(boolean _vref){
  Wire.begin();   // Initialize I2C Bus
  ads_vref_int_enabled = _vref;
}

unsigned int NH8CHIR::read(unsigned char channel, bool mode)
{
  unsigned char command = 0;
  unsigned int reading = 0;	
  
  command = channels[channel];
  
  if (mode){
    command = command ^ 0x80; 
  }
  if (ads_vref_int_enabled){ 
    command = command ^ 0x08; 
  }

  Wire.beginTransmission(ads_address);
  Wire.write(command); 
  Wire.endTransmission();	
  
  Wire.requestFrom(ads_address, 2);

  if(2 <= Wire.available()) 
  {
    reading = Wire.read();
    reading = reading << 8; 
    reading |= Wire.read(); 
  }
  return reading;		
}
