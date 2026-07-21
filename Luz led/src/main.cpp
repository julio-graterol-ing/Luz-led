#include <Arduino.h> //Required library for Arduino framework in PlatformIO
#include <NewPing.h> // Professional non Blocking ultrasonic library

// Hardware pin assigment
const int PIN_TRIGGER = 12; // Outbound ultrasonic pulse pin
const int PIN_ECHO = 11;    // Inbound ultrasonic return pin
const int PIN_LED = 13;     // Proximity alert indicator LED

// Maximum distance we want to ping for (in centimeters). Macimum sensor limit is 400-500cm
const int MAX_DISTANCE = 200;

// NewPing instance setup using our hardware configuration
NewPing sonar(PIN_TRIGGER, PIN_ECHO, MAX_DISTANCE);

// System State Variables
unsigned int distanceCm = 0; // Stores the real time distance in centimeters

// Non blocking Telemetry Timer Variables
unsigned long previousMillis = 0;         // Stores the last time telemetry was sent
const unsigned long RADAR_INTERVAL = 150; // Sample and print distance

// SETUP: Runs once when the microcontroller starts or resets
void setup()
{

  // Initialize communication for physical diagnostics telemetry
  Serial.begin(9600);

  // Pin peripherals configuration
  pinMode(PIN_LED, OUTPUT); // PWM pin set as output
}

void loop()
{

  // Non blocking execution time checker
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= RADAR_INTERVAL)
  {
    previousMillis = currentMillis;

    // 1. Read & Process: Send a ping, get return time and convert directly to centimeters
    distanceCm = sonar.ping_cm();

    // 2. Conditional Logic: Evaluate proximity thresholds
    // If an object is detected closer than 15 centimeters (ignoring 0 wich means out og range)
    if (distanceCm < 15 && distanceCm > 0)
    {
      digitalWrite(PIN_LED, HIGH); // Activate visual ganger alert
      Serial.print("WARNING! Object detected at: ");
    }
    else
    {
      digitalWrite(PIN_LED, LOW); // Clear visual alert
      Serial.print("Safe zone. Distance: ");
    }

    // 3.Telemetry Output: Print the final engineering values
    if (distanceCm == 0)
    {
      Serial.println("Out of range or no obstacle");
    }
    else
    {
      Serial.print(distanceCm);
      Serial.println(" cm");
    }
  }
}
