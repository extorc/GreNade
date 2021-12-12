#include <iostream>
#include <memory>
#include <limits>
#include "vec3.h"
#include "Ray.h"
#include "Camera.h"
#include "Hittable.h"
#include "Sphere.h"
#include "hittable_list.h"

vec3 ColorRay(Ray &r, Hittable_list &world)
{
    hit_record rec;

    if (world.hit(r, 0, std::numeric_limits<double>::infinity(), rec))
        return vec3(rec.normal.x() + 0.5, rec.normal.y() + 0.5, rec.normal.z() + 0.5);

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (float)(1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    Hittable_list world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera camera;

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--)
    {

        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; i++)
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);

            Ray r(camera.origin, camera.lower_left_corner + (float)u * camera.horizontal + (float)v * camera.vertical - camera.origin);
            vec3 pixel_color = ColorRay(r, world);
            std::cout << static_cast<int>(255.999 * pixel_color.x()) << ' '
                      << static_cast<int>(255.999 * pixel_color.y()) << ' '
                      << static_cast<int>(255.999 * pixel_color.z()) << '\n';
        }
    }

    return 0;
}