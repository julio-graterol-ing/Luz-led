#include <Arduino.h>
#include "Climate.h"
#include "Motion.h"
#include "DisplayCore.h"

//instantiate core system modular drivers
ClimateSensor climate;
ServoMotion motion;
DisplayCore displayModule;

void setup() {
  Serial.begin(9600);

  //Initialize all detached hardware subsystems
  climate.init();
  motion.init();
  displayModule.init();
}

void loop() {
  //Critical task high speed multiplexing refresh engine
  displayModule.refresh();

  unsigned long currentMillis = millis();

  //Process all asynchronous time sliced task in parallel
  climate.update(currentMillis);
  motion.update(currentMillis);

  //Fetch real time data using getter and update the graphics core
  displayModule.updateData(currentMillis, climate.getTemperature(), climate.getHumidity());
  
}