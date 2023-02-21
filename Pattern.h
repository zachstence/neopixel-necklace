#pragma once

#include "FastLED.h"

class Pattern {
public:
    Pattern(CRGBSet leds) : leds(leds) {};

    virtual void run() = 0;

protected:
    CRGBSet leds;
};
