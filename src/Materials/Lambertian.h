#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
  Lambertian(const color &c) : albedo(c) {}
  bool Scatter(Ray &ray_in, hit_record &rec, color &attenuation, Ray &scattered) const override
  {
    auto scatter_dir = rec.normal + unit_vector(random_in_unit_sphere());

    if (scatter_dir.near_zero())
      scatter_dir = rec.normal;

    scattered = Ray(rec.p, scatter_dir);
    attenuation = albedo;
    return true;
  }

private:
  color albedo;
};