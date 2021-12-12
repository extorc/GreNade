#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public:
  Sphere() {}
  Sphere(point3 cen, float r) : center(cen),
                                radius(r) {}
  bool hit(Ray &r, float t_min, float t_max, hit_record &rec) const override;

private:
  point3 center;
  float radius;
};