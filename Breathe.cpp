/*

	Breathe library for Arduino.

	Created 17 February 2015 
	Copyright Koos Looijesteijn

	Licence, info and latest version at https://github.com/kslstn/Breathe

*/

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <math.h>

#include <Breathe.h>

const int numberOfFadingLEDs = 14; // I would like to make this more dynamic, as it takes 99 bytes of memory more than if I use 3 instead.

// Calculate next brightness value during breath cycle:
float Breathe::breathe(float fadeSpeed, long offset, int sign){
  // fadeSpeed: 1.0 is a good default, 0.75 a good sleep mode, 3 is pretty fast
  // offset: if lED has to fade in/out, we need to do a phase shift to allign the function with millis()
  // sign: HIGH = fade in, LOW = fade out.
  long offsetMillis = millis() - offset;
  float phaseShift = (-1+2*sign)*6;  // Aligned with fade in speed. For phase shift aligned with 0: (-1+2*sign)*3*PI/2 = (-1+2*sign)*4.7123889
  return 108.3*(exp(sin((fadeSpeed*offsetMillis/2000.0*PI) + phaseShift)) - 0.36787944); 
}
// Calculate next brightness value during fade:
float Breathe::fade(float brightness, float fadeSpeed, int toggle){
  // toggle: HIGH = fade in, LOW = fade out.
  static long previousFadeStep;
  if(millis() > previousFadeStep + 25UL){
    previousFadeStep = millis(); 
    brightness = brightness + (-1+2*toggle)*1.5*fadeSpeed;
  }
  return brightness;
}
// Start or end the breathing cycle with a fade:
void Breathe::set(int pin, int toggle, float fadeSpeed){
  static bool init[numberOfFadingLEDs];
  static long offset[numberOfFadingLEDs];
  static float brightness[numberOfFadingLEDs];

  if (toggle == HIGH){// fade in and start breathing
    if (init[pin] == 0){
      if (brightness[pin] < 56){
        brightness[pin] = fade(brightness[pin], fadeSpeed, toggle);
      }
      else{
        offset[pin] = millis() ;
        init[pin] = 1; // So the fade in cycle is skipped and breathe is called instead.
      }
    }
    else{
      brightness[pin] = breathe(fadeSpeed, offset[pin]);
    }
  }
  else{ // fade out and stop breathing
    if (brightness[pin] > 5){
      brightness[pin] = fade(brightness[pin], fadeSpeed, toggle);
    }
    if (brightness[pin] < 5){
      brightness[pin] = 0;
      init[pin] = 0;
    }
  }
  analogWrite(pin, brightness[pin]); // ... and finally set the LED's brightness.    
}