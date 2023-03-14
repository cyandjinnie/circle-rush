#include "SpinningCircles.h"
#include "Canvas.h"
#include "Engine.h"

#include <iostream>

float max(float a, float b) {
  return a < b ? b : a;
}

void SpinningCircles::draw() {
  Canvas::get_instance()->draw_circle(x, y, r, main_circle_c);
  Canvas::get_instance()->draw_circle(x + r * cos(angle), y + r * sin(angle), small_r, small_circles_c);
  Canvas::get_instance()->draw_circle(x - r * cos(angle), y - r * sin(angle), small_r, small_circles_c);
  
  for (int i = 0; i < num_trace_circles; i++) {
    float trace_circle_angle = trace_circles_fixed_angles[i];
    float ttl = trace_circles_ttl[i];
  
    Canvas::get_instance()->draw_circle(
      x - r * cos(trace_circle_angle),
      y - r * sin(trace_circle_angle),
      get_trace_circle_rad_by_ttl(ttl),
      small_circles_c
    );
  }
}

float SpinningCircles::get_trace_circle_rad_by_ttl(float ttl) {
  return 0.8f * small_r * ttl / max_trace_circle_ttl;
}

double floor_to_pi(double x) {
  return atan2(sin(x),cos(x));
}

double floor_to_pi_smart(double x) {
  double y = atan2(sin(x),cos(x));
  
  if (y < -M_PI / 2) {
    return y + M_PI;
  } else if (y > M_PI / 2) {
    return y - M_PI;
  } else {
    return y;
  }
}

void SpinningCircles::activate_traces_for_angle(float dt, int rotation_mode, float angle, float new_angle) {
  for (int i = 0; i < num_trace_circles; i++) {
    float trace_circle_angle = trace_circles_fixed_angles[i];
    
    if (rotation_mode > 0) {
      if (trace_circle_angle > angle && trace_circle_angle < new_angle) {
        // std::cout << "1" << std::endl;
        float t = abs(new_angle - trace_circle_angle) / rotation_speed;
        trace_circles_ttl[i] = max(max_trace_circle_ttl - t, 0);
        trace_circles_ttl[(i + 8) % 16] = max(max_trace_circle_ttl - t, 0);
      }
    } else {
      if (trace_circle_angle > new_angle && trace_circle_angle < angle) {
        // std::cout << "2" << std::endl;
        float t = abs(angle - trace_circle_angle) / rotation_speed;
        trace_circles_ttl[i] = max(max_trace_circle_ttl - t, 0);
        trace_circles_ttl[(i + 8) % 16] = max(max_trace_circle_ttl - t, 0);
      }
    }
  }
}

void SpinningCircles::act(float dt) {
  int rotation_mode = is_key_pressed(VK_SPACE) ? 1 : -1;
  float new_angle = floor_to_pi(angle + rotation_mode * rotation_speed * dt);
  
  // Tick
  for (int i = 0; i < num_trace_circles; i++) {
    trace_circles_ttl[i] = max(trace_circles_ttl[i] - dt, 0);
  }
  
  activate_traces_for_angle(dt, rotation_mode, angle, new_angle);
  activate_traces_for_angle(dt, rotation_mode, floor_to_pi(angle + M_PI), floor_to_pi(new_angle + M_PI));
  
  angle = new_angle;
}

std::vector<int> SpinningCircles::collide(std::unordered_map<int, Particles::Particle> &particles) {
  std::vector<int> collisions;
  
  for (auto& [id, p] : particles) {
    double x1 = x + r * cos(angle);
    double y1 = y + r * sin(angle);
  
    double x2 = x - r * cos(angle);
    double y2 = y - r * sin(angle);
    
    if ((x1-p.x)*(x1-p.x) + (y1-p.y)*(y1-p.y) < (small_r + p.size)*(small_r + p.size)
       || (x2-p.x)*(x2-p.x) + (y2-p.y)*(y2-p.y) < (small_r + p.size)*(small_r + p.size)) {
      collisions.push_back(id);
    }
  }
  
  return collisions;
}
