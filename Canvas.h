#pragma once

#include <cstdint>

#include "Color.h"

class Canvas {
 private:
  Canvas() = default;
  
 public:
  static Canvas* get_instance();

  void draw_circle(float cx, float cy, float r, Color color);
  void draw_rect(float p_min_x, float p_min_y, float p_max_x, float p_max_y, Color color);
  void draw_digit(float x, float y, int digit, Color color, int block_size_in_pixels = 2);
  
  bool is_in_bounds(int x, int y);
};