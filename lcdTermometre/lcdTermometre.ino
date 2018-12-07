#include <LiquidCrystal.h>

int lm35 = A0;

LiquidCrystal lcd(7,6,5,4,3,2);
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  
  lcd.begin(16,2);
  lcd.clear();
  //analogWrite(lm35,OUTPUT);
  lcd.print("Sicaklik: ");
  analogReference(INTERNAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*float sicaklikV = analogRead(lm35);
  float gerilim = (sicaklikV / 1023) *5000;
  float sicaklik = gerilim / 10.0;*/
  float sicaklikV = analogRead(lm35);
  float sicaklik = sicaklikV / 9.31;
  /*Serial.print("sicaklikV :");
  Serial.println(sicaklikV);
  Serial.print("gerilim :");
  Serial.println(gerilim);
  Serial.print("sicaklik :");
  Serial.println(sicaklik);*/
  
  lcd.setCursor(0,1);
  lcd.print(sicaklik);
  lcd.setCursor(6,1);
  lcd.print("\337C");
  delay(1000);
  /*
  lcd.setCursor(0,0);
  //lcd.scrollDisplayRight();
  lcd.print("Merhaba Dunya");
  lcd.setCursor(0,1);
  lcd.print("Arduniooo! "+String(lm35));
  delay(500);
  */
  
}
