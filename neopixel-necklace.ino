#include "FastLED.h"

#define NUM_LEDS 23
#define LEDS_PIN 1

CRGB _leds[NUM_LEDS];

CRGBSet leds(_leds, NUM_LEDS);
CRGBSet outer(leds(0, 15));
CRGBSet center(leds(16, 16));
CRGBSet inner(leds(17, 22));

auto outerColor = CHSV(40, 255, 255);
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

void loop() {
    for (auto i = 0; i < outer.len; i++) {
        uint8_t v = max(0, outerColor.v - i * dimBy);
        auto _i = (i + c) % outer.len;
        auto color = CHSV(outerColor.h, outerColor.s, v);
        outer[_i] = color;
    }

    for (auto i = 0; i < inner.len; i++) {
        uint8_t v = max(0, innerColor.v - i * dimBy);
        auto _i = (i + c + 255) % inner.len;
        auto color = CHSV(innerColor.h, innerColor.s, v);
        inner[_i] = color;
    }

    auto centerOffset = c % 30;
    auto centerV = max(0, centerColor.v - centerOffset * 10);
    auto color = CHSV(centerColor.h, centerColor.s, centerV);
    center = color;

    c--;
    FastLED.show();
    delay(50);
}