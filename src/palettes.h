#pragma once

#include <vector>

#include "FastLED.h"

typedef std::vector<CHSV> Palette;

std::vector<Palette> PALETTES = {
    { CHSV(   0,   0, 255 ) }, // White
    { CHSV(   0, 255, 255 ) }, // Red
    { CHSV( 220, 255, 255 ) }, // Fuchsia
    { CHSV( 200, 255, 255 ) }, // Lavender
    { CHSV( 173, 255, 255 ) }, // Cobalt
    { CHSV( 152, 255, 255 ) }, // Powder blue
    { CHSV( 130, 255, 255 ) }, // Cyan
    { CHSV( 113, 255, 255 ) }, // Sea foam
    { CHSV(  88, 255, 255 ) }, // Lime
    { CHSV(  41, 255, 255 ) }, // Yellow
    { CHSV(  24, 255, 255 ) }, // Orange
    { CHSV(  13, 255, 255 ) }, // Red-orange
};
