#include "FastLED.h"

#include "../utils.h"
#include "../Direction.h"
#include "Pattern.h"

class Pulse : public Pattern {
public:
    struct Opts {
        CRGBSet *zones;
        uint8_t numZones;
        Palette palette;
        Direction direction;
    };

    Pulse(Opts opts):
        Pattern("Pulse", opts.palette),
        zones(opts.zones),
        numZones(opts.numZones),
        direction(opts.direction)
    {
        this->setPalette(opts.palette);
    }

    void run() {
        for (auto i = 0; i < this->numZones; i++) {
            auto phaseOffset = 255 - this->zonePhaseOffset * i;
            auto highOffset = this->zoneHighOffset * i;

            uint8_t v = beatsin8(this->bpm, 0, 255 - highOffset, 0, phaseOffset);

            // Round 10 down to zero to prevent hues from turning red
            if (v < 10) {
                v = 0;
            }

            auto _i = this->direction == Forward ? i : (this->numZones - 1) - i;
            this->zones[_i] = CHSV(this->color.h, this->color.s, v);
        }

        FastLED.show();
    }

    void setPalette(Palette palette) {
        this->color = palette.at(0);
    }

protected:
    CRGBSet *zones;
    uint8_t numZones;
    CHSV color;
    Direction direction;

private:
    // Controls how fast the pattern plays (beats per minute)
    uint8_t bpm = 32;

    // Dim each zone by this amount compared to the previous zone
    // Lower number means later zones are just as bright as earlier zones
    // Higher number means later zones are dimmer than earlier zones
    uint8_t zoneHighOffset = 70;

    // The phase difference between each of the zones (0-255)
    // Lower number means they all fire at once
    // Higher number means they all fire at a regular interval from each other
    uint8_t zonePhaseOffset = 30;
};
