#include <string>

#include "FastLED.h"

#include "Pattern.h"
#include "../utils.h"

class Twinkle : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
        CHSV color;
    };

    struct TwinkleSpec {
        uint8_t offset;
        int bpm;

        void debug() {
            Serial.printf("TwinkleSpec\n  offset: %d\n  bpm: %d\n", this->offset);
        }
    };

    Twinkle(Opts opts):
        leds(opts.leds),
        color(opts.color)
    {
        Serial.println("new Twinkle()");
        this->specs = new TwinkleSpec[this->leds.len];
        for (auto i = 0; i < this->leds.len; i++) {
            this->specs[i] = this->randomTwinkleSpec();
        }
    }

    ~Twinkle() {
        delete this->specs;
    }

    void run() {
        EVERY_N_SECONDS(1) {
            Serial.println("Twinkle.run()");
        }
        for (auto i = 0; i < this->leds.len; i++) {
            uint8_t v = this->beat(i);
            this->leds[i] = CHSV(this->color.h, this->color.s, v);
        }

        FastLED.show();
    }

protected:
    CRGBSet leds;
    CHSV color;

private:
    int bpmMin = 20;
    int bpmMax = 40;

    TwinkleSpec *specs;

    uint8_t beat(uint8_t i) {
        auto spec = this->specs[i];
        return beatsin8(spec.bpm, 0, this->color.v, 0, spec.offset);
    }

    TwinkleSpec randomTwinkleSpec() {
        auto offset = random8();
        auto bpm = random(this->bpmMin, this->bpmMax + 1);

        return TwinkleSpec { offset, bpm };
    }
};
