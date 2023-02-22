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
