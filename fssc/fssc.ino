

/*
Author: Danny van den Brande, arduinosensors.nl. BlueCore Tech.
This code is written for the AT24C32/DS1307 RTC Module and 
4 digit Seven Segment displays. 
Be sure to check if you have a common anode or cathode display.(change @ line 26)
 */
#include "Wire.h"
#include "SevSeg.h" //https://github.com/sparkfun/SevSeg/tree/master/src
 
#define DS1307_ADDRESS 0x68
 
//Create an instance
SevSeg sevseg;
 
int valor = 0;
 
byte zero = 0x00; 
unsigned long timer;
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  //Comment this line after you have set the date @ void TimeSelection() below
//   TimeSelection(); Uncomment this line when your setting the time. Set time @ (line 66)
  
  //Change to COMMON_ANODE  COMMON_CATHODEif you have a Common anode display.
byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  timer = millis();
}
 
void loop()
{
  char tempString[10]; //Used for sprintf
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int seconds = ConvertToDecimal(Wire.read());
  int minutes = ConvertToDecimal(Wire.read());
  int hours = ConvertToDecimal(Wire.read() & 0b111111); 
  sprintf(tempString, "%02d%02d", hours, minutes);
  sevseg.setNumber(int(tempString), 3);
  Serial.println(tempString);
}
 
void TimeSelection()   //Select date and time here below!!(line 69,70,71)
//after setting time also comment time TimeSelection() @ void setup
{
  byte seconds = 10; //Valores de 0 a 59
  byte minutes = 38; //Valores de 0 a 59
  byte hours = 3; //Valores de 0 a 23
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //Stop no CI para que o mesmo possa receber os dados
 
  //As linhas abaixo escrevem no CI os valores de 
  //data e hora que foram colocados nas variaveis acima
  Wire.write(ConvertToPCD(seconds));
  Wire.write(ConvertToPCD(minutes));
  Wire.write(ConvertToPCD(hours));
  Wire.write(zero);
  Wire.endTransmission(); 
}
 
byte ConvertToPCD(byte val)
{ 
  //Convert Decimal to binary
  return ( (val/10*16) + (val%10) );
}
 
byte ConvertToDecimal(byte val)  
{ 
  //Convert binary to decimal
  return ( (val/16*10) + (val%16) );
}
