#include <Arduino.h> //Required library for Arduino framework in PlatformIO
#include <DHT.h> // offical Adafruit for enviromental climate sensitive

//Hardware Pin and Sensor Type Configuration
const int PIN_DHT = 2; // Digital pin connected to the DHT11 data line
#define DHTTYPE DHT11 //Define the specific sensor hardware type

// Instatiate the enviromental sensor driver object
DHT dht(PIN_DHT, DHTTYPE);

//System State Variables
float temperatureC = 0.0; //Store the calculated temperature in celsius
float humidityPct = 0.0; //Store the calculated relative humidity percentage

//Non-Blocking Telemetry Timer Variables
unsigned long previousClimateMillis = 0;
const unsigned long CLIMATE_INTERVAL = 2000; //DHT11 sensor requires at least 2 seconds between reads

void setup() {
  // Initialize communication for physical diagnostic logs
  Serial.begin(9600);

  //Initialize the physical internal registers of the DHT sensor
  dht.begin();

}

void loop() {

  //Non blocking execution time checker using the system clock
  unsigned long currentMillis = millis();

  if (currentMillis - previousClimateMillis >= CLIMATE_INTERVAL) {
    previousClimateMillis = currentMillis;

    //1. Read: Capture raw digital streams and convert to floating point metrics
    humidityPct = dht.readHumidity();
    temperatureC = dht.readTemperature();

    //2. Error Checking: Validate if the data received from the hardware is valid
     if (isnan(humidityPct) || isnan (temperatureC)) {
      Serial.println("CRITICAL ERROR:Failed to read from DHT sensor Hardware");
      return; // Exit this cycle immediately to prevent bad telemetry output
     }

     //3. Telemetry Output: Transmit Performance data to the monitor screen
     Serial.print("CLIMATE DATA | Humidity: ");
     Serial.print(humidityPct);
     Serial.print("% | Temperature: ");
     Serial.print(temperatureC);
     Serial.println("*C");
     }
  
  }

