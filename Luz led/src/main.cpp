#include <Arduino.h>

//Hardware output pin definition
#define VOLTAGE_SOURCE_PIN 3

void setup() {
  //Configure the execution pin as a pure digital output
  pinMode(VOLTAGE_SOURCE_PIN, OUTPUT);

  //Force the pin to hold a constant high state steady 5V output
  digitalWrite(VOLTAGE_SOURCE_PIN, HIGH);

}

void loop() {
  //No execution changes needed inside the main loop for voltage calibration
}