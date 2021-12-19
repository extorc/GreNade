#include "Sphere.h"

bool Sphere::hit(Ray &r, float t_min, float t_max, hit_record &rec) const
{
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0)
    return false;

  auto sqrtd = sqrt(discriminant);

  //Find nearest root
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root)
  {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
      return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  rec.normal = (rec.p - center) / radius;
  rec.mat_ptr = mat_ptr;

  return true;
}
