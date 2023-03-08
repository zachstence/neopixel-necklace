#include "FastLED.h"

#include "Pattern.h"

class Strobe : Pattern {
public:
    struct Opts {
        CRGBSet leds;
        int bpm;
        CHSV color;
    };
    
    Strobe(Opts opts):
        leds(opts.leds),
        bpm(opts.bpm),
        color(opts.color)
    {
        this->periodMs = 60000 / this->bpm;
    }

    void run() {
        EVERY_N_MILLIS(this->periodMs) {
            this->on = !this->on;
        }

        if (this->on) {
            this->leds = this->color;
        } else {
            this->leds = CRGB::Black;
        }

        FastLED.show();
    }

protected:
    CRGBSet leds;
    int bpm;
    CHSV color;

private:
    int periodMs;
    bool on = true;
};