#include <vector>

#include "FastLED.h"

uint8_t paletteIndex = 0;

std::vector<CRGBPalette16> PALETTES = {
    
};

void cyclePalette() {
    paletteIndex = (paletteIndex + 1) % PALETTES.size();
    Serial.printf("paletteIndex = %d\n", paletteIndex);
}

CRGBPalette16* currentPalette() {
    return &PALETTES[paletteIndex];
}
