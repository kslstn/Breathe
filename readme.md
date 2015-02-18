Blinking LEDs are awesome indicators for say, letting you know the oil level in your car engine is low and you need to stop your car. Not so much for your home automation projects that need some indicator lights. You know that LED on MacBooks that blinks like the computer is breathing slowly? That's much nicer ain't it. Linear fades are so ugly!

Here's the Breathe library for you to get the same effect in your Arduino projects. If you want, you can set the speed of the effect. You don't have to.

#How to use#
- Download the files and put the complete Breathe folder in your Arduino libraries folder. Just search 'Arduino library' if you need help with that.
- Use Breathe.set(LED_PIN); to start the effect, Breathe.set(LED_PIN, LOW) to stop it. Instead of LED_PIN you insert the number of the pin that controls your LED.
- Check the examples for more options.

#Math stuff#
Linear fades on LEDs don't look linear: it's as if the bright part of the transition takes much longer. I searched the web for 'breathing LED effect' and found [Sean Voisen](
http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/) had given that some thought as well. The conclusion of that blog post is that this equation creates a pleasing, relatable breathing effect, similar to that on Apple laptops: f(x) = e^sin(x).
With some adjustments for phase and amplitude, that equation is used in this library.