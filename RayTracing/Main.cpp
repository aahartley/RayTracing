#include "RTWeekend.h"
#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>


Color ray_color(const Ray& r, const Hittable& world, int depth) {
    HitRecord rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0, 0, 0);

    if (world.hit(r, 0.0f, infinity, rec)) {
        Point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5f * ray_color(Ray(rec.p, target - rec.p), world, depth - 1);
    }
    Vec3 unitDirection = unitVector(r.direction);
    float t = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + t * Color(0.5f, 0.7f, 1.0f);
}

int main() {

    // Image
    const float aspectRatio = 16.0f / 9.0f;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspectRatio);
    const int samplesPerPixel = 100;
    const int max_depth = 50;

    //World
    HittableList world;
    world.add(make_shared<Sphere>(Point3(1, 0, -1), 0.5f));
    world.add(make_shared<Sphere>(Point3(0, -100.5f, -1), 100.0f));


    // Camera
    Camera cam;

    // Render
    //std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    uint8_t* pixels = new uint8_t[image_width * image_height * 3];
    int index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                auto u = (i + randomFloat()) / (image_width - 1);
                auto v = (j + randomFloat()) / (image_height - 1);
                Ray r = cam.get_ray(u, v);
                pixelColor += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixelColor, samplesPerPixel,index,pixels);

        }
    
    }
    std::cerr << "\nDone.\n";
    stbi_write_png("image.png", image_width, image_height, 3, pixels, image_width * 3);

}