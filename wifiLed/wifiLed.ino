#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(12,11,5,4,3,2);
 SoftwareSerial Serial1(7,6); // RX, TX
const String wifiAdi = "ARSBil";
const String wifiSifresi = "oa159753..oa";

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(500);
  lcd.begin(16,2);
  lcd.print("Sistem Basliyor.");
  delay(1000);

  if (!internetBaglan()) {
    Serial.println("internete bağlanamadı");  
    lcd.print("internete baglanamadi");  
  } else {
    Serial.println("Modul internete bağlandı");
    lcd.print("Modul internete baglandi");
  }

  String istek ="GET /index.php HTTP/1.0\r\nConnection: close\r\nHost: www.arsbil.com\r\n\r\n";
  Serial1.print("AT+CIPSTART=\"TCP\",\"www.arsbil.com\",80\r\n");
  Serial1.find("OK");

  Serial.println("Bağlantı İsteği Yollandı");
  lcd.print("Baglanti Istegi Yollandi");
  delay(1000);

  Serial1.print("AT+CIPSEND=");
  Serial1.find(">");

  Serial1.println(String(istek.length()));
  Serial.println("HTTP İsteği Gönderildi.");
  lcd.print("HTTP  Istegi Yollandi");
  delay(1000);

  Serial1.print(istek);
  Serial1.find("SEND OK");
  Serial.println("Baglantı Kuruldu");
  lcd.print("Baglanti Kuruldu");

  String alinanVeri = "";
  char k;
  long zaman = millis();

  while(alinanVeri.indexOf("CLOSED") == -1) {
    
  Serial.println("1");
    if(millis() - zaman > 3000) {
       Serial.println("2");
      break;
    }
    while(Serial1.available()) {
       Serial.println("3");
      k = Serial1.read();
      alinanVeri+=k;
    }
  }
 Serial.println("4");
  Serial.println("Gelen Veriler:");
  Serial.println(alinanVeri);

  Serial.println("Seçilen Veriler");
  Serial.print("Sıcaklık: ");
  Serial.println(parcala(alinanVeri,"temp"));
  lcd.print("Sicaklik:"+parcala(alinanVeri,"temp"));
  Serial.print("Nem: ");
  Serial.println(parcala(alinanVeri,"humidity"));
  lcd.setCursor(0,2);
  lcd.print("Nem:"+parcala(alinanVeri,"humidity"));

  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

}


String parcala(String parca, String bol) {
  int ilk = parca.indexOf(bol) + bol.length() +2;
  String ikincikisim = parca.substring(ilk);
  int son1 = ikincikisim.indexOf(",");
  int son2 = ikincikisim.indexOf("}");
  if(son1<0) 
    son1=999;
    
  if(son2<0)
      son2=999;
  int son;

  if(son1< son2) 
    son=son1;
  else
    son=son2;

  return parca.substring(ilk,ilk+son);
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
    Serial.print(cevap);
  }
  return cevap;
}

boolean internetBaglan() {
  ATKomuduYolla("AT+CWMODE=1\r\n", 1000, true);
  ATKomuduYolla("AT+CWJAP=\""+ wifiAdi +"\",\""+ wifiSifresi +"\"\r\n", 1000, true);
  String durum = "";
  durum = ATKomuduYolla("AT+CIFSR\r\n", 8000, true);
  if (durum.indexOf("FAIL") != -1) {
    return false;
  }
  return true;
}
