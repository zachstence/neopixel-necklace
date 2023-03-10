#include <vector>
#include <memory>
#include <functional>

#include "leds.h"
#include "Patterns/Pattern.h"
#include "Patterns/SolidColor.h"

typedef std::function<std::unique_ptr<Pattern>()> PatternFactory;

// make_unique polyfill since we're on C++11
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

std::vector<PatternFactory> PATTERN_FACTORIES = {
    [] {
        return make_unique<SolidColor>(
            SolidColor::Opts {
                leds,
                color: CHSV(0, 255, 255),
            }
        );
    },
    [] {
        return make_unique<SolidColor>(
            SolidColor::Opts {
                leds,
                color: CHSV(100, 255, 255),
            }
        );
    },
    [] {
        return make_unique<SolidColor>(
            SolidColor::Opts {
                leds,
                color: CHSV(200, 255, 255),
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
