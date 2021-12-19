#pragma once

#include "vec3.h"
#include "Ray.h"
#include "hit_record.h"

class Hittable
{
public:
  virtual bool hit(Ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};