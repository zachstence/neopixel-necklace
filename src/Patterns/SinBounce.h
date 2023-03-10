#include "Arduino.h"
#include "FastLED.h"

#include "Pattern.h"
#include "../utils.h"

class SinBounce : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
        CHSV color;  
    };

    SinBounce(Opts opts) : leds(opts.leds), color(opts.color) {}

    void run()  {
        auto top = 10;
        auto loops = 4;

        uint8_t sinBeat = beatsin8(15, 0, this->leds.len * loops, 0, 0);
        auto i = (sinBeat + top) % this->leds.len;
        this->leds[i] = this->color;

        fadeBrightnessBy(this->leds, 5);

        FastLED.show();
    }


protected:
    CRGBSet leds;
    CHSV color;
};
