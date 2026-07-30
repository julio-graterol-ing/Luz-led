#ifndef DISPLAYCORE_H
#define DISPLAYCORE_H

#include <Arduino.h>
#include <SevSeg.h>

class DisplayCore {
    private:
        SevSeg sevSeg;
        unsigned long previousToggleMillis;
        const unsigned long TOGGLE_INTERVAL;
        int displayState;

    public:
        // constructor and core control routines
        DisplayCore();
        void init();
        void refresh();
        void updateData(unsigned long currentMillis, int temp, int hum);

};

#endif 