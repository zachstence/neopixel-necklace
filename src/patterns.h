#include <vector>
#include <memory>
#include <functional>

#include "leds.h"
#include "Patterns/Pattern.h"
#include "Patterns/SolidColor.h"

typedef std::function<std::unique_ptr<Pattern>()> PatternFactory;

std::vector<PatternFactory> PATTERN_FACTORIES = {
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

uint8_t patternIndex = 0;
std::unique_ptr<Pattern> currentPattern;

void cyclePattern() {
    patternIndex = (patternIndex + 1) % PATTERN_FACTORIES.size();
    currentPattern = std::move(PATTERN_FACTORIES[patternIndex]());
    Serial.printf("patternIndex = %d\n", patternIndex);
}
