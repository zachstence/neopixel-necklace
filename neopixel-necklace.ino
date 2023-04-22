#include "FastLED.h"
#include "OneButton.h"

#include "src/config.h"
#include "src/patterns.h"
#include "src/palettes.h"
#include "src/leds.h"

OneButton button;

uint8_t patternIndex = 0;
std::unique_ptr<Pattern> currentPattern;

uint8_t paletteIndex = 0;
Palette currentPalette;

void cyclePattern() {
    patternIndex = (patternIndex + 1) % PATTERN_FACTORIES.size();
    currentPattern = PATTERN_FACTORIES[patternIndex]();
    currentPattern->setPalette(currentPalette);
    Serial.printf("patternIndex = %d\n", patternIndex);
}

void cyclePalette() {
    paletteIndex = (paletteIndex + 1) % PALETTES.size();
    currentPalette = PALETTES[paletteIndex];
    currentPattern->setPalette(currentPalette);
    Serial.printf("paletteIndex = %d\n", paletteIndex);
}


////////////////////////


void setup() {
    setupButton();
    setupLeds();

    currentPattern = PATTERN_FACTORIES[patternIndex]();
    currentPalette = PALETTES[paletteIndex];
}

void loop() {
    leds.fill_solid(CRGB::Black);
    currentPattern->run();

    button.tick();
}



///////////////////////////////////////////////////



void setupButton() {
    // OneButton has no option for INPUT_PULLDOWN, so we have to override the pinMode after creating our OneButton
    button = OneButton(BUTTON_PIN, false, false);
    pinMode(BUTTON_PIN, INPUT_PULLDOWN);

    button.attachClick(cyclePattern);
    button.attachDoubleClick(cyclePalette);
}
