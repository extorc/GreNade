#pragma once

#include "Ray.h"
#include "hit_record.h"

struct hit_record;

class Material
{
public:
  virtual bool Scatter(Ray &ray_in, hit_record &rec, color &attenuation, Ray &scattered) const = 0;
};