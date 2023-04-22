#include "Arduino.h"
#include "FastLED.h"

#include "Pattern.h"
#include "../utils.h"

class SolidColor : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
        Palette palette;  
    };

    SolidColor(Opts opts) : Pattern("SolidColor", opts.palette), leds(opts.leds) {
        this->setPalette(opts.palette);
    }

    void run() override {
        this->leds = color;
        FastLED.show();
    }

    void setPalette(Palette palette) {
        this->color = palette.at(0);
    }

private:
    CRGBSet leds;
    CRGB color;
};
