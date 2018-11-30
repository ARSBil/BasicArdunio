/*
 * Seri port ekranınadan gelen tam sayının tekmi çift mi 
 * olduğunu bulan program.
 */

int sayi, kalan;
int led=10;

void setup() {
  Serial.begin(9600);  
  pinMode(led,OUTPUT);
  
  Serial.println("Bir TamSayı Giriniz: "); 

}

void loop() {
 /* digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  delay(1000);*/
  while(Serial.available()>1) {
     sayi = Serial.parseInt(); //Seri portdan geleni tamsayı yapar.
     kalan = sayi % 2;
     if (kalan==0) {
        Serial.println("Çift Sayı");
        digitalWrite(led,HIGH);
     }
      else {
        Serial.println("Tek Sayı");
        digitalWrite(led,LOW);
      }
    

     
     
  }

}
