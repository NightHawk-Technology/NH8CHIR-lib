#include <Wire.h>                     // Include Wire.h for I2C functionality
#include <NH8CHIR.h>                  // Include ADS7828.h for TI ADS7828 functions

NH8CHIR adc(0x49);                    // Set the ADS7828 i2c address to 0x49 (A0 connected to ground, A1 connected to 5v)


void setup()
{
  Serial.begin(115200);                 // Start Serial 
  Serial.println("Sketch begin");     // Print begin message
  adc.init();                         // Initialize ADC in external reference mode and initialize the i2c bus
}

void loop()
{
  
  for(int x = 0; x < 8; x++){                     // Loops from 0 to 7
    
    read_value = adc.read(x, SD);                 // Read value of ADC channel x (0 to 7) in Single-ended mode
    voltage = read_value * (vref / 4095.0);       // Calculate voltage output value according to the voltage reference and resolution
    
    Serial.print("Channel ");                 // Prints...
    Serial.print(x);                          // Prints channel number
    Serial.print(": ");                       // Prints...
    Serial.print(read_value);                 // Prints value read from ADC
  }
  delay(1000);                           // Wait for 1 second
}



