#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object
void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  Serial.begin(9600);
  
   sevseg.setNumber(3141,3);
    sevseg.refreshDisplay(); // Must run repeatedly
    //
}

void loop() {
  /*for(int i=0;i<10;i++) {
    String aa = String(i)+String(i)+String(i)+String(i);
    Serial.println(aa);
    sevseg.setNumber(1111, 3);
    sevseg.refreshDisplay(); // Must run repeatedly
    
  }*/
}
