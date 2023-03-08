#pragma once

#include "FastLED.h"

void fadeBrightnessBy(CRGBSet leds, uint8_t fadeBy) {
    for (auto &led : leds) {
        auto hsv = rgb2hsv_approximate(led);

        auto newV = max(0, hsv.v - fadeBy);

        // Round 10 down to zero to prevent hues from turning red
        if (newV < 10) {
            newV = 0;
        }

        led = CHSV(hsv.h, hsv.s, newV);
    }
}

CHSV randomColor() {
    uint8_t h = random8();
    return CHSV(h, 255, 255);
}

// Recursive function to return gcd of a and b
int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
 
// Function to return LCM of two numbers
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}