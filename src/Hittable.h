#pragma once

#include "vec3.h"
#include "Ray.h"

struct hit_record
{
  point3 p;
  vec3 normal;
  float t;
};

class Hittable
{
public:
  virtual bool hit(Ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};