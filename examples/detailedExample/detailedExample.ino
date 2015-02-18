/*

  This example demonstrates the options of the Breathe library.
  
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
  // This example uses the Arduino's clock that counts milliseconds since start up to time actions.
  long currentMillis = millis();

  if (currentMillis < 6000){
    // Start breathing LEDs with Breathe.set():
    Breathe.set(PIN_RED); // Pass at least a pin number as argument.
    Breathe.set(PIN_YELLOW, HIGH); // The second argument: HIGH for fade in, LOW for fade out.     
    Breathe.set(PIN_GREEN, HIGH, 1.2); // the third argument sets the speed of the effect
  }
  if ((currentMillis > 6000) && (currentMillis < 12000)){
    // If no new input is sent, LEDs keep their brightness - Red stays on now.
    // Breathe.set() is also used to turn LEDs of.
    digitalWrite(PIN_YELLOW, LOW); // You can switch the LEDs on and off the normal way too, but you can't properly fade it in afterward.
    Breathe.set(PIN_GREEN, LOW, 100); // It's better to switch LEDs off with a (quick) fade. After fade out, the LED stays out.
  }
  if ((currentMillis > 12000) && (currentMillis < 14000)){
    // The fade out can have a different speed than the breathing cycle ...
    Breathe.set(PIN_RED, HIGH, 4); // And you can just as well change the speed of a cycle that was started before.
    Breathe.set(PIN_YELLOW, HIGH, 1); // This will not fade in nicely, because it's been switched off with digitalWrite. 
  }
  if ((currentMillis > 14000) && (currentMillis < 18000)){
    Breathe.set(PIN_RED, HIGH, 4);
    Breathe.set(PIN_YELLOW, HIGH, 0.8);
  }
  if ((currentMillis > 18000) && (currentMillis < 20000)){
    Breathe.set(PIN_RED, LOW, 4);
    Breathe.set(PIN_YELLOW, LOW, 4);
  }  
  if ((currentMillis > 20000)){
    Breathe.set(PIN_RED, HIGH, 1, 30);// the fourth argument sets a minimum brightness. The default is 0.
    Breathe.set(PIN_YELLOW, HIGH, 1, 30);
    Breathe.set(PIN_GREEN, HIGH, 1, 30);
    // The Breathe.set command must be inside a loop so it's called over and over again, calculating a different brightness every time.    
  }
}