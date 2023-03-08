#include "FastLED.h"
#include "OneButton.h"

#include "src/config.h"

#include "src/Direction.h"
#include "src/Patterns/Pattern.h"
#include "src/Patterns/SolidColor.h"
#include "src/Patterns/SinBounce.h"
#include "src/Patterns/Pulse.h"
#include "src/Patterns/Rezz.h"
#include "src/Patterns/Strobe.h"
#include "src/Patterns/Twinkle.h"

uint8_t BRIGHTNESS = (BRIGHTNESS_PERCENT * 255) / 100;

CRGB _leds[NUM_LEDS];

CRGBSet leds(_leds, NUM_LEDS);
CRGBSet outer(leds(0, 15));
CRGBSet center(leds(16, 16));
CRGBSet inner(leds(17, 22));

OneButton button;

void setup() {
    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    // Set up button
    // OneButton has no option for INPUT_PULLDOWN, so we have to override the pinMode after creating our OneButton
    button = OneButton(BUTTON_PIN, false, false);
    pinMode(BUTTON_PIN, INPUT_PULLDOWN);

    button.attachClick([]() {
        Serial.println("Button clicked!");
    });

    // Clear all LEDs
    leds.fill_solid(CRGB::Black);
    FastLED.show();
}

Twinkle::Opts opts = {
    leds: leds,
    color: CHSV(0, 0, 255),
};
Twinkle pattern = Twinkle(opts);

void loop() {
    pattern.run();

    button.tick();
}
