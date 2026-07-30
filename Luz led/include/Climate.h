#ifndef CLIMATE_H
#define CLIMATE_H

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN A4
#define DHTTYPE DHT11

class ClimateSensor {
    private:
        DHT dht;
        int currentTemperature;
        int currentHumidity;
        unsigned long previousDHTMillis;
        const unsigned long DHT_INTERVAL;

    public:
        ClimateSensor(); //Constructor
        void init(); //Call dht.begin() inside
        void update(unsigned long currentMillis); //Implement the millis logic
        int getTemperature() const; //Return temperature
        int getHumidity() const; //Return humidity
};

#endif 