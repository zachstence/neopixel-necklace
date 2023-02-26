#include "FastLED.h"
#include "OneButton.h"

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

OneButton button;

CHSV outerColor = randomColor(255);
CHSV innerColor = randomColor(255);
CHSV centerColor = randomColor(255);

SinBounce::Opts outerOpts = {
    leds: outer,
    color: outerColor,
};
SinBounce outerPattern = SinBounce(outerOpts);

SinBounce::Opts innerOpts = {
    leds: inner,
    color: innerColor,
};
SinBounce innerPattern = SinBounce(innerOpts);

Pulse::Opts centerOpts = {
    zones: &center,
    numZones: 1,
    color: centerColor,
    direction: Direction::Forward,
};
Pulse centerPattern = Pulse(centerOpts);

void initPatterns() {
    Serial.println("initPatterns called");
    SinBounce::Opts outerOpts = {
        leds: outer,
        color: outerColor,
    };
    outerPattern = SinBounce(outerOpts);

    SinBounce::Opts innerOpts = {
        leds: inner,
        color: innerColor,
    };
    innerPattern = SinBounce(innerOpts);

    Pulse::Opts centerOpts = {
        zones: &center,
        numZones: 1,
        color: centerColor,
        direction: Direction::Forward,
    };
    centerPattern = Pulse(centerOpts);
}

void setup() {
    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(70);

    // Set up button
    // OneButton has no option for INPUT_PULLDOWN, so we have to override the pinMode after creating our OneButton
    button = OneButton(BUTTON_PIN, false, false);
    pinMode(BUTTON_PIN, INPUT_PULLDOWN);

    button.attachClick([]() {
        Serial.println("Button clicked! Generating random colors");
        outerColor = randomColor(255);
        innerColor = randomColor(255);
        centerColor = randomColor(255);
        initPatterns();
    });

    // Clear all LEDs
    leds.fill_solid(CRGB::Black);
    FastLED.show();

    initPatterns();
}

void loop() {
    outerPattern.run();
    innerPattern.run();
    centerPattern.run();

    button.tick();
}
