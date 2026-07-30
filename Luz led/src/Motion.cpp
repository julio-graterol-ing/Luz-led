#include "Motion.h"

//Initialize default kinematic parameter via initialization list
ServoMotion::ServoMotion() : MOTION_INTERVAL(30) {
    currentPosition = 0;
    rotationDirection = 1;
    previousMotionMillis = 0;

}

// Lowlevel driver attachment
void ServoMotion::init() {
    actuator.attach(SERVO_PIN);
}

//Asynchronous position scheduler sweep
void ServoMotion::update(unsigned long currentMillis) {
    if (currentMillis - previousMotionMillis >= MOTION_INTERVAL) {
        previousMotionMillis = currentMillis;

        currentPosition += rotationDirection;
        if (currentPosition >= 180 || currentPosition <= 0) {
            rotationDirection = -rotationDirection;
        }
        actuator.write(currentPosition);
    }
}