/*
 * Seri port ekranınadan gelen tam sayının tekmi çift mi 
 * olduğunu bulan program.
 */

int a, b;
int led=10;
int led1=9;
void setup() {
  Serial.begin(9600);  
  pinMode(led,OUTPUT);
  pinMode(led1,OUTPUT);
  
  Serial.println("Bir TamSayı Giriniz: "); 

}

void loop() {
 /* digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  delay(1000);*/
  while(Serial.available()>2) {
     a = Serial.parseInt(); //ilk sayı a değişkenine
     b = Serial.parseInt(); //ikinci sayı b değişkenine

      
     digitalWrite(led,LOW);
     digitalWrite(led1,LOW);
     if (a>b) {
        Serial.println("İlk Sayı Daha Büyük");
        digitalWrite(led,HIGH);
     }
     else if (b>a) {
        Serial.println("İkinci Sayı Daha Büyük");
        digitalWrite(led1,HIGH);
     }
      else {
        Serial.println("Eşitlik sağlandı");
        digitalWrite(led,LOW);
        digitalWrite(led1,LOW);
      }
    

     
     
  }

}
