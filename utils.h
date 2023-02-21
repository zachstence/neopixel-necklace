#pragma once

#include "FastLED.h"

void fadeBrightnessBy(CRGBSet leds, uint8_t fadeBy) {
    for (auto &led : leds) {
        auto hsv = rgb2hsv_approximate(led);
        auto newV = max(0, hsv.v - fadeBy);
        led = CHSV(hsv.h, hsv.s, newV);
    }
}
