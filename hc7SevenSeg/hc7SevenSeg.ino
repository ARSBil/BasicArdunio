
#include "Arduino.h"
#include "HC7Seg.h"

/* Digital pins used to drive each digit and digit segment of your display. Please
   change these to match the connections to your module */
#define SEG_A   2
#define SEG_B   4
#define SEG_C   8
#define SEG_D   6
#define SEG_E   7
#define SEG_F   3
#define SEG_G   9
#define SEG_DP  5
#define DIG_1 13
#define DIG_2 12
#define DIG_3 11
#define DIG_4 10

//HC7Seg HC7Seg(COM_CATHODE_1DIG, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP, DIG_1); //1 digit common cathode example (e.g. HCOPTO0012)
HC7Seg HC7Seg(COM_CATHODE_4DIG, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP, DIG_1, DIG_2, DIG_3, DIG_4); //4 digit common cathode example (e.g. HCOPTO0013)
//HC7Seg HC7Seg(COM_ANODE_8DIG, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP, DIG_1, DIG_2, DIG_3, DIG_4, DIG_5, DIG_6, DIG_7, DIG_8); //8 digit common anode example


void setup()
{
   HC7Seg.clear();
    HC7Seg.print7Seg(1235, 0, 2);
}

void loop()
{
  
  /* Scroll an integer number 
  for(int i = 0; i <= 14; i++)
  {
    HC7Seg.clear();
    HC7Seg.print7Seg(1235, i, 2);
    delay(500);
  }*/
}
