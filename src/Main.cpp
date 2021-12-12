#include <iostream>
#include "vec3.h"
#include "Ray.h"
#include "Camera.h"
#include "Hittable.h"
#include "Sphere.h"

vec3 ColorRay(Ray &r)
{
    hit_record rec;
    Sphere s(vec3(0, 0, -1), 0.5);
    bool hit = s.hit(r, 0.01, 10, rec);

    if (hit)
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
            vec3 pixel_color = ColorRay(r);
            std::cout << static_cast<int>(255.999 * pixel_color.x()) << ' '
                      << static_cast<int>(255.999 * pixel_color.y()) << ' '
                      << static_cast<int>(255.999 * pixel_color.z()) << '\n';
        }
    }

    return 0;
}