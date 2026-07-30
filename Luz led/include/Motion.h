#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include <Servo.h>

// Hardware pinout configuration for the actuator
#define SERVO_PIN A0

class ServoMotion {
    private:
        Servo actuator; //Private instance of the servo driver
        int currentPosition; //Stores the current physical anle 0-180
        int rotationDirection; //Directionvector: 1 for clockwise, -1 for counter clockwise
        unsigned long previousMotionMillis;
        const unsigned long MOTION_INTERVAL;

    public:
        ServoMotion(); //constructor definition
        
        //Core system methods
        void init();
        void update(unsigned long currentMillis);
        
};

#endif 