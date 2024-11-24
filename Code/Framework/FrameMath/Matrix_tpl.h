#pragma once

#include <FrameMath/MathCommon.h>

#include <initializer_list>
#include <functional>

namespace Frame {

	template<typename T, int H, int W>
	struct Matrix_tpl {

		Matrix_tpl() = default;
		Matrix_tpl(std::initializer_list<T> values) {
			auto it = values.begin();
			for(int i = 0, size = Min(H * W, static_cast<int>(values.size())); i < size; i++, it++) {
				data[i] = * it;
			}
		}

		Matrix_tpl<T, H, W> & operator +=(const Matrix_tpl<T, H, W> & m) { this->ForEachIn([& m](T * data, int i) { data[i] += m.data[i]; }); return * this; }
		Matrix_tpl<T, H, W> & operator -=(const Matrix_tpl<T, H, W> & m) { this->ForEachIn([& m](T * data, int i) { data[i] -= m.data[i]; }); return * this; }

		Matrix_tpl<T, H, W> operator +(const Matrix_tpl<T, H, W> & m) const { return Matrix_tpl<T, H, W> { * this } += m; }
		Matrix_tpl<T, H, W> operator -(const Matrix_tpl<T, H, W> & m) const { return Matrix_tpl<T, H, W> { * this } -= m; }

		template<typename T, int H2, int W2>
		Matrix_tpl<T, H, W2> operator *(const Matrix_tpl<T, H2, W2> & m) const {
			static_assert(H2 == W, "COLUMN of the first matrix must equals to ROW of the second matrix!");

			Matrix_tpl<T, H, W2> mat {};

			for(int resy = 0; resy < H; resy++) {
				for(int resx = 0; resx < W2; resx++) {
					
					for(int i = 0; i < W; i++) {
						mat.At(resy, resx) += this->At(resy, i) * m.At(i, resx);
					}

				}
			}

			return mat;
		}

		Matrix_tpl<T, H, W> & operator +=(T val) { this->ForEachOf([& val](T & elem) { elem += val; }); return * this; }
		Matrix_tpl<T, H, W> & operator -=(T val) { this->ForEachOf([& val](T & elem) { elem -= val; }); return * this; }
		Matrix_tpl<T, H, W> & operator *=(T val) { this->ForEachOf([& val](T & elem) { elem *= val; }); return * this; }
		Matrix_tpl<T, H, W> & operator /=(T val) { this->ForEachOf([& val](T & elem) { elem /= val; }); return * this; }

		Matrix_tpl<T, H, W> operator +(T val) const { return Matrix_tpl<T, H, W> { * this } += val; }
		Matrix_tpl<T, H, W> operator -(T val) const { return Matrix_tpl<T, H, W> { * this } -= val; }
		Matrix_tpl<T, H, W> operator *(T val) const { return Matrix_tpl<T, H, W> { * this } *= val; }
		Matrix_tpl<T, H, W> operator /(T val) const { return Matrix_tpl<T, H, W> { * this } /= val; }

		template<typename T, int H2, int W2>
		bool operator ==(const Matrix_tpl<T, H2, W2> & mat) const {
			if(H2 != H || W2 != W) {
				return false;
			}
			for(int i = H * W - 1; i >= 0; i--) {
				if(data[i] != mat.data[i]) {
					return false;
				}
			}
			return true;
		}
		template<typename T, int H2, int W2>
		bool operator !=(const Matrix_tpl<T, H2, W2> & mat) const {
			return !((* this) == mat);
		}

		const T & operator [](int y) const { return data[y]; }
		T & operator [](int y) { return data[y]; }

		const T & At(int y, int x) const { return data[y * W + x]; }
		T & At(int y, int x) { return data[y * W + x]; }

		int GetWidth() const { return W; }
		int GetHeight() const { return H; }

		void ForEachIn(const std::function<void (T * data, int i)> & func) {
			for(int i = 0, size = H * W; i < size; i++) {
				func(this->data, i);
			}
		}
		void ForEachOf(const std::function<void (T & elem)> & func) {
			for(auto & elem : data) {
				func(elem);
			}
		}

		T data[H * W] {};
	};

}
