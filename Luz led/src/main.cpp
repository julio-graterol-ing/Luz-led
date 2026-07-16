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
 
  // 1. LETTER 'S' (Three short blinks)
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH); // Turn the LED ON
    delay(200);                 // Short duration (200 milliseconds)
    digitalWrite(ledPin, LOW);  // Turn the LED OFF
    delay(200);                 // OFF duration between blinks
  }


  delay(300); //Small pause between letters


  //2. LETTER 'O' (Three long blinks)
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH); // Turn the LED ON 
    delay(600);                 // Long duration (600 milliseconds)
    digitalWrite(ledPin, LOW);  // Turn the LED OFF
    delay(600);                 // OFF duration between blinks
  }


  delay(300); //Small pause between letters


  //3. LETTER 'S' (Three Short blinks)
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH); // Turn the LED ON
    delay(200);                 // short duration (200 milliseconds)
    digitalWrite(ledPin, LOW);  // Turn the LED OFF
    delay(200);                 // Off duration between blink
  }

  //4. LONG PAUSE: (Wait 3 seconds before repeating the distress signal )
  delay(3000);
  
} 