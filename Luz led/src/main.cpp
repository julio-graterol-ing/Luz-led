#include <Arduino.h> //Required library for Arduino framework in PlatformIO
#include <LiquidCrystal.h> // Native Library for parallel LCD Charter display
#include <DHT.h> // offical Adafruit for enviromental climate sensitive

//Hardware Pin Assignment for Parallel LCD Interface (RS, E, D4,D5, D6, D7)
const int PIN_RS = 12;
const int PIN_E = 11;
const int PIN_D4 = 5;
const int PIN_D5 = 4;
const int PIN_D6 = 3;
const int PIN_D7 = 2;


//Hardware Pin and Sensor Type Configuration
const int PIN_DHT = 6; // Digital pin connected to the DHT11 data line
#define DHTTYPE DHT11 //Define the specific sensor hardware type

// Instatiate the enviromental sensor driver object
LiquidCrystal lcd(PIN_RS, PIN_E, PIN_D4, PIN_D5, PIN_D6, PIN_D7);
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

  //Initialize the physical geometry of the screen (16 columns and 2 rows)
  lcd.begin(16, 2);

  //Initialize the physical internal registers of the DHT sensor
  dht.begin();

  //Print an introductory message on the physical matrix screen
  lcd.print("System Booting..."); 

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
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HARDWARE ERROR");
      Serial.println("CRITICAL ERROR:Failed to read from DHT sensor Hardware");
      return; // Exit this cycle immediately to prevent bad telemetry output
     }

     //3. Physical interactive Output: Display metrics on the phisical LCD panel
     lcd.clear(); // Wipe rows to prevent trailing character ghosting artifacts

     //Line 1 configuration: Temperature drive output
     lcd.setCursor(0, 0);
     lcd.print("Temp: ");
     lcd.print(temperatureC);
     lcd.print(" C");

     //Line 2 configuration: Humidity drive output
     lcd.setCursor(0, 1); // Move data block to column 0, row 1 (second line)
     lcd.print("Humid: ");
     lcd.print(humidityPct);
     lcd.print(" %");

     //Parallel background diagnostic feeback for the PC screen
     Serial.println("LCD interface succesfully refreshed with fres variables");
     }
  
  }

