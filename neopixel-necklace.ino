#include "FastLED.h"

#include "src/config.h"

#include "src/Direction.h"
#include "src/Patterns/SolidColor.h"
#include "src/Patterns/SinBounce.h"
#include "src/Patterns/Pulse.h"

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

Pulse pulse = Pulse(zones, 3, CHSV(150, 255, 255), Direction::Forward);

void loop() {
    pulse.run();
}
