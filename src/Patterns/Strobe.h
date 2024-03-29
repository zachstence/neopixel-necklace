#include "FastLED.h"

#include "Pattern.h"

class Strobe : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
        int bpm;
        Palette palette;
    };
    
    Strobe(Opts opts):
        Pattern("Strobe", opts.palette),
        leds(opts.leds),
        bpm(opts.bpm)
    {
        this->setPalette(opts.palette),
        this->periodMs = 60000 / this->bpm;
    }

    void run() {
        if (millis() >= this->nextToggle) {
            this->on = !this->on;
            this->nextToggle = millis() + this->periodMs;
        }
        
        if (this->on) {
            this->leds = this->color;
        } else {
            this->leds = CRGB::Black;
        }

        FastLED.show();
    }

    void setPalette(Palette palette) {
        this->color = palette.at(0);
    }

protected:
    CRGBSet leds;
    int bpm;
    CHSV color;

private:
    int periodMs;
    bool on = true;
    int nextToggle = 0;
};