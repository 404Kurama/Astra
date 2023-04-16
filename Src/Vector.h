#pragma once
#include <numbers>
#include <cmath>

struct Vector3
{
	constexpr Vector3(const float x = 0.f, const float y = 0.f, const float z = 0.f) noexcept : x(x), y(y), z(z) { }

	constexpr const Vector3& operator-(const Vector3& vec) const noexcept {
		return Vector3{ x - vec.x, y - vec.y, z - vec.z };
	}

	constexpr const Vector3& operator+(const Vector3& vec) const noexcept {
		return Vector3{ x + vec.x, y + vec.y, z + vec.z };
	}

	constexpr const Vector3& operator/(const float factor) const noexcept {
		return Vector3{ x / factor, y / factor, z / factor };
	}

	constexpr const Vector3& operator*(const float factor) const noexcept {
		return Vector3{ x * factor, y * factor, z * factor };
	}

	constexpr const Vector3& ToAngle() const noexcept {
		return Vector3{
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f 
		};
	}

	constexpr const bool IsZero() const noexcept {
		return x == 0.f && y == 0.f && z == 0.f;
	}

	float x, y, z;
};
