#pragma once
#include "Vec3.h"
#include <iostream>

void write_color(std::ostream& out, Color pixelColor, int samplesPerPixel, int& index, uint8_t*& pixels) {
    float r = pixelColor.x;
    float g = pixelColor.y;
    float b = pixelColor.z;

    // Divide the color by the number of samples and gamma correct, gamma =2.0
    float scale = 1.0f / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    pixels[index++] = static_cast<int>(256 * clamp(r, 0.0f, 0.999f));
    pixels[index++] = static_cast<int>(256 * clamp(g, 0.0f, 0.999f));
    pixels[index++] = static_cast<int>(256 * clamp(b, 0.0f, 0.999f));
    // Write the translated [0,255] value of each color component.
    //out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
    //    << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
    //    << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
