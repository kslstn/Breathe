/*

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

const int numberOfFadingLEDs = 14; // For slightly less memory use, you may want to decrease this number and use the highest pin with a breathing LED.
// Calculate new brightness value during breathing cycle:
float Breathe::breathe(float fadeSpeed, long offset, int minBrightness){
	float min = (float)minBrightness;
	// phase shift aligned with 0: 3*PI/2 = 4.7123889
	return min + ((255 - min) / 255) * 108.3 * (exp(sin((fadeSpeed * (millis() - offset) / 2000.0*PI) + 4.7123889)) - 0.36787944); 
}
// Figure out what to do with the pin's output based on the function's arguments and time passed:
void Breathe::set(int pin, int toggle, float fadeSpeed, int minBrightness){
	static float brightness[numberOfFadingLEDs];
	static long offset[numberOfFadingLEDs];
	static long previousStep[numberOfFadingLEDs];
	float currentCycleBrightness = breathe(fadeSpeed, offset[pin], minBrightness);
	float range = 10 + 6*fadeSpeed;

	if ((toggle == HIGH) || (brightness[pin] > minBrightness + 1)){// fade in and start breathing. If toggle is LOW, we continue till brightness is very low.
		if (millis() < previousStep[pin] + 100){ // with more than 100ms between two calls, it's assumed there's been a pause.
			brightness[pin] = currentCycleBrightness;
			previousStep[pin] = millis(); // Save current time to check in the next call how much time has passed since now.
		}
		else{
			if (brightness[pin] < minBrightness){
				brightness[pin] += fadeSpeed;
			}
			if (brightness[pin] == minBrightness){ // If out of sync and brightness equals minimum, ...
				offset[pin] = millis(); // ... create phase shift ...
				brightness[pin] = breathe(fadeSpeed, offset[pin], minBrightness);// ... to sync with lowest point on the breathing curve.
				previousStep[pin] = millis();
			}
			else if ((brightness[pin] > currentCycleBrightness - range) && (brightness[pin] < currentCycleBrightness + range)){
				brightness[pin] = breathe(fadeSpeed, offset[pin], minBrightness);
				previousStep[pin] = millis();
			}
		}
	}
	else{// Toggle is LOW and the brightness is very low.
		brightness[pin] = minBrightness;
	}
	analogWrite(pin, brightness[pin]); // Set the pin's output.
}