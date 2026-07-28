#include <Arduino.h>
#include <DHT.h>
#include <Servo.h>
#include <SevSeg.h>

//Hardware Pinout configuration Collision free mapping 
#define DHTPIN A4 //DHT11 sensor connected to analog pin A4
#define DHTTYPE DHT11
#define SERVO_PIN A0 // Servo signal (orange wire) connected to analog pin A0

//Hardware Driver instantiation
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;
SevSeg sevSeg;

//Global telemetry registers (SRAM memory optimized)
int currentTemperature = 0;
int currentHumidity = 0;
int servoPosition = 0;
int servoDirection = 1;

//Asynchronous system clock (time frontiers driven by millis)
unsigned long previousDHTMillis = 0;
unsigned long previousServoMillis = 0;
unsigned long previousDisplayToggleMillis = 0;

//Critical execution Intervals (time slicing windows)
const unsigned long DHT_INTERVAL = 2000; // DHT11 requires 2s cycles to avoid silicon saturation
const unsigned long SERVO_INTERVAL = 30; // Incremental step every 30ms for smooth mechanical sweeping
const unsigned long TOGGLE_INTERVAL = 3000; // Data alternation frequency 3 seconds

//Screen state machine variable (0 = Temperature, 1 = Humidity)
int displayState = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  myServo.attach(SERVO_PIN);

  //Physical layout calibration for 5461AS common cathode model
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13}; // direct control lines 
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; //Data bus lines (8 individual 220 resistors intercalated)

  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;

  // Inject geometric parameter into the library engine
  sevSeg.begin(hardwareConfig,numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevSeg.setBrightness(90);
}

void loop(){
  //Critical Refres task: driven directly every single clock cycle to maintain multiplexing stability
  sevSeg.refreshDisplay();

  unsigned long currentMillis = millis();

  //Task 1: Asynchronous climate telemetry acquisition every 2000ms
  if (currentMillis - previousDHTMillis >= DHT_INTERVAL) {
    previousDHTMillis = currentMillis;
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    //Validate register data integrity before overwriting
    if (!isnan(t) && !isnan(h)) {
      currentTemperature = (int)t;
      currentHumidity = (int)h;
    }
  }

  //Task 2: kinematic control loop for the servo actuatuor every 30ms
  if (currentMillis - previousServoMillis >= SERVO_INTERVAL) {
    previousServoMillis = currentMillis;
    servoPosition += servoDirection;

    //Invert rotation direction at mechanical bounds
    if (servoPosition >= 180 || servoPosition <= 0) {
      servoDirection = -servoDirection;

    }
    myServo.write(servoPosition);
  }
  
  //Task 3: Screen Display toggler every 3000ms
  if (currentMillis - previousDisplayToggleMillis >= TOGGLE_INTERVAL) {
    previousDisplayToggleMillis = currentMillis;
    displayState = (displayState + 1) % 2;

  }

// Task 4: dynamic buffer formatting rendering on 5461AS
// Strict 6 byte allocation sizing to guarantee protection against buffer overflow
 if (displayState == 0) {
  char tempBuffer[6];
  //format temperature string with black padding ("t 26")
  sprintf(tempBuffer, "t%3d", currentTemperature);
  sevSeg.setChars(tempBuffer);
 } else {
  char humBuffer[6];
  // format humidity string with blank padding ("h 50")
  sprintf(humBuffer, "h%3d", currentHumidity);
  sevSeg.setChars(humBuffer);
 }
}