/*

	Breathe library for Arduino.

	Created 17 February 2015 
	Copyright Koos Looijesteijn

	Licence, info and latest version at https://github.com/kslstn/Breathe

*/
#ifndef Breathe_h
#define Breathe_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <math.h>


class Breathe{
	public:
		void set(int pin, int toggle = HIGH, float fadeSpeed = 0.8, int minBrightness = 0);
	private:
		float breathe(float fadeSpeed = 0.8, long offset = 0, int minBrightness = 0);
};
#endif