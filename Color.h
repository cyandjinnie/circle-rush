#pragma once

#include <cstdint>

class Color {
public:
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        this->color_code = (a << 24) + (r << 16) + (g << 8) + b;
    };

    Color(uint32_t color_code) {
        this->color_code = color_code;
    };

    uint32_t color_code = 0;
};