#include <SoftwareSerial.h>

SoftwareSerial wifiBaglantisi(10,11);

const String wifiAdi = "ARSBil";
const String wifiSifresi = "oa159753..oa";

const String serverIP = "192.168.1.8";
const String port = "3001";

int motorHizi = 50;
const int sagileri = 9;
const int saggeri = 8;
const int solileri = 12;
const int solgeri = 13;
const int solenable = 6;
const int sagenable = 5;

void ileri() {
  analogWrite(sagenable, motorHizi);
  digitalWrite(sagileri, HIGH);
  digitalWrite(saggeri,LOW);

  analogWrite(solenable, motorHizi);
  digitalWrite(solileri, HIGH);
  digitalWrite(solgeri, LOW);
}

void sag() {
  analogWrite(sagenable, motorHizi);
  digitalWrite(sagileri, LOW);
  digitalWrite(saggeri, HIGH);

  analogWrite(solenable, motorHizi);
  digitalWrite(solileri, HIGH);
  digitalWrite(solgeri, LOW);
}
void sol(){
  analogWrite(sagenable, motorHizi);
  digitalWrite(sagileri, HIGH);
  digitalWrite(saggeri, LOW);

  analogWrite(solenable, motorHizi);
  digitalWrite(solileri, LOW);
  digitalWrite(solgeri, HIGH);
}

void geri(){
  analogWrite(sagenable, motorHizi);
  digitalWrite(sagileri, LOW);
  digitalWrite(saggeri, HIGH);
  
  analogWrite(solenable, motorHizi);
  digitalWrite(solileri, LOW);
  digitalWrite(solgeri, HIGH);
}

void dur(){
  digitalWrite(sagileri, HIGH);
  digitalWrite(saggeri, HIGH);
  digitalWrite(solileri, HIGH);
  digitalWrite(solgeri, HIGH);
}

void setup() {
  Serial.begin(9600);
  wifiBaglantisi.begin(115200);
  wifiBaglantisi.println("AT+CIOBAUD=9600");
readwifiBaglantisi(4000);

  wifiBaglantisi.begin(9600);
  delay(500);
  /*if(!interneteBaglan()){
    Serial.println("internete baglanamadi");
  }
  else {
    Serial.println("Modul internete baglandi");
    ATKomuduYolla("AT+CIPMUX=1",1000,true);  // multiple connections 
    readwifiBaglantisi(2000);
    
    Serial.println("1");
  }*/
InitwifiBaglantisi();
  wifiBaglantisi.print("AT+CIPSTART=\"TCP\",\"192.168.1.8\",3001\r\n");
  readwifiBaglantisi(4000);
  if(wifiBaglantisi.find("OK")){
    Serial.println("Servera baglanildi");
    
   // ATKomuduYolla("AT+CIFSR",1000,true); // IP adress
  
    //ATKomuduYolla("AT+CIPMUX=1",1000,true);  // multiple connections 

  }
  else {
    Serial.println("Servera baglanilamadi");
  }
  delay(100);
  
}

void loop() {
  while(wifiBaglantisi.available()){
    if(!wifiBaglantisi.find(":"))
      break;

    delay(5);

    while(wifiBaglantisi.available()){
      char k = wifiBaglantisi.read();
      switch(k) {
        case 'w':
          ileri();
          Serial.println("ileri");
          break;

        case 'a':
          sol();
          Serial.println("sol");
          break;

        case 'd':
          sag();
          Serial.println("sag");
          break;

        case 's':
          geri();
          Serial.println("geri");
          break;

        case 'x':
          dur();
          Serial.println("dur");
          break;        
      }
    }
  }

}

void readwifiBaglantisi(const int timeout)
{
  String reponse = "";
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(wifiBaglantisi.available())
    {
      char c = wifiBaglantisi.read();
      reponse+=c;
    }
  }
  Serial.print(reponse);   
}
String ATKomuduYolla(String ATKomudu, int zamanAsimi, boolean debug) {
  wifiBaglantisi.print(ATKomudu);
  long int zaman = millis();
  String cevap = "";
  while(zaman+zamanAsimi>millis()) {
    while(wifiBaglantisi.available()) {
      char k = wifiBaglantisi.read();
      cevap+=k;
    }
    if(cevap.indexOf("OK") != -1) 
      break;
  }
  if(debug) {
    Serial.print(cevap);
  }
  return cevap;
}
void InitwifiBaglantisi()
{  
  wifiBaglantisi.println("AT");
  readwifiBaglantisi(2000);
  wifiBaglantisi.println("AT+RST");
  readwifiBaglantisi(2000);

  wifiBaglantisi.println("AT+CWMODE=1"); //Wifi mode
  readwifiBaglantisi(5000);

  wifiBaglantisi.println("AT+CWJAP=\""+ wifiAdi +"\",\""+ wifiSifresi +"\""); //connect wifi
  readwifiBaglantisi(10000);

  wifiBaglantisi.println("AT+CIFSR"); // IP adress
  readwifiBaglantisi(1000);
/*
  wifiBaglantisi.println("AT+CIPMUX=1");  // multiple connections 
  readwifiBaglantisi(1000);
*/
}

boolean interneteBaglan() {
  ATKomuduYolla("AT+CWMODE=1\r\n", 1000, true);
  ATKomuduYolla("AT+CWJAP=\""+ wifiAdi +"\",\""+ wifiSifresi +"\"\r\n", 1000, true);
  String durum = "";
  durum = ATKomuduYolla("AT+CIFSR\r\n", 8000, true);
  if (durum.indexOf("FAIL") != -1) {
    return false;
  }
  return true;
}
