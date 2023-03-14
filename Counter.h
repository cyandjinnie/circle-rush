#pragma once

#include <cstdint>

#include "Drawable.h"
#include "Color.h"

class Counter : public Drawable {
 public:
  Counter(float x_right_upper, float y_right_upper, Color color, int block_size_in_pixels = 10)
    : x_right_upper(x_right_upper), y_right_upper(y_right_upper), text_color(color), block_size_in_pixels(block_size_in_pixels) {}
  
  void draw() override;
  void increment(int d);
 
 private:
  uint64_t counter = 0;
  float x_right_upper;
  float y_right_upper;
  int block_size_in_pixels;
  Color text_color;
};