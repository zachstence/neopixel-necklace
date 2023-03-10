#include <vector>
#include <memory>
#include <functional>

#include "leds.h"
#include "utils.h"
#include "Patterns/Pattern.h"
#include "Patterns/Pulse.h"
#include "Patterns/Rezz.h"
#include "Patterns/SinBounce.h"
#include "Patterns/SolidColor.h"
#include "Patterns/Strobe.h"
#include "Patterns/Twinkle.h"

typedef std::function<std::unique_ptr<Pattern>()> PatternFactory;

// make_unique polyfill since we're on C++11
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

CHSV primaryColor = rgb2hsv_approximate(CRGB::SeaGreen);
CHSV secondaryColor = rgb2hsv_approximate(CRGB::Amethyst);
CHSV tertiaryColor = rgb2hsv_approximate(CRGB::PowderBlue);

std::vector<PatternFactory> PATTERN_FACTORIES = {
    [] {
        return make_unique<Pulse>(
            Pulse::Opts {
                zones: rings,
                numZones: numRings,
                color: primaryColor,
                direction: Direction::Forward,
            }
        );
    },
    [] {
        return make_unique<Pulse>(
            Pulse::Opts {
                zones: rings,
                numZones: numRings,
                color: primaryColor,
                direction: Direction::Backward,
            }
        );
    },
    [] {
        return make_unique<Rezz>(
            Rezz::Opts {
                zones: rings,
                numZones: numRings,
                onColor: primaryColor,
                offColor: CHSV(primaryColor.h, primaryColor.s, 50),
            }
        );
    },
    [] {
        // TODO need to support multiple patterns at once so we can style zones differently
        return make_unique<SinBounce>(
            SinBounce::Opts {
                leds: outer,
                color: CHSV(primaryColor.h, primaryColor.s, 50),
            }
        );
    },
    [] {
        return make_unique<SolidColor>(
            SolidColor::Opts {
                leds,
                color: primaryColor,
            }
        );
    },
    [] {
        return make_unique<Strobe>(
            Strobe::Opts {
                leds,
                bpm: 300,
                color: primaryColor,
            }
        );
    },
    [] {
        return make_unique<Twinkle>(
            Twinkle::Opts {
                leds,
                color: primaryColor,
            }
        );
    },
};

uint8_t patternIndex = 0;
std::unique_ptr<Pattern> currentPattern;

void cyclePattern() {
    patternIndex = (patternIndex + 1) % PATTERN_FACTORIES.size();
    currentPattern = PATTERN_FACTORIES[patternIndex]();
    Serial.printf("patternIndex = %d\n", patternIndex);
}
