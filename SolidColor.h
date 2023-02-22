#include "Arduino.h"
#include "FastLED.h"

#include "Pattern.h"
#include "utils.h"

class SolidColor : Pattern {
public:
    SolidColor(CRGBSet leds, CRGB color);

    void run();

private:
    CRGBSet leds;
    CRGB color;
};

SolidColor::SolidColor(CRGBSet leds, CRGB color) : leds(leds), color(color) {}

void SolidColor::run() {
    this->leds.fill_solid(color);

    for (auto i = 0; i < this->leds.len; i++) {
        CRGB led = this->leds[i];
        Serial.printf("1    \tLED %d is RGB %d %d %d\n", i, led.r, led.g, led.b);
    }

    for (CRGB led : this->leds) {
        Serial.printf("2    \tLED ? is RGB %d %d %d\n", led.r, led.g, led.b);
    }

    FastLED.show();
}
