int tetik=12;
int eko=11;
unsigned long sure;
float mesafe;

void setup() {
  Serial.begin(9600);
  pinMode(tetik,OUTPUT);
  pinMode(eko,INPUT);

}

void loop() {


  Serial.print("Ölüçülen Mesafe: ");
  Serial.print(mesafeOlc());
  Serial.println("cm");

delay(500);
  
}

float mesafeOlc() {
    // put your main code here, to run repeatedly:
  digitalWrite(tetik,LOW);
  delayMicroseconds(2);
  digitalWrite(tetik,HIGH);
  delayMicroseconds(10);
  digitalWrite(tetik,LOW);

  sure = pulseIn(eko,HIGH);
  mesafe = (float)sure*0.01715;
  return mesafe;
}
