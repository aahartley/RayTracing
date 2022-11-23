#pragma once
#include <cmath>
#include <iostream>
class Vec3 {
	public:
		float x,y,z;

		Vec3() : x(0),y(0),z(0) {}
		Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		Vec3 operator- () const { return Vec3(-x, -y, -z); }

		Vec3& operator+=(const Vec3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		Vec3& operator*=(const float t) {
			x *= t;
			y *= t;
			z *= t;
			return *this;
		}

		Vec3& operator/=(const float t) {
			return *this *= 1.0f / t;
		}
		float magnitude() const {
			return std::sqrtf(magnitudeSquared());
		}
		float magnitudeSquared() const {
			return (x * x + y * y + z * z);
		}

		Vec3& normalize() {
			float length = (1 / magnitude());
			x *= length;
			y *= length;
			z *= length;
			return *this;
		}
		inline static Vec3 random() {
			return Vec3(randomFloat(), randomFloat(), randomFloat());
		}

		inline static Vec3 random(float min, float max) {
			return Vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
		}
	
		bool near_zero() const {
			// Return true if the vector is close to zero in all dimensions.
			const auto s = 1e-8;
			return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
		}

};
using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}
inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}
inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}
inline Vec3 operator*(float s, const Vec3& v) {
	return Vec3(s * v.x, s * v.y, s * v.z);
}
inline Vec3 operator*(const Vec3& v, float s) {
	return s * v;
}
inline Vec3 operator/(Vec3 v, float t) {
	return (1 / t) * v;
}

inline float dot(const Vec3& u, const Vec3& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}
inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.y * v.z - u.z * v.y,
				-(u.x * v.z - u.z * v.x),
				u.x * v.y - u.y * v.x);
}
inline Vec3 unitVector(const Vec3& v) {
	return v /v.magnitude();
}

inline Vec3 random_in_unit_sphere() {
	while (true) {
		auto p = Vec3::random(-1, 1);
		if (p.magnitudeSquared() >= 1) continue;
		return p;
	}
}
inline Vec3 random_unit_vector() {
	return unitVector(random_in_unit_sphere());
}
inline Vec3 random_in_hemisphere(const Vec3& normal) {
	Vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}
inline Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n) * n;
}
inline Vec3 refract(const Vec3& uv, const Vec3& n, float etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0f);
	Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	Vec3 r_out_parallel = -sqrt(fabs(1.0f - r_out_perp.magnitudeSquared())) * n;
	return r_out_perp + r_out_parallel;
}
inline Vec3 random_in_unit_disk() {
	while (true) {
		auto p = Vec3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
		if (p.magnitudeSquared() >= 1) continue;
		return p;
	}
}