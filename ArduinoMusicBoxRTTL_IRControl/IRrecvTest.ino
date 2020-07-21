/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <IRremote.h>
#include "codes.h"
int RECV_PIN = 22;

IRrecv irrecv(RECV_PIN);

decode_results results;




void initIRecv()
{
  //Serial.begin(115200);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

int doIRDecode() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    int cmd= checkRecvCode(results.value);
    return cmd;
  }
  return -1;
  //delay(100);
}

int checkRecvCode(unsigned long value) {
  if (value == 0xFF629D) {
    Serial.println("KEY_UP");
    return 'U';
  }
  else if (value == 0xFFA857) {
    Serial.println("KEY_DOWN");
    return 'D';
  }
  else if (value == 0xFF22DD) {
    Serial.println("KEY_LEFT");
    return 'L';
  }
  else if (value == 0xFFC23D) {
    Serial.println("KEY_RIGHT");
    return 'R';
  }
  else if (value == 0xFF02FD) {
    Serial.println("KEY_OK");
    return 'O';
  }
  else if (value == 0xFF6897) {
    Serial.println("KEY_ONE");
    return 1;
  }
  else if (value == 0xFF9867) {
    Serial.println("KEY_TWO");
    return 2;
  }
  else if (value == 0xFFB04F) {
    Serial.println("KEY_THREE");
    return 3;
  }
  else if (value == 0xFF30CF) {
    Serial.println("KEY_FOUR");
    return 4;
  }
  else if (value == 0xFF18E7) {
    Serial.println("KEY_FIVE");
    return 5;
  }
  else if (value == 0xFF7A85) {
    Serial.println("KEY_SIX");
    return 6;
  }
  else if (value == 0xFF10EF) {
    Serial.println("KEY_SEVEN");
    return 7;
  }
  else if (value == 0xFF38C7) {
    Serial.println("KEY_EIGHT");
    return 8;
  }
  else if (value == 0xFF5AA5) {
    Serial.println("KEY_NINE");
    return 9;
  }
  else if (value == 0xFF42BD) {
    Serial.println("KEY_STAR");
    return '*';
  }
  else if (value == 0xFF4AB5) {
    Serial.println("KEY_ZERO");
    return 'Z';
  }
  else if (value == 0xFF52AD) {
    Serial.println("KEY_SHARP");
    return 'S';
  }
  else if (value == 0xFFFFFFFF) {
    Serial.println("NEC_REPEAT_CODE");
    return 'R';
  }
  else {
    Serial.println("KEY_UNKNOWN");
    return -1;
  }
}

//void printCode(unsigned long value) {
//  if (value == 0xFF629D) {
//    Serial.println("KEY_UP");
//  }
//  else if (value == 0xFFA857) {
//    Serial.println("KEY_DOWN");
//  }
//  else if (value == 0xFF22DD) {
//    Serial.println("KEY_LEFT");
//  }
//  else if (value == 0xFFC23D) {
//    Serial.println("KEY_RIGHT");
//  }
//  else if (value == 0xFF02FD) {
//    Serial.println("KEY_OK");
//  }
//  else if (value == 0xFF6897) {
//    Serial.println("KEY_ONE");
//  }
//  else if (value == 0xFF9867) {
//    Serial.println("KEY_TWO");
//  }
//  else if (value == 0xFFB04F) {
//    Serial.println("KEY_THREE");
//  }
//  else if (value == 0xFF30CF) {
//    Serial.println("KEY_FOUR");
//  }
//  else if (value == 0xFF18E7) {
//    Serial.println("KEY_FIVE");
//  }
//  else if (value == 0xFF7A85) {
//    Serial.println("KEY_SIX");
//  }
//  else if (value == 0xFF10EF) {
//    Serial.println("KEY_SEVEN");
//  }
//  else if (value == 0xFF38C7) {
//    Serial.println("KEY_EIGHT");
//  }
//  else if (value == 0xFF5AA5) {
//    Serial.println("KEY_NINE");
//  }
//  else if (value == 0xFF42BD) {
//    Serial.println("KEY_STAR");
//  }
//  else if (value == 0xFF4AB5) {
//    Serial.println("KEY_ZERO");
//  }
//  else if (value == 0xFF52AD) {
//    Serial.println("KEY_SHARP");
//  }
//  else if (value == 0xFFFFFFFF) {
//    Serial.println("NEC_REPEAT_CODE");
//  }
//  else {
//    Serial.println("KEY_UNKNOWN");
//  }
//}
