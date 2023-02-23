#include "Arduino.h"
#include "FastLED.h"

#include "Pattern.h"
#include "../utils.h"

class SolidColor : Pattern {
public:
    struct Opts {
        CRGBSet leds;
        CHSV color;  
    };

    SolidColor(Opts opts) : leds(opts.leds), color(opts.color) {}

    void run() {
        this->leds = color;
        FastLED.show();
    }

private:
    CRGBSet leds;
    CRGB color;
};
