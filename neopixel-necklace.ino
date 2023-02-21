#include "FastLED.h"

#define NUM_LEDS 23
#define LEDS_PIN 1

CRGB _leds[NUM_LEDS];

CRGBSet leds(_leds, NUM_LEDS);
CRGBSet outer(leds(0, 15));
CRGBSet center(leds(16, 16));
CRGBSet inner(leds(17, 22));

auto outerColor = CHSV(120, 255, 255);
auto innerColor = CHSV(100, 255, 255);
auto centerColor = CHSV(160, 255, 255);

void setup() { 
    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(70);

    // Clear all LEDs
    leds.fill_solid(CRGB::Black);
    FastLED.show();
}

uint8_t c = 0;
uint8_t dimBy = 70;

void fadeBrightnessBy(CRGBSet leds, uint8_t fadeBy) {
    for (auto &led : leds) {
        auto hsv = rgb2hsv_approximate(led);
        auto newV = max(0, hsv.v - fadeBy);
        led = CHSV(hsv.h, hsv.s, newV);
    }
}

void loop() {
    auto top = 10;

    auto loops = 4;
    uint8_t sinBeat = beatsin8(15, 0, outer.len * loops, 0, 0);
    auto i = (sinBeat + top) % outer.len;
    outer[i] = outerColor;
    fadeBrightnessBy(outer, 5);
    FastLED.show();
}
