#pragma once

#include "../FrameMath/Matrix_tpl.h"
#include "../FrameMath/Vector2.h"
#include "../FrameMath/Vector3.h"

namespace Frame {

	template<typename T>
	struct Matrix33_tpl : public Matrix_tpl<T, 3, 3> {

		typedef Matrix_tpl<T, 3, 3> BaseMatrixType;

		Matrix33_tpl() : BaseMatrixType() {};
		Matrix33_tpl(std::initializer_list<T> values) : BaseMatrixType(values) {}
		Matrix33_tpl(const T * values, size_t count) : BaseMatrixType(values, count) {}

		Matrix33_tpl(const BaseMatrixType & mat) : BaseMatrixType(mat.data, 9) {}
		
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

		Matrix33_tpl<T> operator +(const BaseMatrixType & m) const { return BaseMatrixType::operator +(m); }
		Matrix33_tpl<T> operator -(const BaseMatrixType & m) const { return BaseMatrixType::operator -(m); }
		Matrix33_tpl<T> operator *(const BaseMatrixType & m) const { return BaseMatrixType::operator *(m); }

		Matrix33_tpl<T> operator +=(const BaseMatrixType & m) { return BaseMatrixType::operator +=(m); }
		Matrix33_tpl<T> operator -=(const BaseMatrixType & m) { return BaseMatrixType::operator -=(m); }
		Matrix33_tpl<T> operator *=(const BaseMatrixType & m) { (* this) = (* this) * m; return * this; }

		Matrix33_tpl<T> operator +(T val) const { return BaseMatrixType::operator +(val); }
		Matrix33_tpl<T> operator -(T val) const { return BaseMatrixType::operator -(val); }
		Matrix33_tpl<T> operator *(T val) const { return BaseMatrixType::operator *(val); }
		Matrix33_tpl<T> operator /(T val) const { return BaseMatrixType::operator /(val); }

		Matrix33_tpl<T> operator +=(T val) { return BaseMatrixType::operator +=(val); }
		Matrix33_tpl<T> operator -=(T val) { return BaseMatrixType::operator -=(val); }
		Matrix33_tpl<T> operator *=(T val) { return BaseMatrixType::operator *=(val); }
		Matrix33_tpl<T> operator /=(T val) { return BaseMatrixType::operator /=(val); }
		
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
			const float cosa = cos(rad), sina = sin(rad);
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

		// TRS
		// translation * rotation * scale
		static Matrix33_tpl<T> CreateTransform(const Frame::Vec2_tpl<T> & v, float rot, const Frame::Vec2_tpl<T> & scale) {
			const float cosa = cos(rot), sina = sin(rot);
			return {{
					cosa * scale.x, -sina * scale.y, v.x,
					sina * scale.x, cosa * scale.y, v.y,
					0.f, 0.f, 1.f
				}};
		}

		// translation * scale * rotation
		static Matrix33_tpl<T> CreateTransformTSR(const Frame::Vec2_tpl<T> & v, const Frame::Vec2_tpl<T> & scale, float rot) {
			const float cosa = cos(rot), sina = sin(rot);
			return {{
					cosa * scale.x, -sina * scale.x, v.x,
					sina * scale.y, cosa * scale.y, v.y,
					0.f, 0.f, 1.f
				}};
		}

		// scale * rotation * translation
		static Matrix33_tpl<T> CreateTransformSRT(const Vec2_tpl<T> & scale, float rot, const Vec2_tpl<T> & v) {
			const float cosa = cos(rot), sina = sin(rot);
			return {{
					cosa * scale.x, -sina * scale.x, scale.x * (cosa * v.x - sina * v.y),
					sina * scale.y, cosa * scale.y, scale.y * (sina * v.x + cosa * v.y),
					0.f, 0.f, 1.f
				}};
		}

		// translation * scale
		static Matrix33_tpl<T> CreateTransformTS(const Frame::Vec2_tpl<T> & v, const Frame::Vec2_tpl<T> & scale) {
			return {{
					scale.x, 0.f, v.x,
					0.f, scale.y, v.y,
					0.f, 0.f, 1.f
				}};
		}

		// scale * translation
		static Matrix33_tpl<T> CreateTransformST(const Frame::Vec2_tpl<T> & scale, const Frame::Vec2_tpl<T> & v) {
			return {{
					scale.x, 0.f, scale.x * v.x,
					0.f, scale.y, scale.y * v.y,
					0.f, 0.f, 1.f
				}};
		}
	};

	typedef Matrix33_tpl<float> Matrix33;
	typedef Matrix33_tpl<double> Matrix33d;
	typedef Matrix33_tpl<int> Matrix33i;

}
