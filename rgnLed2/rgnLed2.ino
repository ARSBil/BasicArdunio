int kirmiz = 9;
int yesil = 10;
int mavi = 11;

void setup() {
  pinMode(kirmiz,OUTPUT);
  pinMode(yesil,OUTPUT);
  pinMode(mavi,OUTPUT);
}

void loop() {
  analogWrite(kirmiz,50);
  analogWrite(yesil,50);
  analogWrite(mavi,50);
  delay(5000);

  analogWrite(kirmiz,0);
  analogWrite(yesil,255);
  analogWrite(mavi,0);
  delay(500);
  analogWrite(kirmiz,0);
  analogWrite(yesil,0);
  analogWrite(mavi,255);
  delay(500);
}
