#include <Arduino.h>
#include <SevSeg.h>

SevSeg sevSeg;

//Non blocking animation timer variables
unsigned long previousAnimMillis = 0;
const unsigned long ANIMATION_INTERVAL = 800;

//System state machine varibles 
int currentStep = 0;

void setup() {
  Serial.begin(9600);

  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13}; //Official verified 5461AS layout
  byte segmentPins[] = { 2, 3, 4, 5, 6, 7, 8, 9};

  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = false; //Turn off leading zeros natively

  sevSeg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevSeg.setBrightness(90);

}

void loop() {
  //1. Refresh: Constantly drive the high speed multiplexing pins
  sevSeg.refreshDisplay();

  //2. Asynchronous animation engine: driven by system clock ticks
  unsigned long currentMillis = millis();
  if (currentMillis - previousAnimMillis >= ANIMATION_INTERVAL) {
    previousAnimMillis = currentMillis;

    //Custom state machine creating clean cascading effect 
    switch (currentStep) {
      case 0: 
        sevSeg.setChars("1   "); //Shows '1' in digit 1 rest is black
        break;
      case 1:
        sevSeg.setChars("12  "); // shows '1' and '2', rest black
        break;
      case 2:
        sevSeg.setChars("123  "); //Shows '1', '2', '3'
        break;
      case 3:
        sevSeg.setChars("1234"); //full alignment completed
        break;
      
        case 4: // total blackout phase
        sevSeg.blank();
        break;

      case 5: 
        sevSeg.setChars("5   "); 
        break;
      case 6:
        sevSeg.setChars("56  "); 
        break;
      case 7:
        sevSeg.setChars("567  "); 
        break;
      case 8:
      sevSeg.setChars("5678");
      break;

    }
    //Cycle counter (0 to 9)
    currentStep = (currentStep + 1) % 10;

  }
}
