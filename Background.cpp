#include "Background.h"
#include "Canvas.h"
#include "Engine.h"

void Background::draw() {
  Canvas::get_instance()->draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, this->color);
}