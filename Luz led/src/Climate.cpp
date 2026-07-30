#include "Climate.h"

//Constructor list initialization for constant values
ClimateSensor::ClimateSensor() : dht(DHTPIN, DHTTYPE), DHT_INTERVAL(2000) {
    currentTemperature = 0;
    currentHumidity = 0;
    previousDHTMillis = 0;
}

//low level hardware sensor activation
void ClimateSensor::init() {
    dht.begin();
}

//Asynchronous background processor using millis
void ClimateSensor::update(unsigned long currentMillis) {
    if (currentMillis - previousDHTMillis >= DHT_INTERVAL) {
        previousDHTMillis = currentMillis;

        float t = dht.readTemperature();
        float h = dht.readHumidity();

        //safety guard check before changing data registers
        if (!isnan(t) && !isnan(h)) {
            currentTemperature = (int)t;
            currentHumidity = (int)h;
        }
    }
}

int ClimateSensor::getTemperature() const {
    return currentTemperature;
}

int ClimateSensor::getHumidity() const {
    return currentHumidity;
}