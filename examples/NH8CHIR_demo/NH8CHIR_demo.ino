#include <Wire.h>
#include <NH8CHIR.h>

NH8CHIR adc(0x49);                            //  Define sensor as adc on address 0x49

void setup()
{
  Serial.begin(115200);                       //  Use serial monitor on baud rate 115200
  adc.init();                                 //  Initialize NH8CHIR sensor on 0x49 address
}

void loop()
{
  
  for(int x = 0; x < 8; x++){                 //  Loop x from 1 to 7
    
    int read_value = adc.read(x, SD);         //  Define read_value variable as value from sensor by channel x
    Serial.print(read_value);                 //  Print value from sensor channel x to serial monitor
    Serial.print("  ");                       //  Print tab behind value
  }
  Serial.println();                           //  Break new line
  delay(10);                                  //  Delay for 10 miliseconds
}
