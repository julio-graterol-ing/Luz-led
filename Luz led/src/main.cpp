#include <Arduino.h>  //Required library for Arduino framework in PlatformIO

//Hardware definition: Built-in Led is connected to digital pin 12
const int ledPin = 13; 

//SETUP: Runs once when the microcontroller starts or resets
void setup() {
  // Configure the digital pin as an OUTPUT to send voltage to the LED
  pinMode(ledPin, OUTPUT);

  // START SERIAL COMMUNICATION: Set the speed to 9600 bits per second
  Serial.begin(9600);

}


void loop() {

  //Turn the LED ON and send a message to the computer screen
  digitalWrite(ledPin, HIGH);
  Serial.println("LED status: ON");
  delay(1000);

  //Turn the LED OFF and send a message to the computer screen
  digitalWrite(ledPin, LOW);
  Serial.println("LED status: OFF");
  delay(1000);
 
} 