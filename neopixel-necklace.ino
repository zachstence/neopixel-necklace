#include "FastLED.h"
#include "OneButton.h"

#include "src/config.h"
#include "src/patterns.h"
#include "src/palettes.h"

OneButton button;

void setup() {
    setupButton();
    setupLeds();

    currentPattern = std::move(PATTERN_FACTORIES[0]());
}

void loop() {
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
