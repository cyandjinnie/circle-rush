#include "Canvas.h"
#include "Engine.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <exception>

void Canvas::draw_circle(float cx, float cy, float r, Color color) {
  for (float x_f = cx - r; x_f < cx + r; x_f++) {
    for (float y_f = cy - r; y_f < cy + r; y_f++) {
      int x = round(x_f);
      int y = round(y_f);
      
      if ((cx-x_f)*(cx-x_f) + (cy-y_f)*(cy-y_f) <= r * r && is_in_bounds(x, y)) {
        buffer[x][y] = color.color_code;
      }
    }
  }
}

void Canvas::draw_rect(float p_min_x, float p_min_y, float p_max_x, float p_max_y, Color color) {
  for (int x = static_cast<int>(p_min_x); x < static_cast<int>(p_max_x); x++) {
    for (int y = static_cast<int>(p_min_y); y < static_cast<int>(p_max_y); y++) {
      
      if (is_in_bounds(x, y)) {
        buffer[x][y] = color.color_code;
      }
    }
  }
}

bool Canvas::is_in_bounds(int x, int y) {
    return (0 <= x) && (x < SCREEN_WIDTH) && (0 <= y) && (y < SCREEN_HEIGHT);
}

Canvas* Canvas::get_instance() {
  static Canvas instance;
  
  return &instance;
}

void Canvas::draw_digit(float x, float y, int digit, Color color, int block_size_in_pixels) {
  std::vector<int> pixel_map;
  
  switch (digit) {
    case 0:
      pixel_map = {       0,1,1,
                          1,0,1,
                          1,0,1,
                          1,0,1,
                          1,1,1};
      break;
    case 1:
      pixel_map = {       1,1,0,
                          0,1,0,
                          0,1,0,
                          0,1,0,
                          1,1,1};
      break;
    case 2:
      pixel_map = {       1,1,0,
                          0,0,1,
                          0,1,1,
                          0,1,0,
                          1,1,1};
      break;
    case 3:
      pixel_map = {       1,1,0,
                          0,0,1,
                          0,1,0,
                          0,0,1,
                          1,1,1};
      break;
    case 4:
      pixel_map = {       0,0,1,
                          0,1,1,
                          1,0,1,
                          1,1,1,
                          0,0,1};
      break;
    case 5:
      pixel_map = {       1,1,1,
                          1,0,0,
                          1,1,1,
                          0,0,1,
                          1,1,0};
      break;
    case 6:
      pixel_map = {       0,1,1,
                          1,0,0,
                          1,1,1,
                          1,0,1,
                          1,1,0};
      break;
    case 7:
      pixel_map = {       1,1,1,
                          0,0,1,
                          0,0,1,
                          0,1,0,
                          0,1,0};
      break;
    case 8:
      pixel_map = {       1,1,1,
                          1,0,1,
                          0,1,0,
                          1,0,1,
                          1,1,1};
      break;
    case 9:
      pixel_map = {       0,1,1,
                          1,0,1,
                          1,1,1,
                          0,0,1,
                          1,1,0};
      break;
    default:
      throw std::exception();
  }
  
  std::vector<std::pair<int, int>> colored_pixel_offsets;
  
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      if (pixel_map[i * 3 + j] == 1) {
        colored_pixel_offsets.emplace_back(i, j);
      }
    }
  }
  
  for (auto& [x_offset, y_offset] : colored_pixel_offsets) {
    float x_start = x + (float)(x_offset * block_size_in_pixels);
    float y_start = y + (float)(y_offset * block_size_in_pixels);
    
    for (int i = 0; i < block_size_in_pixels; i++) {
      for (int j = 0; j < block_size_in_pixels; j++) {
        int x_real = round(x_start + i);
        int y_real = round(y_start + j);
        
        if (is_in_bounds(x_real, y_real)) {
          buffer[x_real][y_real] = color.color_code;
        }
      }
    }
  }
}
