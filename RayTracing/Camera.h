#pragma once
#include "RTWeekend.h"

class Camera {
public:
	Camera(Point3 lookFrom, Point3 lookAt, Vec3 vUp, float vfov, float aspectRatio, float aperture, float focusDist) {
        float theta = degrees_to_radians(vfov);
        float h = tan(theta / 2);
        float viewport_height = 2.0f * h;
        float viewport_width = aspectRatio * viewport_height;

        w = unitVector(lookFrom - lookAt);
        u = unitVector(cross(vUp, w));
        v = cross(w, u);

        origin = lookFrom;
        horizontal = focusDist * viewport_width * u;
        vertical = focusDist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focusDist * w;

        lens_radius = aperture / 2;
	}
    Ray get_ray(float s, float t) const {
        Vec3 rd = lens_radius * random_in_unit_disk();
        Vec3 offset = u * rd.x + v * rd.y;

        return Ray(origin + offset,lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

private:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    float lens_radius;
};