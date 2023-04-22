#pragma once

#include "FastLED.h"

#include "../palettes.h"

class Pattern {
public:
    Pattern() {
        Serial.println("Pattern()");
    }

    Pattern(std::string name, Palette palette): name(name), palette(palette) {
        Serial.printf("Pattern() %s\n", this->name.c_str());
    }

    virtual ~Pattern() {
        Serial.printf("~Pattern() %s\n", this->name.c_str());
    }

    virtual void run() = 0;

    virtual void setPalette(Palette palette) {}

    CHSV getColor(uint8_t index) {
        return this->palette.at(0);
        // return this->palette.at(index % this->palette.size());
    }

protected:
    std::string name;
    Palette palette;
};
