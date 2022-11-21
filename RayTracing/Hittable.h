#pragma once
#include "Ray.h"

struct HitRecord {
	Point3 p;
	Vec3 normal;
	float t;
	bool frontFace;

	inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal) {
		frontFace = dot(r.direction, outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};