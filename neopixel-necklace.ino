#include "FastLED.h"

#include "config.h"
#include "SolidColor.h"
#include "SinBounce.h"

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

SolidColor solidColor = SolidColor(outer, CRGB(255, 0, 0));

SinBounce sinBounce = SinBounce(outer, CHSV(100, 255, 255));

void loop() {
    // sinBounce.run();
    solidColor.run();
}
