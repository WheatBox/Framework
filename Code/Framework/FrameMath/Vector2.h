#pragma once

#include <FrameMath/MathCommon.h>

#include <vector>

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

		Vec2_tpl<T> operator +(const Vec2_tpl<T> & v) const { return { this->x + v.x, this->y + v.y }; }
		Vec2_tpl<T> operator -(const Vec2_tpl<T> & v) const { return { this->x - v.x, this->y - v.y }; }
		Vec2_tpl<T> operator *(const Vec2_tpl<T> & v) const { return { this->x * v.x, this->y * v.y }; }
		Vec2_tpl<T> operator /(const Vec2_tpl<T> & v) const { return { this->x / v.x, this->y / v.y }; }

		Vec2_tpl<T> operator -() const { return { -x, -y }; }

		bool operator ==(const Vec2_tpl<T> & v) const { return this->x == v.x && this->y == v.y; }
		bool operator !=(const Vec2_tpl<T> & v) const { return this->x != v.x || this->y != v.y; }

		T Dot(const Vec2_tpl<T> & v) const { return this->x * v.x + this->y * v.y; }
		T Cross(const Vec2_tpl<T> & v) const { return this->x * v.y - this->y * v.x; }

		T Length() const { return std::sqrt(x * x + y * y); }

		T Radian() const {
			double res = static_cast<double>(std::acos(x / Length()));
			return static_cast<T>((y < 0) ? (2 * pi_d - res) : res);
		}
		T Degree() const { return RadToDeg(Radian()); }

		// 弧度 | Radian
		T IncludedAngle(const Vec2_tpl<T> & v) const {
			return std::acos(Dot({ v.x, v.y }) / (Length() * std::sqrt(v.x * v.x + v.y * v.y)));
		}
		T IncludedAngleDegree(const Vec2_tpl<T> & v) const { return RadToDeg(IncludedAngle(v)); }

		Vec2_tpl GetRotated(T rad) const {
			T cosr = std::cos(rad), sinr = std::sin(rad);
			return {
				x * cosr - y * sinr,
				y * cosr + x * sinr
			};
		}
		Vec2_tpl GetRotatedDegree(T deg) const {
			return GetRotated(DegToRad(deg));
		}

		Vec2_tpl & Rotate(T rad) {
			T cosr = std::cos(rad), sinr = std::sin(rad);
			x = x * cosr - y * sinr;
			y = y * cosr + x * sinr;
			return * this;
		}
		Vec2_tpl & RotateDegree(T deg) {
			return Rotate(DegToRad(deg));
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

	template<typename Result_Vec2_ValueType = float, typename ArgsType>
	inline Vec2_tpl<Result_Vec2_ValueType> Vec2Cast(ArgsType _x, ArgsType _y) {
		return {
			Result_Vec2_ValueType(_x),
			Result_Vec2_ValueType(_y)
		};
	}

	template<typename Result_Vec2_ValueType = float, typename Argument_Vec2_ValueType>
	inline Vec2_tpl<Result_Vec2_ValueType> Vec2Cast(const Vec2_tpl<Argument_Vec2_ValueType> & _vec) {
		return {
			Result_Vec2_ValueType(_vec.x),
			Result_Vec2_ValueType(_vec.y)
		};
	}

	// 范例 | Example:
	// Rotate2DVectors(radian, { & v1, & v2, ... });
	template<typename T>
	constexpr void Rotate2DVectors(float radian, std::initializer_list<Vec2_tpl<T> *> vecs) {
		T cosr = std::cos(radian), sinr = std::sin(radian);
		T xTemp;
		for(auto vec : vecs) {
			xTemp = vec->x;
			vec->x = xTemp * cosr - vec->y * sinr;
			vec->y = vec->y * cosr + xTemp * sinr;
		}
	}

	// 范例 | Example:
	// std::vector<Vec2> vecs { ... };
	// Rotate2DVectors(radian, vecs);
	template<typename T>
	constexpr void Rotate2DVectors(float radian, std::vector<Vec2_tpl<T>> & vecs) {
		T cosr = std::cos(radian), sinr = std::sin(radian);
		T xTemp;
		for(auto & vec : vecs) {
			xTemp = vec.x;
			vec.x = xTemp * cosr - vec.y * sinr;
			vec.y = vec.y * cosr + xTemp * sinr;
		}
	}

	// 范例 | Example:
	// Rotate2DVectors(degree, { & v1, & v2, ... });
	template<typename T>
	constexpr void Rotate2DVectorsDegree(float degree, std::initializer_list<Vec2_tpl<T> *> vecs) {
		Rotate2DVectors(DegToRad(degree), vecs);
	}

	// 范例 | Example:
	// std::vector<Vec2> vecs { ... };
	// Rotate2DVectors(degree, vecs);
	template<typename T>
	constexpr void Rotate2DVectorsDegree(float degree, std::vector<Vec2_tpl<T>> & vecs) {
		Rotate2DVectors(DegToRad(degree), vecs);
	}

}
