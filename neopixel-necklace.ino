#include "FastLED.h"

#include "src/config.h"

#include "src/Direction.h"
#include "src/Patterns/Pattern.h"
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

SinBounce::Opts outerOpts = {
    leds: outer,
    color: CHSV(100, 255, 255),
};
SinBounce outerPattern = SinBounce(outerOpts);

SinBounce::Opts innerOpts = {
    leds: inner,
    color: CHSV(150, 255, 255),
};
SinBounce innerPattern = SinBounce(innerOpts);

Pulse::Opts centerOpts = {
    zones: &center,
    numZones: 1,
    color: CHSV(200, 255, 255),
    direction: Direction::Forward,
};
Pulse centerPattern = Pulse(centerOpts);

void loop() {
    outerPattern.run();
    innerPattern.run();
    centerPattern.run();
}
