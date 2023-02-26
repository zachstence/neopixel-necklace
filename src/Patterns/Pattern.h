#pragma once

#include "FastLED.h"

class Pattern {
public:
    Pattern() {}

    virtual void run() = 0;
};
