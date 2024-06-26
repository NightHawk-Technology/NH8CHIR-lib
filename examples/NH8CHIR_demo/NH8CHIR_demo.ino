#include <Wire.h>
#include <NH8CHIR.h>

NH8CHIR adc(0x49);

void setup()
{
  Serial.begin(115200);
  adc.init();
}

void loop()
{
  
  for(int x = 0; x < 8; x++){
    
    int read_value = adc.read(x, SD);
    Serial.print("Channel ");
    Serial.print(x);
    Serial.print(": ");
    Serial.print(read_value);
  }
  delay(10);
}
