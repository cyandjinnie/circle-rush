#pragma once

#include "Drawable.h"
#include "GameObject.h"
#include "Color.h"

#include <unordered_map>

class Particles : public Drawable, public GameObject {
 public:
  struct Particle {
    float x;
    float y;
    float vx;
    float vy;
    double size;
    int type;
    float ttl;
  };
  
  Particles(float fire_rate, float good_prob, float size, Color bad_c, Color good_c)
    : fire_rate(fire_rate), good_prob(good_prob), size(size), bad_c(bad_c), good_c(good_c) {
  }
  
  void act(float dt);
  void spawn_new_particles(float dt);
  void draw();
  std::unordered_map<int, Particle>& get_particles();
 
 private:
  
  int sample_type();
  int sample_bool(float p);
  
  float size;
  float fire_rate;
  float good_prob;
  
  Color good_c;
  Color bad_c;
  
  float time_last_spawned = 0;
  int counter = 0;
  
  std::unordered_map<int, Particle> storage;
};