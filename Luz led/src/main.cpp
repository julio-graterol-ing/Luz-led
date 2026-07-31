#include <Arduino.h>

void setup() {
  // Esp32 telemetry requires a hig speed baud rate
  Serial.begin(115200);

  //Print micro architecture specification on boot
  Serial.println("==========================================");
  Serial.println("   ESP32 32 BIT ARCHITECTURE INITIALIZED  ");
  Serial.println("==========================================");

  //Fetch and display CPU current clock speed (Should print 240 MHz)
  Serial.print("[STATUS] CPU Clock Frequency: ");
  Serial.print(getCpuFrequencyMhz());
  Serial.println ("MHz");

}

void loop() {
  // Asynchronous message loop to test execution ticks
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000) {
    previousMillis = currentMillis;
    Serial.println("[HEADBEAT] 32 bit Concurrent loop running active");
  }
}