/*

  This is the sketch I used for the little demo I put on YouTube: https://www.youtube.com/edit?o=U&video_id=JGcX6KW1d2o
  
*/

#include <Breathe.h>
Breathe Breathe;

// You can use pin 0 to 13, in this example, 9, 10 and 11 are used.
#define PIN_GREEN 9
#define PIN_YELLOW 10
#define PIN_RED 11

void setup(){ 
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);       
  pinMode(PIN_RED, OUTPUT);
}

void loop(){
  long currentMillis = millis();

  if (currentMillis < 600){
    Breathe.set(PIN_GREEN, HIGH, 10);
    Breathe.set(PIN_YELLOW, HIGH, 10);
    Breathe.set(PIN_RED, HIGH, 10);
  }
  if ((currentMillis > 700 ) && (currentMillis < 2200)){
    Breathe.set(PIN_GREEN, LOW, 3);
    Breathe.set(PIN_YELLOW, LOW, 3);
    Breathe.set(PIN_RED, LOW, 3);
  }
  if ((currentMillis > 2300 ) && (currentMillis < 3500)){
    Breathe.set(PIN_GREEN, HIGH, 2);
  }
  if ((currentMillis > 3500 ) && (currentMillis < 4700)){
    Breathe.set(PIN_GREEN, LOW, 2);
    Breathe.set(PIN_YELLOW, HIGH, 2);
  }
  if ((currentMillis > 4700 ) && (currentMillis < 5900)){
    Breathe.set(PIN_YELLOW, LOW, 2);
    Breathe.set(PIN_RED, HIGH, 2);
  }
  if ((currentMillis > 5900 ) && (currentMillis < 7300)){
    Breathe.set(PIN_RED, LOW, 2);
  }
  if (currentMillis > 7500 ){
    Breathe.set(PIN_GREEN, HIGH, 1, 10);
    Breathe.set(PIN_YELLOW, HIGH, 1, 10);
    Breathe.set(PIN_RED, HIGH, 1, 10);
  }
}