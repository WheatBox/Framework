#pragma once

#include <FrameMath/Matrix_tpl.h>
#include <FrameMath/Vector2.h>

namespace Frame {

	template<typename T>
	struct Matrix22_tpl : public Matrix_tpl<T, 2, 2> {

		typedef Matrix_tpl<T, 2, 2> BaseMatrixType;

		Matrix22_tpl() : BaseMatrixType() {};
		Matrix22_tpl(std::initializer_list<T> values) : BaseMatrixType(values) {}
		Matrix22_tpl(const T * values, size_t count) : BaseMatrixType(values, count) {}

		Matrix22_tpl(const BaseMatrixType & mat) : BaseMatrixType(mat.data, 4) {}

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

		Matrix22_tpl<T> operator +(const BaseMatrixType & m) const { return BaseMatrixType::operator +(m); }
		Matrix22_tpl<T> operator -(const BaseMatrixType & m) const { return BaseMatrixType::operator -(m); }
		Matrix22_tpl<T> operator *(const BaseMatrixType & m) const { return BaseMatrixType::operator *(m); }

		Matrix22_tpl<T> operator +=(const BaseMatrixType & m) { return BaseMatrixType::operator +=(m); }
		Matrix22_tpl<T> operator -=(const BaseMatrixType & m) { return BaseMatrixType::operator -=(m); }
		Matrix22_tpl<T> operator *=(const BaseMatrixType & m) { (* this) = (* this) * m; return * this; }

		Matrix22_tpl<T> operator +(T val) const { return BaseMatrixType::operator +(val); }
		Matrix22_tpl<T> operator -(T val) const { return BaseMatrixType::operator -(val); }
		Matrix22_tpl<T> operator *(T val) const { return BaseMatrixType::operator *(val); }
		Matrix22_tpl<T> operator /(T val) const { return BaseMatrixType::operator /(val); }

		Matrix22_tpl<T> operator +=(T val) { return BaseMatrixType::operator +=(val); }
		Matrix22_tpl<T> operator -=(T val) { return BaseMatrixType::operator -=(val); }
		Matrix22_tpl<T> operator *=(T val) { return BaseMatrixType::operator *=(val); }
		Matrix22_tpl<T> operator /=(T val) { return BaseMatrixType::operator /=(val); }
		
		Vec2_tpl<T> operator *(const Vec2_tpl<T> & v) const {
			return { this->data[0] * v.x + this->data[1] * v.y, this->data[2] * v.x + this->data[3] * v.y };
		}

		static Matrix22_tpl<T> CreateIdentity() {
			return {{
					1.f, 0.f,
					0.f, 1.f
				}};
		}

		// 如果你想将多个变换矩阵相乘，请将先执行的变换矩阵放在右边，后执行的变换矩阵放在左边
		// If you want to multiply multiple transformation matrices, please place the transformation matrix
		// executed first on the right and the transformation matrix executed later on the left
		static Matrix22_tpl<T> CreateRotation(float rad) {
			float cosa = cos(rad), sina = sin(rad);
			return {{
					cosa, -sina,
					sina, cosa
				}};
		}

		// 如果你想将多个变换矩阵相乘，请将先执行的变换矩阵放在右边，后执行的变换矩阵放在左边
		// If you want to multiply multiple transformation matrices, please place the transformation matrix
		// executed first on the right and the transformation matrix executed later on the left
		static Matrix22_tpl<T> CreateScale(const Frame::Vec2_tpl<T> & scale) {
			return {{
					scale.x, 0.f,
					0.f, scale.y
				}};
		}

	};

	typedef Matrix22_tpl<float> Matrix22;
	typedef Matrix22_tpl<double> Matrix22d;
	typedef Matrix22_tpl<int> Matrix22i;

}
