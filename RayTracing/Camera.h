#pragma once
#include "RTWeekend.h"

class Camera {
public:
	Camera() {
        float aspect_ratio = 16.0f / 9.0f;
        float viewport_height = 2.0f;
        float viewport_width = aspect_ratio * viewport_height;
        float focal_length = 1.0f;

        origin = Point3(0, 0, 0);
        horizontal = Vec3(viewport_width, 0.0f, 0.0f);
        vertical = Vec3(0.0f, viewport_height, 0.0f);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);
	}
    Ray get_ray(float u, float v) const {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

private:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
};