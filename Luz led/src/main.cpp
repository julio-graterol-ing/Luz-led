#include <Arduino.h>  //Required library for Arduino framework in PlatformIO

//Hardware pin assigment
const int PIN_POTENTIOMETER = A0; // Analog input pin for voltage reading 
const int PIN_LED = 9; // PWM output pin for brightness control

//Variables for analog conversion
int rawAnalogValue = 0; // Keeps track of the current LED state (ON/OFF)
int ledState = LOW; // Holds the raw reading from the potentiometer

// Asynchronous Timing Variables (Non-blocking)
unsigned long previousMillis = 0; // Stores the last time telemetry was sent
unsigned long blinkInterval = 500; // Dynamic variable for the blink speed

//SETUP: Runs once when the microcontroller starts or resets
void setup() {

  // Initialize communication for physical diagnostics telemetry
  Serial.begin(9600);

  // Pin peripherals configuration
  pinMode(PIN_LED, OUTPUT); // PWM pin set as output
  
}


void loop() {

  // 1. READ: Monitor the physical position of the knob (0 to 1023)
  rawAnalogValue = analogRead(PIN_POTENTIOMETER);

  // 2. PROCESS: Map the analog reading to a dynamic time interval (100ms to 2000ms)
  blinkInterval = map(rawAnalogValue, 0, 1023, 100, 2000);

  // 3. ASYNCHRONOUS ENGINE: Check if the dybamically calculated interval has passed
  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= blinkInterval) {
    //Save the timestamp of the next cycle
    previousMillis = currentMillis;

    //Toggle the LED state using bitwise or logical inversion
    if(ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    
  // Apply the new state to the physical hardware
  digitalWrite(PIN_LED, ledState);

    }

    //Telemetry: Print current status and interval speed in real-time
    Serial.print ("Potentiometer Raw: ");
    Serial.print(rawAnalogValue);
    Serial.print(" | Dynamic Blink Interval:");
    Serial.print(blinkInterval);
    Serial.println(" ms");

  

} 