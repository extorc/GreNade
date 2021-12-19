#pragma once

#include "vec3.h"
#include <memory>
#include "Material.h"

struct hit_record
{
  point3 p;
  vec3 normal;
  std::shared_ptr<Material> mat_ptr;
  float t;
};