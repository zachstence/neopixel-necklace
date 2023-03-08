#include <numeric>

#include "FastLED.h"

#include "Pattern.h"
#include "../utils.h"

class Rezz : Pattern {
public:
    struct Opts {
        CRGBSet *zones;
        uint8_t numZones;
        CHSV onColor;
        CHSV offColor;
    };

    Rezz(Opts opts):
        zones(opts.zones),
        numZones(opts.numZones),
        onColor(opts.onColor),
        offColor(opts.offColor)
    {
        for (auto i = 0; i < this->numZones; i++) {
            this->zoneLenLcm = lcm(this->zoneLenLcm, this->zones[i].len);
        }
    }

    void run() {
        EVERY_N_MILLIS(this->periodMs / this->zoneLenLcm) {
            this->offset = (this->offset + 1) % this->zoneLenLcm;
        }

        for (auto i = 0; i < this->numZones; i++) {
            auto zone = this->zones[i];

            auto zoneOffset = this->offset % zone.len;

            // Set all to offColor
            zone = this->offColor;

            // This will truncate, so in zone.len is odd there will be an odd LED out
            // Unfortunately there's not a great way to do this pattern on an odd number of LEDs
            uint8_t halfLen = zone.len / 2;
            uint8_t onQuarterLen = floor(halfLen / 2.0);

            // Set on LEDs on both halves
            for (auto i = 0; i < onQuarterLen; i++) {
                auto i1 = (i + zoneOffset) % zone.len;
                auto i2 = (i + zoneOffset + halfLen) % zone.len;
                zone[i1] = onColor;
                zone[i2] = onColor;
            }
        }
        FastLED.show();
    }

protected:
    CRGBSet *zones;
    uint8_t numZones;
    CHSV onColor;
    CHSV offColor;

    // Controls how fast the pattern plays (length of one rotation (period) in milliseconds)
    int periodMs = 5000;

private:
    int offset = 0;
    int zoneLenLcm = 1;
};
