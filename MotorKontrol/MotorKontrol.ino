
int solCiz = A0;
int sagCiz = A1;

// motor A
int enA = 10;
int in1 = 7;
int in2 = 6;

// motor B
int enB = 5;
int in3 = 9;
int in4 = 8;

int tetik=12;
int eko=11;
unsigned long sure;
float mesafe;
int hizSol,hizSag;
int hiz=125;
void setup()
{
  // Bütün motor pinleri çıkış
  Serial.begin(9600);
  pinMode(tetik,OUTPUT);
  pinMode(eko,INPUT);

  
  pinMode(solCiz, INPUT);
  pinMode(sagCiz,INPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void Ileri(int pwm)
{
  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //////////////////////
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Geri(int pwm)
{
  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //////////////////////
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Sag(int pwm)
{
  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //////////////////////
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Sol(int pwm)
{
  analogWrite(enA, pwm);
  analogWrite(enB, pwm);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //////////////////////
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void Dur ()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //////////////////////
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop()
{
    if(Serial.available()>1) {
    int yon = Serial.read();
    //yon.trim();
    //Serial.println(yon);
    switch(yon) {
      case 'w': Ileri(255);    
      Serial.print("ileri: ");  
    Serial.println(yon);
      break;
      case 's': Geri(255);      
      Serial.print("geri: ");  
    Serial.println(yon);
      break;
      case 'a': Sag(200);
      Serial.print("sag: ");  
    Serial.println(yon);
      break;
      case 'd': Sol(200);
      Serial.print("sol: ");  
    Serial.println(yon);
      break;  
      default: Dur();
      Serial.print("dur: ");  
    Serial.println(yon);
    }

  }
    if(mesafeOlc()<=20.0)
      Dur();
    else 
      Ileri(255);
delay(5);
  int solOku = analogRead(solCiz);
  int sagOku = analogRead(sagCiz);

  if(solOku>800 && hizSag>0) {
    hizSol--;
    Sol(hizSol);
  }
  else if(solOku>800 && sagOku>800) {
    hizSol=hiz;
    hizSag=hiz;
   .. Ileri(hiz);
  }else if(sagOku<800 && hizSag>0) {
    hizSag--;
    Sag(hizSag);
  }

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
