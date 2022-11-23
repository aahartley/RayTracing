#include "RTWeekend.h"
#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Material.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

HittableList randomScene() {
    HittableList world;

    shared_ptr<Lambertian> ground_material = make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(Point3(0.0f, -1000.0f, 0.0f), 1000.0f, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = randomFloat();
            Point3 center(a + 0.9f * randomFloat(), 0.2f, b + 0.9f * randomFloat());

            if ((center - Point3(4.0f, 0.2f, 0.0f)).magnitude() > 0.9f) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8f) {
                    // diffuse
                    Vec3 albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95f) {
                    // metal
                    Vec3 albedo = Color::random(0.5f, 1.0f);
                    float fuzz = randomFloat(0.0f, 0.5f);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5f);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                }
            }
        }
    }

    shared_ptr<Dielectric> material1 = make_shared<Dielectric>(1.5f);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0f, material1));

    shared_ptr<Lambertian> material2 = make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0f, material2));

    shared_ptr<Metal> material3 = make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0f, material3));

    return world;
}
Color ray_color(const Ray& r, const Hittable& world, int depth) {
    HitRecord rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0, 0, 0);
    if (world.hit(r, 0.0001f, infinity, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.matPtr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return Color(0, 0, 0);
    }
    Vec3 unitDirection = unitVector(r.direction);
    float t = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + t * Color(0.5f, 0.7f, 1.0f);
}

int main() {

    // Image
    const float aspectRatio = 3.0f / 2.0f;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width/aspectRatio);
    const int samplesPerPixel = 500;
    const int max_depth = 50;

    //World
    HittableList world = randomScene();


    // Camera
    Point3 lookfrom(13, 3, 2);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.1f;

    Camera cam(lookfrom, lookat, vup, 20, aspectRatio, aperture, dist_to_focus);

    // Render
    //std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    uint8_t* pixels = new uint8_t[image_width * image_height * 3];
    int index = 0;
    //#pragma omp parallel for num_threads(12)
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