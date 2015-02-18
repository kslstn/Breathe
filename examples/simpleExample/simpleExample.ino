/*

  Simple example for using the Breathe library.

*/

#include <Breathe.h>
Breathe Breathe; // Don't forget to breathe.

// Set the pins with LEDs
#define PIN_RED 11

void setup(){
  pinMode(PIN_RED, OUTPUT);
}

void loop(){
  Breathe.set(PIN_RED); 
}