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

// Calculate next brightness value during breathing cycle:
float Breathe::breathe(float fadeSpeed, long offset){
	return 108.3*(exp(sin((fadeSpeed * (millis() - offset) / 2000.0*PI) + 4.7123889)) - 0.36787944); // phase shift aligned with 0: 3*PI/2 = 4.7123889
}
void Breathe::set(int pin, int toggle, float fadeSpeed){
	static float brightness[numberOfFadingLEDs];
	static long offset[numberOfFadingLEDs];
	static long previousStep[numberOfFadingLEDs];
	float currentCycleBrightness = breathe(fadeSpeed, offset[pin]);
	float range = 10 + 6*fadeSpeed;

	if ((toggle == HIGH) || (brightness[pin] > 1)){// fade in and start breathing. If toggle is LOW, we continue till brightness is very low.
		Serial.println("toggle=");
		Serial.println(toggle);
		if (millis() < previousStep[pin] + 100){ // with more than 100ms between two calls, it's assumed there's been a pause.
			brightness[pin] = currentCycleBrightness;
			previousStep[pin] = millis(); // Save current time to check in the next call how much time has passed since now.
		}
		else{
			if ((brightness[pin] ==  0)){ // If out of sync and brightness equals zero, create phase shift to start immediately with fade in.
				offset[pin] = millis();
				brightness[pin] = breathe(fadeSpeed, offset[pin]);
				previousStep[pin] = millis();
			}
			else if ((brightness[pin] > currentCycleBrightness - range) && (brightness[pin] < currentCycleBrightness + range)){
				brightness[pin] = breathe(fadeSpeed, offset[pin]);
				previousStep[pin] = millis();
			}
		}
	}
	else{// Toggle is LOW and the brightness is very low.
		brightness[pin] = 0;
	}
	analogWrite(pin, brightness[pin]); // Set the pin's output.
}