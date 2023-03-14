#pragma once

#include "Color.h"
#include "Drawable.h"

class Background : public Drawable {
 public:
  explicit Background(Color color) : color(color) {};
  
  void draw() override;
 
 private:
  Color color;
};