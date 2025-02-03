#pragma once

#include <FrameMath/Vector2.h>

#include <utility>

namespace Frame {

	template<typename T>
	static inline bool PointInRectangle(const Vec2_tpl<T> & point, const Vec2_tpl<T> & rectXY1, const Vec2_tpl<T> & rectXY2) {
		const Vec2_tpl<T> rectLT { std::min(rectXY1.x, rectXY2.x), std::min(rectXY1.y, rectXY2.y) };
		const Vec2_tpl<T> rectRB { std::max(rectXY1.x, rectXY2.x), std::max(rectXY1.y, rectXY2.y) };
		return point.x >= rectLT.x && point.x <= rectRB.x && point.y >= rectLT.y && point.y <= rectRB.y;
	}

}