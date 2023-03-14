#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Color.h"
#include "Engine.h"
#include "Statics.h"
#include "Background.h"
#include "SpinningCircles.h"
#include "Particles.h"
#include "Counter.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_RETURN)
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  schedule_quit_game() - quit game after act()

SpinningCircles* spinning_circles;
Particles* particles;
Background* background;
Counter* counter;

// initialize game data in this function
void initialize()
{
  auto bg_color = Color(82, 178, 207);
  auto big_circle_color = Color(126, 196, 207);
  auto small_circles_color = Color(255, 255, 255);
  auto text_color = Color(255, 255, 255);
  
  background = new Background(bg_color);
  
  spinning_circles = new SpinningCircles(
    SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2,
    SCREEN_WIDTH / 6,
    M_PI / 1.5,
    SCREEN_WIDTH / 25,
    big_circle_color,
    small_circles_color
  );
  
  counter = new Counter(
    SCREEN_WIDTH - 10,
    20,
    text_color,
    10
  );
  
  auto bad_color = Color(255, 255, 255);
  auto good_color = Color(0, 0, 0);
  
  const int FIRE_RATE = 3;
  const float BAD_PROB = 0.75;
  const float PROJECTILE_SIZE = SCREEN_WIDTH / 32;
  
  particles = new Particles(
    FIRE_RATE,
    BAD_PROB,
    PROJECTILE_SIZE,
    bad_color,
    good_color
  );
  
  drawables.push_back(background);
  drawables.push_back(spinning_circles);
  drawables.push_back(particles);
  drawables.push_back(counter);
  
  game_objects.push_back(spinning_circles);
  game_objects.push_back(particles);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();

  for (auto& o : game_objects) {
    o->act(dt);
  }
  
  auto& particle_list = particles->get_particles();
  auto collisions = spinning_circles->collide(particle_list);
  
  for (auto& id : collisions) {
    if (particle_list[id].type == 1) {
      schedule_quit_game();
    } else {
      particle_list.erase(id);
      counter->increment(1);
    }
  }
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

//  for (int i = 0; i < SCREEN_HEIGHT; i++) {
//    buffer[i][i] = 0xFFFFFFFF;
//     buffer[i][i + 30] = 0xFFFFFFFF;
//  }

  for (auto& d : drawables) {
    d->draw();
  }
}

// free game data in this function
void finalize()
{
  delete spinning_circles;
  delete particles;
  delete background;
}

