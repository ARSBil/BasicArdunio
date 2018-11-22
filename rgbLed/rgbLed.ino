int pin2=2;
int pin3=3;
int pin4=4;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin2,HIGH);
  delay(2000);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin2,LOW);
  delay(2000);
    digitalWrite(pin4,HIGH);
    digitalWrite(pin3,LOW);
  delay(2000);
  digitalWrite(pin4,LOW);
  delay(1000);
}
