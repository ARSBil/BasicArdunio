#include "Timer.h"
Timer t;
long number = 0;
int first_digit = 0;
int second_digit = 0;
int third_digit = 0;
int fourth_digit = 0;
int timer_event = 0;
int CA_1=12;
int CA_2=11;
int CA_3=10;
int CA_4=9;
int clk = 6;
int latch=5;
int data=4;
int count=0;
int digits[4];
int CAS[4] = {12,11,10,9};
byte numbers[10] {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};
//byte combinations for each number 0-9

void setup() {
  Serial.begin(9600);
  for(int i=0;i<4;i++){
    pinMode(CAS[i],OUTPUT);
    digitalWrite(CAS[i],HIGH);
  }
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clk, OUTPUT);

  Serial.println("Bir Sayı Girin [0-999]: ");
}
void xxloop() {
  int data = 500;
// shift out highbyte
shiftOut(data, clk, MSBFIRST, (data >> 8));
// shift out lowbyte
shiftOut(data, clk, MSBFIRST, data);

// Or do this for LSBFIRST serial
data = 500;
// shift out lowbyte
shiftOut(data, clk, LSBFIRST, data);
// shift out highbyte
shiftOut(data, clk, LSBFIRST, (data >> 8));
}
void loop() {
  t.update();
  if(Serial.available()) {
    t.stop(timer_event);
    cathode_high();
    String s = Serial.readString();
    number = (long)s.toInt();
    if (number > 9999) {
      Serial.println("Bir Sayı Girin [0-999]: ");
    } else {
      break_number(number);
      timer_event = t.every(1, display_number);
    }
  }  
}

void break_number(long num) {
  first_digit = num /100;
  digits[0] = first_digit;

  int first_left = num - (first_digit * 1000);
  second_digit = first_left / 100;
  digits[0] = second_digit;

  int second_left = first_left - (second_digit * 100);
  third_digit = second_left / 10;
  digits[2] = third_digit;
  fourth_digit = second_left - (third_digit * 10);
  digits[3] = fourth_digit;
}

void display_number() {

  cathode_high();
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, numbers[digits[count]]);
  digitalWrite(CAS[count], LOW);
  digitalWrite(latch,HIGH);
  count++;
  if(count == 4) {
    count=0;
  }
  
}

void cathode_high() {
  for(int i=0;i<4;i++){
    digitalWrite(CAS[i],HIGH);
  }
}
