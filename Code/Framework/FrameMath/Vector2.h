#pragma once

#include <FrameMath/Math.h>

namespace Frame {
	
	template<typename T>
	struct Vec2_tpl {

		Vec2_tpl() { x = 0; y = 0; }
		Vec2_tpl(T xy) { x = xy; y = xy; }
		Vec2_tpl(T x, T y) { this->x = x; this->y = y; }
		
		Vec2_tpl<T> & operator =(const Vec2_tpl<T> & v) { this->x = v.x; this->y = v.y; return * this; }
		Vec2_tpl<T> & operator +=(const Vec2_tpl<T> & v) { this->x += v.x; this->y += v.y; return * this; }
		Vec2_tpl<T> & operator -=(const Vec2_tpl<T> & v) { this->x -= v.x; this->y -= v.y; return * this; }
		Vec2_tpl<T> & operator *=(const Vec2_tpl<T> & v) { this->x *= v.x; this->y *= v.y; return * this; }
		Vec2_tpl<T> & operator /=(const Vec2_tpl<T> & v) { this->x /= v.x; this->y /= v.y; return * this; }

		Vec2_tpl<T> & operator =(const T & val) { this->x = val; this->y = val; return * this; }
		Vec2_tpl<T> & operator +=(const T & val) { this->x += val; this->y += val; return * this; }
		Vec2_tpl<T> & operator -=(const T & val) { this->x -= val; this->y -= val; return * this; }
		Vec2_tpl<T> & operator *=(const T & val) { this->x *= val; this->y *= val; return * this; }
		Vec2_tpl<T> & operator /=(const T & val) { this->x /= val; this->y /= val; return * this; }

		Vec2_tpl<T> operator +(const Vec2_tpl<T> & v) const { return { this->x + v.x, this->y + v.y }; };
		Vec2_tpl<T> operator -(const Vec2_tpl<T> & v) const { return { this->x - v.x, this->y - v.y }; };
		Vec2_tpl<T> operator *(const Vec2_tpl<T> & v) const { return { this->x * v.x, this->y * v.y }; };
		Vec2_tpl<T> operator /(const Vec2_tpl<T> & v) const { return { this->x / v.x, this->y / v.y }; };

		Vec2_tpl<T> operator +(const T & val) const { return { this->x + val, this->y + val }; };
		Vec2_tpl<T> operator -(const T & val) const { return { this->x - val, this->y - val }; };
		Vec2_tpl<T> operator *(const T & val) const { return { this->x * val, this->y * val }; };
		Vec2_tpl<T> operator /(const T & val) const { return { this->x / val, this->y / val }; };

		T Dot(T _x, T _y) const { return this->x * _x + this->y * _y; };
		T Dot(const Vec2_tpl<T> & v) const { return this->x * v.x + this->y * v.y; };
		T Cross(T _x, T _y) const { return this->x * _y - this->y * _x; };
		T Cross(const Vec2_tpl<T> & v) const { return this->x * v.y - this->y * v.x; };

		T Length() const { return std::sqrt(x * x + y * y); }

		T Radian() const {
			T res = std::acos(x / Length());
			return ((y < 0) ? (2 * pi_d - res) : res);
		}
		T Degree() const { return RadToDeg(Radian()); }

		T IncludedAngleRadian(T _x, T _y) const { return std::acos(Dot(_x, _y) / (Length() * std::sqrt(_x * _x + _y * _y))); }
		T IncludedAngleRadian(const Vec2_tpl<T> & v) const { return IncludedAngleRadian(v.x, v.y); }
		
		T IncludedAngleDegree(T _x, T _y) const { return RadToDeg(IncludedAngleRadian(_x, _y)); }
		T IncludedAngleDegree(const Vec2_tpl<T> & v) const { return RadToDeg(IncludedAngleRadian(v.x, v.y)); }

		Vec2_tpl RotateRadian(T rad) const {
			T cosr = std::cos(rad), sinr = std::sin(rad);
			return {
				x * cosr - y * sinr,
				y * cosr + x * sinr
			};
		}
		
		Vec2_tpl RotateDegree(T deg) const {
			return RotateRadian(DegToRad(deg));
		}

		Vec2_tpl GetNormalized() const {
			T len = Length();
			return { x / len, y / len };
		}

		Vec2_tpl & Normalize() {
			T len = Length();
			x /= len;
			y /= len;
			return * this;
		}

		T x;
		T y;
	};

	typedef Vec2_tpl<float> Vec2;
	typedef Vec2_tpl<double> Vec2d;
	typedef Vec2_tpl<int> Vec2i;

}