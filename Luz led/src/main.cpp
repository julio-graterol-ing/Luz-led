#include <Arduino.h>  //Required library for Arduino framework in PlatformIO

//Hardware definition: Built-in Led is connected to digital pin 13
const int ledPin = 13; 

//SETUP: Runs once when the microcontroller starts or resets
void setup() {
  // Configure the digital pin as an OUTPUT to send voltage to the LED
  pinMode(ledPin, OUTPUT);
}

//LOOP: Runs continuously in an infinite cycle
void loop() {
  digitalWrite (ledPin, HIGH); // Turn the LED ON (set pin to 5V)
  delay(1000);               // Wait for 1 second (1000 milliseconds)

  digitalWrite (ledPin, LOW); // Turn the LED OFF (set pin to 0V)
  delay(1000);               // Wait for 1 second (1000 milliseconds)

} 