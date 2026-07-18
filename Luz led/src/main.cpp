#include <Arduino.h>  //Required library for Arduino framework in PlatformIO

//Hardware definition: Built-in Led is connected to digital pin 12
const int  PIN_RED = 13;
const int PIN_YELLOW = 12;
const int PIN_GREEN = 11; 


// Timing configuration in milliseconds
const unsigned long TIME_RED = 5000; // Red light duration
const unsigned long TIME_YELLOW = 2000; //Yellow light duration 
const unsigned long TIME_GREEN = 5000; // Green light duration 

//SETUP: Runs once when the microcontroller starts or resets
void setup() {
  // Configure the digital pin as an OUTPUT to send voltage to the LED
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);

  // START SERIAL COMMUNICATION: Set the speed to 9600 bits per second
  Serial.begin(9600);

}


void loop() {

  //STATE 1: Green light activate (Traffic flows)
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_RED, LOW);
  Serial.println("TRAFFIC LIGHT STATUS: GREEN - Go");
  delay(TIME_GREEN);
  
  //STATE 2: Yellow light active (Warning / Transition)
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_YELLOW, HIGH);
  digitalWrite(PIN_RED, LOW);
  Serial.println("TRAFFIC LIGHT STATUS: YELLOW - Warning");
  delay(TIME_YELLOW);

  //STATE 3: Red light activate (Traffic stops)
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_RED, HIGH);
  Serial.println("TRAFFIC LIGHT STATUS: RED - Stop");
  delay(TIME_RED);
  
} 