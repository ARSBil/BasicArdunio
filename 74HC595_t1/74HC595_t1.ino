int latch=9;  //74HC595  pin 9 STCP
int clock=10; //74HC595  pin 10 SHCP
int data=8;   //74HC595  pin 8 DS

void setup()
{
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);
}

void Display(unsigned int num)
{  
  digitalWrite(latch,LOW);
  shiftOut(data,clock,MSBFIRST,num);
  digitalWrite(latch,HIGH); 
}

void loop()
{
    Display(91);
    delay(1000);
    Display(127);
    delay(1000);
}
