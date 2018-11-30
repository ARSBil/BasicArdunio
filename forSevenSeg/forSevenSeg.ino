#include "virtuabotixRTC.h"
#include "SevSeg.h"

SevSeg sevseg;//Instantiate a seven segment object
virtuabotixRTC myRTC(0, 1, 2);
void setup() {
  
  myRTC.setDS1302Time(00, 01, 21, 7, 30, 11, 2018);
  
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
//sevseg.setNumber(3.14159f,3); //Displays '3.141'
}  

void loop() {
/*
myRTC.updateTime();
 
// Şimdi değerleri okuyalım
Serial.print("Şuanki Tarih / Saat : ");
Serial.print(myRTC.dayofmonth);
Serial.print("/");
Serial.print(myRTC.month);
Serial.print("/");
Serial.print(myRTC.year);
Serial.print(" ");
Serial.print(myRTC.hours);
Serial.print(":");
Serial.print(myRTC.minutes);
Serial.print(":");
Serial.println(myRTC.seconds);
 
// 3 saniye gecikme veriyoruz.
delay( 3000);*/

//sevseg.setNumber(int(myRTC.hours+""+myRTC.seconds),2);

   sevseg.setNumber(1234,2);
   sevseg.refreshDisplay();
   sevseg.setBrightness(90);


   

}
