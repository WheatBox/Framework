#pragma once

#include <FrameMath/Math.h>
#include <FrameMath/Vector2.h>

namespace Frame {
	
	template<typename T>
	struct Vec3_tpl {

		Vec3_tpl() { x = y = z = 0; }
		Vec3_tpl(T xyz) { x = y = z = xyz; }
		Vec3_tpl(T x, T y, T z) { this->x = x; this->y = y; this->z = z; }
		Vec3_tpl(const Vec2_tpl<T> & vec2_xy, T z) { x = vec2_xy.x; y = vec2_xy.y; this->z = z; }
		
		Vec3_tpl<T> & operator =(const Vec3_tpl<T> & v) { this->x = v.x; this->y = v.y; this->z = v.z; return * this; }
		Vec3_tpl<T> & operator +=(const Vec3_tpl<T> & v) { this->x += v.x; this->y += v.y; this->z += v.z; return * this; }
		Vec3_tpl<T> & operator -=(const Vec3_tpl<T> & v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; return * this; }
		Vec3_tpl<T> & operator *=(const Vec3_tpl<T> & v) { this->x *= v.x; this->y *= v.y; this->z *= v.z; return * this; }
		Vec3_tpl<T> & operator /=(const Vec3_tpl<T> & v) { this->x /= v.x; this->y /= v.y; this->z /= v.z; return * this; }

		Vec3_tpl<T> operator +(const Vec3_tpl<T> & v) const { return { this->x + v.x, this->y + v.y, this->z + v.z }; }
		Vec3_tpl<T> operator -(const Vec3_tpl<T> & v) const { return { this->x - v.x, this->y - v.y, this->z - v.z }; }
		Vec3_tpl<T> operator *(const Vec3_tpl<T> & v) const { return { this->x * v.x, this->y * v.y, this->z * v.z }; }
		Vec3_tpl<T> operator /(const Vec3_tpl<T> & v) const { return { this->x / v.x, this->y / v.y, this->z / v.z }; }

		bool operator ==(const Vec3_tpl<T> & v) const { return this->x == v.x && this->y == v.y && this->z == v.z; }
		bool operator !=(const Vec3_tpl<T> & v) const { return this->x != v.x || this->y != v.y || this->z == v.z; }

		T Dot(const Vec3_tpl<T> & v) const {
			return this->x * v.x + this->y * v.y + this->z * v.z;
		}
		Vec3_tpl Cross(const Vec3_tpl<T> & v) const {
			return {
				this->y * v.z - this->z * v.y,
				this->z * v.x - this->x * v.z,
				this->x * v.y - this->y * v.x
			};
		}

		T Length() const { return std::sqrt(x * x + y * y + z * z); }

		Vec3_tpl GetNormalized() const {
			T len = Length();
			return { x / len, y / len, z / len };
		}

		Vec3_tpl & Normalize() {
			T len = Length();
			x /= len;
			y /= len;
			z /= len;
			return * this;
		}

		T x;
		T y;
		T z;
	};

	typedef Vec3_tpl<float> Vec3;
	typedef Vec3_tpl<double> Vec3d;
	typedef Vec3_tpl<int> Vec3i;

}
