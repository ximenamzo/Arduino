#include<EEPROM.h>

//int my_array[10] = {B11111100, B01100000, B11011000, B11110010, B01100110, B10110110, B10111110, B11100010, B11111110, B11100110}; //cathode
//int my_array[10] = {B00000011, B10011111, B00100111, B00001101, B10011001, B01001001, B01000001, B00011101, B00000001, B00011001}; //anode
const byte num[10]= {B00000011, B10011111, B00100111, B00001101, B10011001, B01001001, B01000001, B00011101, B00000001, B00011001}; //anode

//                     A B C D E  F  G  dp
const int segPin[8] = {6,7,8,9,10,11,12,13};
//                     dp  G  F  E D C B A
const int segPinr[8] = {13,12,11,10,9,8,7,6};



void setup() {

}

void loop() {
  
}
