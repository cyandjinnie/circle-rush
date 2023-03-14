#pragma once

#include "GameObject.h"
#include "Drawable.h"
#include "Particles.h"
#include "Color.h"

#include <math.h>
#include <unordered_map>
#include <vector>

double floor_to_pi(double x);

class SpinningCircles : public Drawable, public GameObject {
 public:
  SpinningCircles(float x, float y, float r, float v_rot, float small_r, Color main_circle_c, Color small_circles_c)
    : x(x), y(y), r(r), rotation_speed(v_rot), small_r(small_r), main_circle_c(main_circle_c), small_circles_c(small_circles_c) {
    for (int i = 0; i < num_trace_circles; i++) {
      trace_circles_ttl.push_back(0.f);
      trace_circles_fixed_angles.push_back(floor_to_pi(2 * M_PI * i / num_trace_circles));
    }
  }
  
  void act(float dt) override;
  void draw() override;
  std::vector<int> collide(std::unordered_map<int, Particles::Particle>& particles);
  float get_trace_circle_rad_by_ttl(float ttl);
  void activate_traces_for_angle(float dt, int rotation_mode, float angle, float new_angle);
  
 private:
  Color main_circle_c;
  Color small_circles_c;
  
  const int num_trace_circles = 16;
  const float max_trace_circle_ttl = 0.5;
  std::vector<float> trace_circles_ttl;
  std::vector<float> trace_circles_fixed_angles;
  
  float x;
  float y;
  float r;
  float small_r;
  
  double rotation_speed;
  double angle = 0;
};