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