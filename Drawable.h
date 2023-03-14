#pragma once

#include <cstdint>

class Drawable {
public:
    virtual void draw() = 0;
    virtual ~Drawable() = default;
};