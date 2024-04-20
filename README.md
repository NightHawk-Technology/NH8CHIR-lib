## NH8CHIR Library
### current version `` 1.1.0 ``
<hr>

## Documentation

### Basic usage

```
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
    
    read_value = adc.read(x, SD);
    Serial.print("Channel ");
    Serial.print(x);
    Serial.print(": ");
    Serial.print(read_value);
  }
  delay(10);
}
```
<hr>

### IRCalibration
```
#include <Wire.h>
#include <NH8CHIR.h>

NH8CHIR front(0x49);

int front_sensorMin[8] = { 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095 };
int front_sensorMax[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int front_sensorMid[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

unsigned long calibrationStartTime;
const unsigned long calibrationDuration = 5000;

// Check is Black
bool b(int pin) {
  int value = front.read(pin, SD);
  if (value < front_sensorMid[pin]) { return false; }
  if (value > front_sensorMid[pin]) { return true; }
}

void setup(){
  IRCalibrate();
}

void loop(){

}

void sensorCal(int pin) {
  int value = front.read(pin, SD);
  if (value < front_sensorMin[pin]) {
    front_sensorMin[pin] = value;
  }
  if (value > front_sensorMax[pin]) {
    front_sensorMax[pin] = value;
  }
}

void calculateMidpoint() {
  for (int x = 0; x < 8; x++) {
    front_sensorMid[x] = (front_sensorMax[x] + front_sensorMin[x]) / 2;
  }
}

void IRCalibrate() {
  calibrationStartTime = millis();
  while (millis() - calibrationStartTime < calibrationDuration) {
    for (int x = 0; x < 8; x++) {
      sensorCal(x);
    }
  }
  calculateMidpoint();
}


```
