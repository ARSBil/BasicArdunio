#include <SevSeg.h>



/*
Author: Danny van den Brande, arduinosensors.nl. BlueCore Tech.
This code is written for the AT24C32/DS1307 RTC Module and 
4 digit Seven Segment displays. 
Be sure to check if you have a common anode or cathode display.(change @ line 26)
 */
//#include "Wire.h"
 
#define DS1307_ADDRESS 0x68
 
//Create an instance
SevSeg display7seg;
 
int valor = 0;
 
byte zero = 0x00; 
unsigned long timer;
void setup()
{
  //Wire.begin();
  //Comment this line after you have set the date @ void TimeSelection() below
//   TimeSelection(); Uncomment this line when your setting the time. Set time @ (line 66)
  
  //Change to COMMON_ANODE if you have a Common anode display.
  int displayType = COMMON_CATHODE; 
     
  int digit1 = 10; 
  int digit2 = 11; 
  int digit3 = 12; 
  int digit4 = 13; 
 
  int segA = 2;  
  int segB = 3; 
  int segC = 4; 
  int segD = 5; 
  int segE = 6; 
  int segF = 7; 
  int segG = 8; 
  int segDP= 9; 
   
  int numberOfDigits = 4;
 
  //Initialize display
  display7seg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
   
  //Set brightness
  display7seg.SetBrightness(50);
  display7seg.DisplayString(1234, 3);
  //timer = millis();
}
 
void loop()
{
  /*char tempString[10]; //Used for sprintf
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int seconds = ConvertToDecimal(Wire.read());
  int minutes = ConvertToDecimal(Wire.read());
  int hours = ConvertToDecimal(Wire.read() & 0b111111); 
  sprintf(tempString, "%02d%02d", hours, minutes);*/
}
 
