#pragma once
#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable {
public:
	Point3 center;
	float radius;

	Sphere() {}
	Sphere(Point3 cen, float r) : center(cen), radius(r) {};

	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;
};

bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec)const {
    Vec3 oc = r.origin - center;
    float a = r.direction.magnitudeSquared();
    float half_b = dot(oc, r.direction);
    float c = oc.magnitudeSquared() - radius * radius;

    float discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    float sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (-half_b - sqrtd) / a;
    if (root < tMin || tMax < root) {
        root = (-half_b + sqrtd) / a;
        if (root < tMin || tMax < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);

    return true;
}
