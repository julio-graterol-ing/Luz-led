#include <Arduino.h>  //Required library for Arduino framework in PlatformIO

//Hardware pin assigment
const int  PIN_BUTTON = 2; //Digital input connected to the button push circuit 
const int PIN_LED = 13; //Digital output connected to the target feedback LED

//Varibles to Store system state
int buttonState = 0; // Variable to hold the real-time electrical reading

//SETUP: Runs once when the microcontroller starts or resets
void setup() {

  // Initialize communication for physical diagnostics telemetry
  Serial.begin(9600);

  // Pin peripherals configuration
  pinMode(PIN_BUTTON, INPUT); //Configure as input to read external voltage status
  pinMode(PIN_LED, OUTPUT); // Configured as output to control the LED drive

}


void loop() {

  //Read the electrical digital state of pin 2(HIGH or LOW)
  buttonState = digitalRead(PIN_BUTTON);

  //Conditional logic engine evaluating the physical state
  if (buttonState == HIGH) {
    //If the button is pressed (5V is present at the pin)
    digitalWrite(PIN_LED, HIGH);
    Serial.println("INPUT DETECTED: Button pressed -> LED activated.");
  }  else { 
    //If the button is released (Pulled down to 0V ground)
    digitalWrite(PIN_LED, LOW);
  
  }

  // Small delay to prevent telemetry buffer overflow on the Serial Monitor
  delay(50);

} 