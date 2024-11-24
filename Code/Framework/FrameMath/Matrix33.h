#pragma once

#include <FrameMath/Matrix_tpl.h>
#include <FrameMath/Vector2.h>
#include <FrameMath/Vector3.h>

namespace Frame {

	template<typename T>
	struct Matrix33_tpl : public Matrix_tpl<T, 3, 3> {

		typedef Matrix_tpl<T, 3, 3> BaseMatrixType;

		Matrix33_tpl() : BaseMatrixType() {};
		Matrix33_tpl(std::initializer_list<T> values) : BaseMatrixType(values) {}

		Matrix33_tpl(const BaseMatrixType & mat) : BaseMatrixType(std::initializer_list<T>(mat.data, mat.data + 9)) {}
		
		using BaseMatrixType::operator +;
		using BaseMatrixType::operator -;
		using BaseMatrixType::operator *;
		using BaseMatrixType::operator /;

		using BaseMatrixType::operator +=;
		using BaseMatrixType::operator -=;
		using BaseMatrixType::operator *=;
		using BaseMatrixType::operator /=;

		using BaseMatrixType::operator ==;
		using BaseMatrixType::operator !=;

		Matrix33_tpl<T> operator +(const BaseMatrixType & m) const { return Matrix_tpl::operator +(m); }
		Matrix33_tpl<T> operator -(const BaseMatrixType & m) const { return Matrix_tpl::operator -(m); }
		Matrix33_tpl<T> operator *(const BaseMatrixType & m) const { return Matrix_tpl::operator *(m); }

		Matrix33_tpl<T> operator +=(const BaseMatrixType & m) { return Matrix_tpl::operator +=(m); }
		Matrix33_tpl<T> operator -=(const BaseMatrixType & m) { return Matrix_tpl::operator -=(m); }
		Matrix33_tpl<T> operator *=(const BaseMatrixType & m) { (* this) = (* this) * m; return * this; }

		Matrix33_tpl<T> operator +(T val) const { return Matrix_tpl::operator +(val); }
		Matrix33_tpl<T> operator -(T val) const { return Matrix_tpl::operator -(val); }
		Matrix33_tpl<T> operator *(T val) const { return Matrix_tpl::operator *(val); }
		Matrix33_tpl<T> operator /(T val) const { return Matrix_tpl::operator /(val); }

		Matrix33_tpl<T> operator +=(T val) { return Matrix_tpl::operator +=(val); }
		Matrix33_tpl<T> operator -=(T val) { return Matrix_tpl::operator -=(val); }
		Matrix33_tpl<T> operator *=(T val) { return Matrix_tpl::operator *=(val); }
		Matrix33_tpl<T> operator /=(T val) { return Matrix_tpl::operator /=(val); }
		
		Vec2_tpl<T> operator *(const Vec2_tpl<T> & v) const {
			Matrix_tpl<T, 3, 1> n = (* this) * Matrix_tpl<T, 3, 1> { { v.x, v.y, 1.f } };
			return { n[0], n[1] };
		}

		Vec3_tpl<T> operator *(const Vec3_tpl<T> & v) const {
			Matrix_tpl<T, 3, 1> n = (* this) * Matrix_tpl<T, 3, 1> { { v.x, v.y, v.z } };
			return { n[0], n[1], n[2] };
		}

		static Matrix33_tpl<T> CreateIdentity() {
			return {{
					1.f, 0.f, 0.f,
					0.f, 1.f, 0.f,
					0.f, 0.f, 1.f
				}};
		}

		static Matrix33_tpl<T> CreateTranslation(const Frame::Vec2_tpl<T> & v) {
			return {{
					1.f, 0.f, v.x,
					0.f, 1.f, v.y,
					0.f, 0.f, 1.f
				}};
		}

		static Matrix33_tpl<T> CreateRotationZ(float rad) {
			float cosa = cos(rad), sina = sin(rad);
			return {{
					cosa, -sina, 0.f,
					sina, cosa, 0.f,
					0.f, 0.f, 1.f
				}};
		}

		static Matrix33_tpl<T> CreateScale(const Frame::Vec2_tpl<T> & scale) {
			return {{
					scale.x, 0.f, 0.f,
					0.f, scale.y, 0.f,
					0.f, 0.f, 1.f
				}};
		}

	};

	typedef Matrix33_tpl<float> Matrix33;
	typedef Matrix33_tpl<double> Matrix33d;
	typedef Matrix33_tpl<int> Matrix33i;

}
