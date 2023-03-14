#include "Counter.h"
#include "Canvas.h"
#include "Engine.h"

#include <string>
#include <iostream>

int char_to_digit(char x) {
  return x - '0';
}

void Counter::draw() {
  std::string cnt_as_string = std::to_string(counter);
  float digit_length = 4 * block_size_in_pixels;
  
  float x_start_left_upper = x_right_upper - digit_length * cnt_as_string.length();
  
  for (int i = 0; i < cnt_as_string.length(); i++) {
    int digit = char_to_digit(cnt_as_string[i]);
    
    Canvas::get_instance()->draw_digit(
      y_right_upper,
      x_start_left_upper + i * digit_length,
      digit,
      text_color,
      block_size_in_pixels);
  }
}

void Counter::increment(int d) {
  counter += d;
}
