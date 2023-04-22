#pragma once

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
#include "Patterns/Off.h"

typedef std::function<std::unique_ptr<Pattern>()> PatternFactory;

// make_unique polyfill since we're on C++11
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

Palette defaultPalette = { CHSV(0, 0, 255) };

std::vector<PatternFactory> PATTERN_FACTORIES = {
    [] {
        return make_unique<Pulse>(
            Pulse::Opts {
                zones: rings,
                numZones: numRings,
                palette: defaultPalette,
                direction: Direction::Forward,
            }
        );
    },
    [] {
        return make_unique<Pulse>(
            Pulse::Opts {
                zones: rings,
                numZones: numRings,
                palette: defaultPalette,
                direction: Direction::Backward,
            }
        );
    },
    [] {
        return make_unique<Rezz>(
            Rezz::Opts {
                zones: rings,
                numZones: numRings,
                palette: defaultPalette,
            }
        );
    },
    [] {
        // TODO need to support multiple patterns at once so we can style zones differently
        return make_unique<SinBounce>(
            SinBounce::Opts {
                leds: outer,
                palette: defaultPalette,
            }
        );
    },
    [] {
        return make_unique<SolidColor>(
            SolidColor::Opts {
                leds,
                palette: defaultPalette,
            }
        );
    },
    [] {
        return make_unique<Strobe>(
            Strobe::Opts {
                leds,
                bpm: 300,
                palette: defaultPalette,
            }
        );
    },
    [] {
        return make_unique<Strobe>(
            Strobe::Opts {
                leds,
                bpm: 600,
                palette: defaultPalette,
            }
        );
    },
    [] {
        return make_unique<Strobe>(
            Strobe::Opts {
                leds,
                bpm: 1200,
                palette: defaultPalette,
            }
        );
    },
    [] {
        return make_unique<Twinkle>(
            Twinkle::Opts {
                leds,
                palette: defaultPalette,
            }
        );
    },
    [] {
        return make_unique<Off>(
            Off::Opts { leds }
        );
    },
};
