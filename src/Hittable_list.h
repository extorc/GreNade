#pragma once

#include "Hittable.h"
#include <iostream>
#include <memory>
#include <vector>

class Hittable_list
{
public:
  void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }
  void clear() { objects.clear(); }

  bool hit(Ray &r, float t_min, float t_max, hit_record &rec) const;

private:
  std::vector<std::shared_ptr<Hittable>> objects;
};