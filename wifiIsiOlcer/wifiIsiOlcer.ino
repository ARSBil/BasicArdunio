#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
LiquidCrystal lcd(12,11,5,4,3,2);
SoftwareSerial Serial1(7,6); // RX, TX
const String wifiAdi = "ARSBil";
const String wifiSifresi = "oa159753..oa";
int trigPin = 9;
int echoPin = 8;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(500);
  lcd.begin(16,2);
  lcd.print("Sistem Basliyor.");
  delay(1000);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);


  if (!internetBaglan()) {
    Serial.println("internete bağlanamadı");  
    lcd.print("internete baglanamadi");  
  } else {
    Serial.println("Modul internete bağlandı");
      lcd.begin(16,2);
    lcd.print("Modul internete baglandi");
      delay(1000);
  }




}

void loop() {
    olcum();
    
    sicaklikOlcum();
}

void sicaklikOlcum() {
  
  float sicaklikDegeri = analogRead(A0);
  sicaklikDegeri = analogRead(A0) * 0.48828125;
  
  Serial.print("Sıcaklık Değeri: ");
  Serial.print(sicaklikDegeri);
  Serial.println(" C olarak Ölçülmüüştür");
  delay(1000);
}

void olcum() {
  long sure, mesafe;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  mesafe = (sure/2) / 29.1;
  if (mesafe > 200 || mesafe < 0){
    Serial.println("Menzil Disi");
    delay(1000);
  }
  else {
    Serial.print(mesafe);
    Serial.println(" cm");
  }
  delay(500);
  

}

String ATKomuduYolla(String ATKomudu, int zamanAsimi, boolean debug) {
  Serial1.print(ATKomudu);
  long int zaman = millis();
  String cevap = "";
  while(zaman+zamanAsimi>millis()) {
    while(Serial1.available()) {
      char k = Serial1.read();
      cevap+=k;
    }
    if(cevap.indexOf("OK") != -1) 
      break;
  }
  if(debug) {
    Serial.println("-> "+cevap);
  }
  return cevap;
}

boolean internetBaglan() {
  ATKomuduYolla("AT+CWMODE=1\r\n", 1000, true);
  ATKomuduYolla("AT+CWJAP=\""+ wifiAdi +"\",\""+ wifiSifresi +"\"\r\n", 1000, true);
  String durum = "";
  durum = ATKomuduYolla("AT+CIFSR\r\n", 8000, true);
    Serial.println("--> "+durum);
  if (durum.indexOf("FAIL") != -1) {
    return false;
  }
  return true;
}
