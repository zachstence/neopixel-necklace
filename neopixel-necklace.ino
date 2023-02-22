#include "FastLED.h"

#include "config.h"

#include "SolidColor.h"
#include "SinBounce.h"
#include "Pulse.h"

CRGB _leds[NUM_LEDS];

CRGBSet leds(_leds, NUM_LEDS);
CRGBSet outer(leds(0, 15));
CRGBSet center(leds(16, 16));
CRGBSet inner(leds(17, 22));

void setup() { 
    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(70);

    // Clear all LEDs
    leds.fill_solid(CRGB::Black);
    FastLED.show();
}

CRGBSet zones[] = {center, inner, outer};

Pulse pulse = Pulse(zones, 3, CHSV(234, 255, 255));

void loop() {
    pulse.run();
}
