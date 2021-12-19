#include <iostream>
#include <memory>
#include <limits>
#include "Ray.h"
#include "Camera.h"
#include "Hittable.h"
#include "Sphere.h"
#include "Hittable_list.h"
#include "Lambertian.h"
#include "Metal.h"

vec3 ColorRay(Ray &r, Hittable_list &world, int depth)
{
    hit_record rec;

    if (depth <= 0)
    {
        return color(0, 0, 0);
    }

    if (world.hit(r, 0.01, std::numeric_limits<double>::infinity(), rec))
    {
        Ray scattered;
        color attenuation;
        if (rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
            return attenuation * ColorRay(scattered, world, depth - 1);

        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (float)(1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

void WriteColor(color pixel_color, int sample_count)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / sample_count;

    r = sqrt(r * scale);
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    std::cout << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
              << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
              << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int depth = 20;
    const int sample = 50;

    Hittable_list world;
    // world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    // world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, std::make_shared<Lambertian>(color(0.8, 0.8, 0.0))));
    world.add(std::make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5, std::make_shared<Lambertian>(color(0.7, 0.3, 0.3))));
    world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, std::make_shared<Metal>(color(0.8, 0.8, 0.8), 0.3)));
    world.add(std::make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, std::make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0)));
    world.add(std::make_shared<Sphere>(point3(0.0, 1.0, -1.0), 0.5, std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.1)));

    Camera camera; // Camera Struct holding const data

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--)
    {

        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; i++)
        {
            color pixel_color(0, 0, 0);

            for (int s = 0; s < sample; s++)
            {
                auto u = double(i + vec3::random_double()) / (image_width - 1);
                auto v = double(j + vec3::random_double()) / (image_height - 1);

                Ray r(camera.origin, camera.lower_left_corner + (float)u * camera.horizontal + (float)v * camera.vertical - camera.origin);
                pixel_color += ColorRay(r, world, depth);
            }

            WriteColor(pixel_color, sample);
        }
    }

    return 0;
}
