#include "FastLED.h"

#include "Pattern.h"

class Off : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
    };

    Off(Opts opts): Pattern("Off", {}), leds(opts.leds) {}

    void run() {
        this->leds = CRGB::Black;
        FastLED.show();
    }

private:
    CRGBSet leds;
};
