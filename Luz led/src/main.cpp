#include <Arduino.h>  //Required library for Arduino framework in PlatformIO

//Hardware pin assigment
const int PIN_POTENTIOMETER = A0; // Analog input pin for voltage reading 
const int PIN_LED = 9; // PWM output pin for brightness control

//Variables for analog conversion
int rawAnalogValue = 0; // Stores the raw 10 bit ADC value (0 to 1023)
int mappedBrightness = 0; //Store the scaled 8 bit PW; value (0 to 255)

// Non-blocking timer variables (Replacing delay)
unsigned long previousMillis = 0; // Stores the last time telemetry was sent
const unsigned long SERIAL_INTERVAL = 200; //Send data every 200 milliseconds


//SETUP: Runs once when the microcontroller starts or resets
void setup() {

  // Initialize communication for physical diagnostics telemetry
  Serial.begin(9600);

  // Pin peripherals configuration
  pinMode(PIN_LED, OUTPUT); // PWM pin set as output
  // Note: Analog pins configured with analogRead do not require pinMode setup
}


void loop() {

  // 1. READ: Read the raw Voltage physical State (0V = 0, 5V = 1023)
  rawAnalogValue = analogRead(PIN_POTENTIOMETER);

  // 2. PROCESS: Map 10 bit input scale (0-1023) to 8 bit PWM output scale (0-255)
  mappedBrightness = map(rawAnalogValue, 0, 1023, 0, 255);

  // 3. EXECUTE: Write the analog-like voltage variance to the BLUE LED
  analogWrite(PIN_LED, mappedBrightness);

  // 4. TELEMETRY: Non-Blocking time checker using millis()
  unsigned long currentMillis = millis(); // Grab current internal systen time

  // Check if 200ms have passed since the last print
  if (currentMillis - previousMillis >= SERIAL_INTERVAL) {
    //Save the timestamp of this execution
    previousMillis = currentMillis;

    //Send  perfomance diagnostic data to the screen
    Serial.print ("ADC Raw Output: ");
    Serial.print(rawAnalogValue);
    Serial.print(" | PWM Drive: ");
    Serial.println(mappedBrightness);

  }

} 