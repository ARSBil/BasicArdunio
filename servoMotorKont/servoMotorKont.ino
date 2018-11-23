#include <Servo.h>

/*
 * Servo motor kontrolü
 */
 int gecis = 0;
int pot = A0;
Servo serMotor;
void setup() {
  pinMode(pot, INPUT);
  Serial.begin(9600);
  serMotor.attach(9); 

}

void loop() {
  // put your main code here, to run repeatedly:
  int analogDeger = analogRead(pot);
  //float servoAci = (float(analogDeger)*180)/1023;
  int servoAci = map(analogDeger,0,1023,0,180);
  serMotor.write(servoAci);
  if (gecis==servoAci)
    return;
    
  gecis = servoAci;
  Serial.print("Servo Açısı: ");
  Serial.println(servoAci);
  /*delay(1500);
  serMotor.write(180);
  Serial.print("Servo Açısı: ");
  Serial.println("180");
  delay(1500);*/
}
