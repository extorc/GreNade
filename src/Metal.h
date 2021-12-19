#pragma once

#include "Material.h"
#include "vec3.h"

class Metal : public Material
{
public:
  Metal(const color &c, float f) : albedo(c), fuzz(f < 1 ? f : 1) {}
  bool Scatter(Ray &ray_in, hit_record &rec, color &attenuation, Ray &scattered) const override
  {
    vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

private:
  color albedo;
  float fuzz;
};