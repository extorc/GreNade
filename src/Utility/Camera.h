#pragma once
#include "vec3.h"

struct Camera
{
  float viewport_height = 2.0;
  float viewport_width = viewport_height * 16.0 / 9.0;
  float focal_length = 1.0;

  vec3 origin = vec3(0, 0, 0);
  vec3 horizontal = vec3(viewport_width, 0, 0);
  vec3 vertical = vec3(0, viewport_height, 0);
  vec3 lower_left_corner = origin - horizontal * (float)0.5 - vertical * (float)0.5 - vec3(0, 0, focal_length);
};