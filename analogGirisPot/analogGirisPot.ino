/*
analog girişten pot okuma
*/

int pot = A0;

void setup() {
  Serial.begin(9600);
  pinMode(pot, INPUT);

}

void loop() {
  int analogDeger = analogRead(pot);
  Serial.print("Pot Değeri: ");
  Serial.println(analogDeger);
  delay(500);

}
