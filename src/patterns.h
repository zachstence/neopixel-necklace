#include <vector>
#include <memory>
#include <functional>

#include "leds.h"
#include "Patterns/Pattern.h"
#include "Patterns/SolidColor.h"

uint8_t patternIndex = 0;

typedef std::function<std::unique_ptr<Pattern>()> PatternFactory;

std::vector<PatternFactory> PATTERNS = {
    []() {
        return std::unique_ptr<Pattern>(
            new SolidColor(
                SolidColor::Opts {
                    leds,
                    color: CHSV(0, 255, 255),
                }
            )
        );
    },
    []() {
        return std::unique_ptr<Pattern>(
            new SolidColor(
                SolidColor::Opts {
                    leds,
                    color: CHSV(100, 255, 255),
                }
            )
        );
    },
    []() {
        return std::unique_ptr<Pattern>(
            new SolidColor(
                SolidColor::Opts {
                    leds,
                    color: CHSV(200, 255, 255),
                }
            )
        );
    },
};

void cyclePattern() {
    patternIndex = (patternIndex + 1) % PATTERNS.size();
    Serial.printf("patternIndex = %d\n", patternIndex);
}

PatternFactory currentPattern() {
    return PATTERNS[patternIndex];
}
