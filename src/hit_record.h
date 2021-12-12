#pragma once

#include "vec3.h"

struct hit_record
{
  point3 p;
  vec3 normal;
  float t;
};