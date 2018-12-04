

 #include <virtuabotixRTC.h>
/* SevSeg Counter Example
 Copyright 2017 Dean Reading
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
 */

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object
virtuabotixRTC myRTC(5, 4, 3);
void setup() {
  //Serial.begin(9600); 
// Dilediğiniz tarihi aşağıda belirtilen biçimde girebiliyorsunuz. Ben örnek olarak
// bugünün tarihini girdim.
// saniye, dakika, saat, haftanın günü, ayın günü, ay, yıl (Not: haftanın günü 1:pazartesiden başlıyor
myRTC.setDS1302Time(11, 11, 23,2, 4, 12, 2018);

  
  byte numDigits = 4;
  byte digitPins[] = {A0, A1, A2, A3};//{2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // COMMON_CATHODE
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);
}

void loop() {
myRTC.updateTime();
/* 
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
Serial.println(myRTC.seconds);*/
/* 
//Serial.println(aa);
// 3 saniye gecikme veriyoruz.
sevseg.setNumber(1234,3);
  sevseg.refreshDisplay(); // Must run repeatedly
  delay(3000);
   */
  static unsigned long timer = millis();
  static int deciSeconds = 0;
//int aa = (String(myRTC.hours)+String(myRTC.minutes)).toInt();
int aa = (String(myRTC.minutes)+String(myRTC.seconds)).toInt();
 /* if (millis() - timer >= 1000) {
    timer += 100;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    
    if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
  }
*/
    sevseg.setNumber(aa, 2);
  sevseg.refreshDisplay(); // Must run repeatedly
//delay(500);
}
