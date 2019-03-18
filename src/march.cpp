//
// Created by disconcision on 16/03/19.
//

#include "march.h"

#include <iostream>

vec3 normal(double (&sdf)(vec3), const vec3& p) {
  double EPSILON = 1e-3;
  vec3 ex = vec3(EPSILON,0,0),
       ey = vec3(0,EPSILON,0),
       ez = vec3(0,0,EPSILON);
  return vec3(sdf(p + ex) - sdf(p - ex),
              sdf(p + ey) - sdf(p - ey),
              sdf(p + ez) - sdf(p - ez)).normalized();
}


double march(
        const Ray& ray,
        double (&sdf)(vec3),
        const double min_d,
        const double max_d,
        int& hit_id,
        vec3& n) {

  double depth = min_d;
  unsigned MAX_STEPS = 60;
  double EPSILON = 1e-8;

  for (unsigned i=0; i < MAX_STEPS; i++) {
    vec3 p = ray.origin + depth*ray.direction;
    double d = sdf(p);
    //std::cout << "steps: " << i << " depth: " << depth
    //  << " sdf(p): " << d << "\np: " << p << "\n";
    if (d < EPSILON) {
      n = normal(sdf, p);
      return depth;
    }
    depth += d;
    if (depth >= max_d) {
      return max_d;
    }
  }
  return max_d;
}
