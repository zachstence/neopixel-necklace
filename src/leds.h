#include "FastLED.h"

#include "config.h"

uint8_t DEFAULT_BRIGHTNESS = (DEFAULT_BRIGHTNESS_PERCENT * 255) / 100;

CRGB _leds[NUM_LEDS];

CRGBSet leds(_leds, NUM_LEDS);
CRGBSet outer(leds(0, 15));
CRGBSet center(leds(16, 16));
CRGBSet inner(leds(17, 22));

CRGBSet rings[] = {center, inner, outer};
uint8_t numRings = 3;

void setupLeds() {
    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(DEFAULT_BRIGHTNESS);

    // Clear all LEDs
    leds.fill_solid(CRGB::Black);
    FastLED.show();
}
