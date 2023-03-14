#include "Particles.h"
#include "Canvas.h"
#include "Engine.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

void Particles::draw() {
  for (auto& [_, particle] : storage) {
    switch (particle.type) {
      case 0:
        Canvas::get_instance()->draw_circle(particle.x, particle.y, size / sqrt(2), bad_c);
        break;
      case 1:
        Canvas::get_instance()->draw_rect(
          particle.x - size / 2,
          particle.y - size / 2,
          particle.x + size / 2,
          particle.y + size / 2,
          good_c
        );
        break;
    }
  }
}

int Particles::sample_type() {
  return sample_bool(good_prob);
}

int Particles::sample_bool(float p) {
  float random_decimal = float(rand() % 10000) / 10000;
  return random_decimal < p;
}

float sample_angle() {
  float random_decimal = float(rand() % 10000) / 10000;
  return M_PI * 0.5 + ((random_decimal - 0.5) * 0.25 * M_PI);
}

void Particles::act(float dt) {
  std::vector<int> cleanup_ids;
  
  for (auto& [id, particle] : storage) {
    particle.ttl -= dt;
    if (particle.ttl < 0) {
      cleanup_ids.push_back(id);
    } else {
      particle.x += particle.vx * dt;
      particle.y += particle.vy * dt;
    }
  }
  
  // Clean up
  for (auto& id : cleanup_ids) {
    storage.erase(id);
  }
  
  spawn_new_particles(dt);
}

void Particles::spawn_new_particles(float dt) {
  int num_to_spawn = 0;
  
  if (time_last_spawned > fire_rate) {
    num_to_spawn = 1;
    time_last_spawned = 0;
  } else {
    num_to_spawn = 0;
    time_last_spawned += dt;
  }
  
  float vx = SCREEN_WIDTH / 5;
  float vy = SCREEN_HEIGHT / 5;
  float ttl = 10;
  
  for (int i = 0; i < num_to_spawn; i++) {
    int type = sample_type();
    float angle = sample_angle();
    float r = SCREEN_WIDTH / 1.5;
    float x_c = SCREEN_WIDTH / 2;
    float y_c = SCREEN_HEIGHT / 2;
    
    auto particle = Particle{
      x_c, // x_c + r * cos(angle),
      y_c - r, // y_c + r * sin(angle),
      vx * cos(angle),
      vy * sin(angle),
      size / sqrt(2),
      type,
      ttl
    };
    
    int id = counter++;
    storage.insert({ id, std::move(particle) });
  }
}

std::unordered_map<int, Particles::Particle>& Particles::get_particles() {
  return storage;
}