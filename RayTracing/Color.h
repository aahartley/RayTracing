#pragma once
#include "Vec3.h"
#include <iostream>

void write_color(std::ostream& out, Color pixelColor, int samplesPerPixel, int& index, uint8_t*& pixels) {
    auto r = pixelColor.x;
    auto g = pixelColor.y;
    auto b = pixelColor.z;

    // Divide the color by the number of samples.
    auto scale = 1.0f / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    pixels[index++] = static_cast<int>(256 * clamp(r, 0.0f, 0.999f));
    pixels[index++] = static_cast<int>(256 * clamp(g, 0.0f, 0.999f));
    pixels[index++] = static_cast<int>(256 * clamp(b, 0.0f, 0.999f));
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}