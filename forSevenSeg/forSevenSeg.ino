#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object

void setup() {

byte numDigits = 4;

byte digitPins[] = {2, 3, 4, 5};

byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);

sevseg.setBrightness(90);

sevseg.setNumber(1341, 3);

}

void loop() {

sevseg.refreshDisplay(); // Must run repeatedly

}
