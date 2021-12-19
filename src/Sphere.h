#pragma once

#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable
{
public:
  Sphere(point3 cen, float r, std::shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m) {}
  bool hit(Ray &r, float t_min, float t_max, hit_record &rec) const override;

private:
  point3 center;
  float radius;
  std::shared_ptr<Material> mat_ptr;
};