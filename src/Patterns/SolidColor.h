#include "Arduino.h"
#include "FastLED.h"

#include "Pattern.h"
#include "../utils.h"

class SolidColor : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
        CHSV color;  
    };

    SolidColor(Opts opts) : Pattern("SolidColor"), leds(opts.leds), color(opts.color) {
        Serial.println("SolidColor()");
    }

    ~SolidColor() {
        Serial.println("~SolidColor()");
    }

    void run() override {
        EVERY_N_SECONDS(1) {
            Serial.println("SolidColor.run()");
        }
        this->leds = color;
        FastLED.show();
    }

private:
    CRGBSet leds;
    CRGB color;
};
