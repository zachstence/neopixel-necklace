#pragma once

#include "FastLED.h"

class Pattern {
public:
    Pattern() {
        Serial.println("Pattern()");
    }

    Pattern(std::string name): name(name) {
        Serial.printf("Pattern() %s\n", this->name.c_str());
    }

    ~Pattern() {
        Serial.printf("~Pattern() %s\n", this->name.c_str());
    }

    virtual void run() = 0;

protected:
    std::string name;
};
