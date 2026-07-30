#include "DisplayCore.h"

//Setup data toggler boundaries and variables
DisplayCore::DisplayCore() : TOGGLE_INTERVAL(3000) {
    displayState = 0;
    previousToggleMillis = 0;

}

//inject physical geometry and pinout configuration for 5461AS
void DisplayCore::init() {
    byte numDigits = 4;
    byte digitPins[] = {10, 11, 12, 13};
    byte segmentsPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
    bool resistorsOnSegments = true;
    byte hardwareConfig = COMMON_CATHODE;
    bool updateWithDelays = false;
    bool leadinZeros = false;

    sevSeg.begin(hardwareConfig, numDigits, digitPins, segmentsPins, resistorsOnSegments, updateWithDelays, leadinZeros);
    sevSeg.setBrightness(90);
}

//High speed refre gate called every loop iteration
void DisplayCore::refresh() {
    sevSeg.refreshDisplay();
}

//State machone switcher for formatting string streams
void DisplayCore::updateData(unsigned long currentMillis, int temp, int hum) {
    if (currentMillis - previousToggleMillis >= TOGGLE_INTERVAL) {
        previousToggleMillis = currentMillis;
        displayState = (displayState +1) % 2; 
    }
    if (displayState == 0) {
        char tempBuffer[6];
        sprintf(tempBuffer, "t%3d", temp);
        sevSeg.setChars(tempBuffer);

    }else{
        char humBuffer[6];
        sprintf(humBuffer, "h%3d", hum);
        sevSeg.setChars(humBuffer);
    }
}