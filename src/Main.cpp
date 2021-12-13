#include <iostream>
#include <memory>
#include <limits>
#include "Ray.h"
#include "Camera.h"
#include "Hittable.h"
#include "Sphere.h"
#include "Hittable_list.h"

vec3 ColorRay(Ray &r, Hittable_list &world, int depth)
{
    hit_record rec;

    if (depth <= 0)
    {
        return color(0, 0, 0);
    }

    if (world.hit(r, 0, std::numeric_limits<double>::infinity(), rec))
    {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        Ray newRay(rec.p, target - rec.p);
        return 0.5 * ColorRay(newRay, world, depth - 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (float)(1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

void WriteColor(color pixel_color)
{
    std::cout << static_cast<int>(255.999 * pixel_color.x()) << ' '
              << static_cast<int>(255.999 * pixel_color.y()) << ' '
              << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int depth = 20; //Light Bounces > in a diffused lighting environment , light bounces around objects
    //this variable defines , the maximum number of times a light ray can bounce off
    const int sample_count = 10;

    Hittable_list world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera camera; // Camera Struct holding const data

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--)
    {

        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; i++)
        {
            color pixel_color(0, 0, 0);
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);

            Ray r(camera.origin, camera.lower_left_corner + (float)u * camera.horizontal + (float)v * camera.vertical - camera.origin);
            // Generate a ray pointing at a pixel

            for (int i = 0; i < sample_count; i++)
            {
                pixel_color += ColorRay(r, world, depth);
            }
            pixel_color *= (float)(1.0 / sample_count);

            WriteColor(pixel_color);
        }
    }

    return 0;
}
