#pragma once

#include <vector>

#include "FastLED.h"

typedef std::vector<CHSV> Palette;

std::vector<Palette> PALETTES = {
    { CHSV(0, 0, 255), CHSV(0, 0, 170), CHSV(0, 0, 85) }, // Shades of white
    { rgb2hsv_approximate(CRGB::Cyan), rgb2hsv_approximate(CRGB::Amethyst), rgb2hsv_approximate(CRGB::Aquamarine) },
    { rgb2hsv_approximate(CRGB::OrangeRed), rgb2hsv_approximate(CRGB::Orange), rgb2hsv_approximate(CRGB::DeepPink) },
};
