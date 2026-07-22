#include <Arduino.h> //Required library for Arduino framework in PlatformIO
#include <Servo.h> // Native library for hardware servo control

// Hardware pin assigment
const int PIN_POTENTIOMETER = A0; // Analog input for position control
const int PIN_SERVO = 9;    // PWM output to drive the servo motor

//Instantiate the hardware servo driver objects
Servo myServo;


// System State Variables
int rawAnalogValue = 0; //Stores raw data from the knob (0 to 1023)
int targetAngle = 0; //Store calculated mechanical angle (0 to 1023)

// Non blocking Telemetry Timer Variables
unsigned long previousMillis = 0;         // Stores the last time telemetry was sent
const unsigned long SERVO_TELEMETRY_INTERVAL = 200;  // Update print screen every 200ms

// SETUP: Runs once when the microcontroller starts or resets
void setup()
{

  // Initialize communication for physical diagnostics telemetry
  Serial.begin(9600);

  //Attach the servo object to its physical digital control pin
  myServo.attach(PIN_SERVO);
}

void loop()
{

  //1. Read: Capture the real time position of the potentiometer knob
  rawAnalogValue = analogRead(PIN_POTENTIOMETER);

  //2. Process: Map 10 bit input scale (0-1023) to mechanical angle limits (0-180)
  targetAngle = map(rawAnalogValue, 0, 1023, 0, 180);

  //3. Execute: Transmit the target angle comand to the motor driver hardware
  myServo.write(targetAngle);

  //4. Telemetry: Non blocking time checker using the system clock
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= SERVO_TELEMETRY_INTERVAL) {
  previousMillis = currentMillis;

  // Send mechanical diagnostics data to the computer monitor screen
  Serial.print("Potentiometer Input: ");
  Serial.print(rawAnalogValue);
  Serial.print(" | Actuator Angle Command: ");
  Serial.print(targetAngle);
  Serial.println(" deg");

}

}
