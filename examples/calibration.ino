#include <NH8CHIR.h>

NH8CHIR adc(0x49);

int sensorMin[8] = { 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095 };
int sensorMax[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int sensorMid[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

unsigned long calibrationStartTime;
const unsigned long calibrationDuration = 5000;

int bwCal(int pin) {
  int value = adc.read(pin, SD);
  if (value < sensorMid[pin]) { return 0; }
  if (value > sensorMid[pin]) { return 1; }
}

void setup() {
  IRCalibrate();
}

void loop() {

}

void sensorCal(int pin) {
  int value = adc.read(pin, SD);
  if (value < sensorMin[pin]) {
    sensorMin[pin] = value;
  }
  if (value > sensorMax[pin]) {
    sensorMax[pin] = value;
  }
}

void IRCalibrate() {
  calibrationStartTime = millis();
  while (millis() - calibrationStartTime < calibrationDuration) {
    for (int x = 0; x < 8; x++) {
      sensorCal(x);
    }
  }
  for (int x = 0; x < 8; x++) {
    sensorMid[x] = (sensorMax[x] + sensorMin[x]) / 2;
  }
}
